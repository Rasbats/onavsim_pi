/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  onavsim Plugin
 * Author:   David Register, Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
 ***************************************************************************
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
  #include <wx/glcanvas.h>
#endif //precompiled headers

#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/choice.h>

#include "onavsim_pi.h"
#include "onavsimUIDialogBase.h"
#include "onavsimUIDialog.h"

wxString myVColour[] = {_T("rgb(127, 0, 255)"), _T("rgb(0, 166, 80)"),  _T("rgb(253, 184, 19)"),  _T("rgb(248, 128, 64)"),  _T("rgb(248, 0, 0)")};

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new onavsim_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}



//---------------------------------------------------------------------------------------------------------
//
//    onavsim PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"


//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

onavsim_pi::onavsim_pi(void *ppimgr)
      :opencpn_plugin_115(ppimgr)
{
      // Create the PlugIn icons
      initialize_images();

	  wxString shareLocn = *GetpSharedDataLocation() +
		  _T("plugins") + wxFileName::GetPathSeparator() +
		  _T("onavsim_pi") + wxFileName::GetPathSeparator()
		  + _T("data") + wxFileName::GetPathSeparator();
	  wxImage panelIcon(shareLocn + _T("onavsim_panel_icon.png"));
	  if (panelIcon.IsOk())
		  m_panelBitmap = wxBitmap(panelIcon);
	  else
		  wxLogMessage(_T("    onavsim panel icon NOT loaded"));

      m_bShowonavsim = false;
	  
     

}

onavsim_pi::~onavsim_pi(void)
{
      delete _img_onavsim_pi;
      delete _img_onavsim;
}

int onavsim_pi::Init(void)
{
      AddLocaleCatalog( _T("opencpn-onavsim_pi") );

      // Set some default private member parameters
      m_onavsim_dialog_x = 0;
      m_onavsim_dialog_y = 0;
      m_onavsim_dialog_sx = 200;
      m_onavsim_dialog_sy = 400;
      m_ponavsimDialog = NULL;
      m_ponavsimOverlayFactory = NULL;
      m_bonavsimShowIcon = true;

      ::wxDisplaySize(&m_display_width, &m_display_height);

      //    Get a pointer to the opencpn configuration object
      m_pconfig = GetOCPNConfigObject();
	 
      //    And load the configuration items
      LoadConfig();



      // Get a pointer to the opencpn display canvas, to use as a parent for the onavsim dialog
      m_parent_window = GetOCPNCanvasWindow();

	

      //    This PlugIn needs a toolbar icon, so request its insertion if enabled locally
      if(m_bonavsimShowIcon) {
#ifdef onavsim_USE_SVG
          m_leftclick_tool_id = InsertPlugInToolSVG(_T( "onavsim" ), _svg_onavsim, _svg_onavsim, _svg_onavsim_toggled,
            wxITEM_CHECK, _("onavsim"), _T( "" ), NULL, onavsim_TOOL_POSITION, 0, this);
#else
          m_leftclick_tool_id = InsertPlugInTool(_T(""), _img_onavsim, _img_onavsim, wxITEM_CHECK,
                                                 _("onavsim"), _T(""), NULL,
                                                 onavsim_TOOL_POSITION, 0, this);	  
#endif
      }

	  wxMenu dummy_menu;
	  m_position_menu_id = AddCanvasContextMenuItem
	  (new wxMenuItem(&dummy_menu, -1, _("Select onavsim Start Position")), this);
	  SetCanvasContextMenuItemViz(m_position_menu_id, true);



      return (WANTS_OVERLAY_CALLBACK |
              WANTS_OPENGL_OVERLAY_CALLBACK |
              WANTS_CURSOR_LATLON       |
              WANTS_TOOLBAR_CALLBACK    |
              INSTALLS_TOOLBAR_TOOL     |
              WANTS_CONFIG              |
              WANTS_PREFERENCES         
              //WANTS_PLUGIN_MESSAGING
            );
}

bool onavsim_pi::DeInit(void)
{
    if(m_ponavsimDialog) {
        m_ponavsimDialog->Close();
        delete m_ponavsimDialog;
        m_ponavsimDialog = NULL;
    }

    delete m_ponavsimOverlayFactory;
    m_ponavsimOverlayFactory = NULL;

    return true;
}

int onavsim_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int onavsim_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int onavsim_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int onavsim_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxBitmap *onavsim_pi::GetPlugInBitmap()
{
      return &m_panelBitmap;
}

wxString onavsim_pi::GetCommonName()
{
      return _T("onavsim");
}


wxString onavsim_pi::GetShortDescription()
{
      return _("onavsim PlugIn for OpenCPN");
}


wxString onavsim_pi::GetLongDescription()
{
      return _("onavsim PlugIn for OpenCPN\nProvides an overlay of Tidal Current (Stream) Arrows.\n\n\
			   ");
}

void onavsim_pi::SetDefaults(void)
{
}


int onavsim_pi::GetToolbarToolCount(void)
{
      return 1;
}

void onavsim_pi::ShowPreferencesDialog( wxWindow* parent )
{
    onavsimPreferencesDialog *Pref = new onavsimPreferencesDialog(parent);

    Pref->m_cbUseRate->SetValue(m_bCopyUseRate);
    Pref->m_cbUseDirection->SetValue(m_bCopyUseDirection);
	Pref->m_cbUseHighRes->SetValue(m_bCopyUseHighRes);
	Pref->m_cbFillColour->SetValue(m_bonavsimUseHiDef);

	long selection;
	m_sCopyUseScale.ToLong(&selection);

	Pref->m_cScale->SetSelection((int)selection - 1);	

	wxColour myC0 = wxColour(myVColour[0]);
	Pref->myColourPicker0->SetColour(myC0);
    
	wxColour myC1 = wxColour(myVColour[1]);
	Pref->myColourPicker1->SetColour(myC1);

	wxColour myC2 = wxColour(myVColour[2]);
	Pref->myColourPicker2->SetColour(myC2);

	wxColour myC3 = wxColour(myVColour[3]);
	Pref->myColourPicker3->SetColour(myC3);

	wxColour myC4 = wxColour(myVColour[4]);
	Pref->myColourPicker4->SetColour(myC4);


 if( Pref->ShowModal() == wxID_OK ) {

	 //bool copyFillColour = true;
    
	 myVColour[0] = Pref->myColourPicker0->GetColour().GetAsString();
	 myVColour[1] = Pref->myColourPicker1->GetColour().GetAsString();
	 myVColour[2] = Pref->myColourPicker2->GetColour().GetAsString();
	 myVColour[3] = Pref->myColourPicker3->GetColour().GetAsString();
	 myVColour[4] = Pref->myColourPicker4->GetColour().GetAsString();


     bool copyrate = Pref->m_cbUseRate->GetValue();
     bool copydirection = Pref->m_cbUseDirection->GetValue();
	 bool copyresolution = Pref->m_cbUseHighRes->GetValue();

	 int selection = Pref->m_cScale->GetSelection();
	 wxString copyscale = Pref->m_cScale->GetString(selection);

	 bool FillColour = Pref->m_cbFillColour->GetValue();

		 if (m_bCopyUseRate != copyrate) {
			 m_bCopyUseRate = copyrate;
		 }

		 if (m_bCopyUseDirection != copydirection) {
			 m_bCopyUseDirection = copydirection;
		 }

		 if (m_bCopyUseHighRes != copyresolution) {
			 m_bCopyUseHighRes = copyresolution;
		 }

		 if (m_bonavsimUseHiDef != FillColour){
			 m_bonavsimUseHiDef = FillColour;
		 }
		 if (m_sCopyUseScale != copyscale){
			 m_sCopyUseScale = copyscale;
		 }

         if(m_ponavsimDialog )
		 {	
			 
			 m_ponavsimDialog->m_bUseRate = m_bCopyUseRate;
			 m_ponavsimDialog->m_bUseDirection = m_bCopyUseDirection; 
			 m_ponavsimDialog->m_bUseHighRes = m_bCopyUseHighRes;	
			 m_ponavsimDialog->m_bUseFillColour = m_bonavsimUseHiDef;
			 m_ponavsimDialog->m_sUseScale = m_sCopyUseScale;
			

			 m_ponavsimDialog->myUseColour[0] = myVColour[0];
 			 m_ponavsimDialog->myUseColour[1] = myVColour[1];
 			 m_ponavsimDialog->myUseColour[2] = myVColour[2];
 			 m_ponavsimDialog->myUseColour[3] = myVColour[3];
 			 m_ponavsimDialog->myUseColour[4] = myVColour[4];			 
		 }

		 if (m_ponavsimOverlayFactory)
		 {			 
			 m_ponavsimOverlayFactory->m_bShowRate = m_bCopyUseRate;
			 m_ponavsimOverlayFactory->m_bShowDirection = m_bCopyUseDirection;
			 m_ponavsimOverlayFactory->m_bHighResolution = m_bCopyUseHighRes;
			 m_ponavsimOverlayFactory->m_bShowFillColour = m_bonavsimUseHiDef;
			 m_ponavsimOverlayFactory->m_sShowScale = m_sCopyUseScale;
		 }

         SaveConfig();
		 
		 RequestRefresh(m_parent_window); // refresh main window
     }
	
}

void onavsim_pi::OnToolbarToolCallback(int id)
{
    
	if(!m_ponavsimDialog)
    {
		       		
		m_ponavsimDialog = new onavsimUIDialog(m_parent_window, this);
		m_ponavsimDialog->m_buttonStart->SetBackgroundColour(wxColour(0, 255, 0));
		m_ponavsimDialog->m_buttonStop->SetBackgroundColour(wxColour(255, 0, 0));
        wxPoint p = wxPoint(m_onavsim_dialog_x, m_onavsim_dialog_y);
        m_ponavsimDialog->Move(0,0);        // workaround for gtk autocentre dialog behavior
        m_ponavsimDialog->Move(p);

		m_ponavsimDialog->SetSize(m_onavsim_dialog_sx, m_onavsim_dialog_sy);

		m_ponavsimDialog->plugin = this;

        // Create the drawing factory
        m_ponavsimOverlayFactory = new onavsimOverlayFactory( *m_ponavsimDialog );
        m_ponavsimOverlayFactory->SetParentSize( m_display_width, m_display_height);		
        
    }

      // Qualify the onavsim dialog position
            bool b_reset_pos = false;

#ifdef __WXMSW__
        //  Support MultiMonitor setups which an allow negative window positions.
        //  If the requested window does not intersect any installed monitor,
        //  then default to simple primary monitor positioning.
            RECT frame_title_rect;
            frame_title_rect.left =   m_onavsim_dialog_x;
            frame_title_rect.top =    m_onavsim_dialog_y;
            frame_title_rect.right =  m_onavsim_dialog_x + m_onavsim_dialog_sx;
            frame_title_rect.bottom = m_onavsim_dialog_y + 30;


            if(NULL == MonitorFromRect(&frame_title_rect, MONITOR_DEFAULTTONULL))
                  b_reset_pos = true;
#else
       //    Make sure drag bar (title bar) of window on Client Area of screen, with a little slop...
            wxRect window_title_rect;                    // conservative estimate
            window_title_rect.x = m_onavsim_dialog_x;
            window_title_rect.y = m_onavsim_dialog_y;
            window_title_rect.width = m_onavsim_dialog_sx;
            window_title_rect.height = 30;

            wxRect ClientRect = wxGetClientDisplayRect();
            ClientRect.Deflate(60, 60);      // Prevent the new window from being too close to the edge
            if(!ClientRect.Intersects(window_title_rect))
                  b_reset_pos = true;

#endif

            if(b_reset_pos)
            {
                  m_onavsim_dialog_x = 20;
                  m_onavsim_dialog_y = 170;
                  m_onavsim_dialog_sx = 300;
                  m_onavsim_dialog_sy = 540;
            }

      //Toggle onavsim overlay display
      m_bShowonavsim = !m_bShowonavsim;

      //    Toggle dialog?
      if(m_bShowonavsim) {
          m_ponavsimDialog->Show();
      } else {
          m_ponavsimDialog->Hide();         
          }

      // Toggle is handled by the toolbar but we must keep plugin manager b_toggle updated
      // to actual status to ensure correct status upon toolbar rebuild
      SetToolbarItemState( m_leftclick_tool_id, m_bShowonavsim );
      RequestRefresh(m_parent_window); // refresh main window
}

void onavsim_pi::OnonavsimDialogClose()
{
    m_bShowonavsim = false;
    SetToolbarItemState( m_leftclick_tool_id, m_bShowonavsim );

    m_ponavsimDialog->Hide();

    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

}

bool onavsim_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    if(!m_ponavsimDialog ||
       !m_ponavsimDialog->IsShown() ||
       !m_ponavsimOverlayFactory)
        return false;

    m_ponavsimDialog->SetViewPort( vp );
    m_ponavsimOverlayFactory->RenderonavsimOverlay ( dc, vp );
    return true;
}

bool onavsim_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    if(!m_ponavsimDialog ||
       !m_ponavsimDialog->IsShown() ||
       !m_ponavsimOverlayFactory)
        return false;

    m_ponavsimDialog->SetViewPort( vp );
    m_ponavsimOverlayFactory->RenderGLonavsimOverlay ( pcontext, vp );
    return true;
}

void onavsim_pi::OnContextMenuItemCallback(int id)
{

	if (!m_ponavsimDialog)
		return;

	if (id == m_position_menu_id) {

		m_cursor_lat = GetCursorLat();
		m_cursor_lon = GetCursorLon();

		m_ponavsimDialog->OnContextMenu(m_cursor_lat, m_cursor_lon);
	}
}

void onavsim_pi::SetCursorLatLon(double lat, double lon)
{
	m_cursor_lat = lat;
	m_cursor_lon = lon;
}


bool onavsim_pi::LoadConfig(void)
{
    wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

    if(!pConf)
        return false;

    pConf->SetPath ( _T( "/PlugIns/onavsim" ) );

	m_bCopyUseRate = pConf->Read ( _T( "onavsimUseRate" ),1);
    m_bCopyUseDirection = pConf->Read ( _T( "onavsimUseDirection" ), 1);
	m_bCopyUseHighRes = pConf->Read(_T("onavsimUseHighResolution"), 1);
	m_bonavsimUseHiDef = pConf->Read ( _T( "onavsimUseFillColour" ), 1);
	m_sCopyUseScale = pConf->Read(_T("onavsimUseScale"), "1");
	
	m_CopyFolderSelected = pConf->Read ( _T( "onavsimFolder" ));
	if (m_CopyFolderSelected == wxEmptyString){

	  wxString g_SData_Locn = *GetpSharedDataLocation();

      // Establish location of Tide and Current data
      pTC_Dir = new wxString(_T("tcdata"));
      pTC_Dir->Prepend(g_SData_Locn);

	  m_CopyFolderSelected = *pTC_Dir;	  
	}

	m_CopyIntervalSelected = pConf->Read ( _T ( "onavsimInterval"), 20L);

    m_onavsim_dialog_sx = pConf->Read ( _T( "onavsimDialogSizeX" ), 300L );
    m_onavsim_dialog_sy = pConf->Read ( _T( "onavsimDialogSizeY" ), 540L );
    m_onavsim_dialog_x =  pConf->Read ( _T( "onavsimDialogPosX" ), 20L );
    m_onavsim_dialog_y =  pConf->Read ( _T( "onavsimDialogPosY" ), 170L );
	
    pConf->Read( _T("VColour0"), &myVColour[0], myVColour[0] );
    pConf->Read( _T("VColour1"), &myVColour[1], myVColour[1] );
	pConf->Read( _T("VColour2"), &myVColour[2], myVColour[2] );
	pConf->Read( _T("VColour3"), &myVColour[3], myVColour[3] );
	pConf->Read( _T("VColour4"), &myVColour[4], myVColour[4] );
	
    return true;
}

bool onavsim_pi::SaveConfig(void)
{
    wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

    if(!pConf)
        return false;

    pConf->SetPath ( _T( "/PlugIns/onavsim" ) );
    pConf->Write ( _T( "onavsimUseRate" ), m_bCopyUseRate );
    pConf->Write ( _T( "onavsimUseDirection" ), m_bCopyUseDirection );
	pConf->Write(_T("onavsimUseHighResolution"), m_bCopyUseHighRes);
	pConf->Write ( _T( "onavsimUseFillColour" ), m_bonavsimUseHiDef );
	pConf->Write(_T("onavsimUseScale"), m_sCopyUseScale);

	pConf->Write ( _T( "onavsimFolder" ), m_CopyFolderSelected); 
	pConf->Write ( _T( "onavsimInterval" ), m_CopyIntervalSelected);

    pConf->Write ( _T( "onavsimDialogSizeX" ),  m_onavsim_dialog_sx );
    pConf->Write ( _T( "onavsimDialogSizeY" ),  m_onavsim_dialog_sy );
    pConf->Write ( _T( "onavsimDialogPosX" ),   m_onavsim_dialog_x );
    pConf->Write ( _T( "onavsimDialogPosY" ),   m_onavsim_dialog_y );

	pConf->Write( _T("VColour0"), myVColour[0] );
	pConf->Write( _T("VColour1"), myVColour[1] );
	pConf->Write( _T("VColour2"), myVColour[2] );
	pConf->Write( _T("VColour3"), myVColour[3] );
	pConf->Write( _T("VColour4"), myVColour[4] );


    return true;
}

void onavsim_pi::SetColorScheme(PI_ColorScheme cs)
{
    DimeWindow(m_ponavsimDialog);
}

wxString onavsim_pi::StandardPath()
{
	wxStandardPathsBase& std_path = wxStandardPathsBase::Get();
	wxString s = wxFileName::GetPathSeparator();

#if defined(__WXMSW__)
	wxString stdPath = std_path.GetConfigDir();
#elif defined(__WXGTK__) || defined(__WXQT__)
	wxString stdPath = std_path.GetUserDataDir();
#elif defined(__WXOSX__)
	wxString stdPath = (std_path.GetUserConfigDir() + s + _T("opencpn"));
#endif

	stdPath += s + _T("plugins");
	if (!wxDirExists(stdPath))
		wxMkdir(stdPath);

	stdPath += s + _T("oNavSim");

#ifdef __WXOSX__
	// Compatibility with pre-OCPN-4.2; move config dir to
	// ~/Library/Preferences/opencpn if it exists
	wxString oldPath = (std_path.GetUserConfigDir() + s + _T("plugins") + s + _T("oNavSim"));
	if (wxDirExists(oldPath) && !wxDirExists(stdPath)) {
		wxLogMessage("oNavSim_pi: moving config dir %s to %s", oldPath, stdPath);
		wxRenameFile(oldPath, stdPath);
	}
#endif

	if (!wxDirExists(stdPath))
		wxMkdir(stdPath);

	stdPath += s; // is this necessary?
	return stdPath;
}



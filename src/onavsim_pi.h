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

#ifndef _onavsimPI_H_
#define _onavsimPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
  #include <wx/glcanvas.h>
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    0
#define     PLUGIN_VERSION_MINOR    2

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    15

#include "ocpn_plugin.h"
#include "onavsimOverlayFactory.h"
#include "onavsimUIDialog.h"

extern wxString myVColour[5]; 

class ControlDialog;


//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define onavsim_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class onavsim_pi : public opencpn_plugin_115
{
public:
      onavsim_pi(void *ppimgr);
      ~onavsim_pi(void);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The override PlugIn Methods
      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
	  bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
	  void OnContextMenuItemCallback(int id);
	  void SetCursorLatLon(double lat, double lon);
      
	  double GetCursorLat(void) { return m_cursor_lat; }
	  double GetCursorLon(void) { return m_cursor_lon; }

      void SetDefaults(void);
      int  GetToolbarToolCount(void);
      void ShowPreferencesDialog( wxWindow* parent );
      void OnToolbarToolCallback(int id);

// Other public methods
      void SetonavsimDialogX    (int x){ m_onavsim_dialog_x = x;};
      void SetonavsimDialogY    (int x){ m_onavsim_dialog_y = x;}
      void SetonavsimDialogSizeX(int x){ m_onavsim_dialog_sx = x;}
      void SetonavsimDialogSizeY(int x){ m_onavsim_dialog_sy = x;}
      void SetColorScheme(PI_ColorScheme cs);
	  void SetText();

      void OnonavsimDialogClose();

      bool GetCopyRate() { return  m_bCopyUseRate; }
      bool GetCopyDirection() { return  m_bCopyUseDirection; }
	  bool GetCopyResolution() { return  m_bCopyUseHighRes; }
	  bool GetCopyColour() { return m_bonavsimUseHiDef ; }
	  wxString GetCopyScale() { return  m_sCopyUseScale; }

	  wxString GetFolderSelected() {return m_CopyFolderSelected;}
	  int      GetIntervalSelected() {return m_CopyIntervalSelected;}
  
      onavsimOverlayFactory *GetonavsimOverlayFactory(){ return m_ponavsimOverlayFactory; }

	  ControlDialogBase * myControlDialog;

private:
      bool LoadConfig(void);
      bool SaveConfig(void);

      wxFileConfig     *m_pconfig;
      wxWindow         *m_parent_window;

      onavsimUIDialog     *m_ponavsimDialog;
      onavsimOverlayFactory *m_ponavsimOverlayFactory;

      int              m_display_width, m_display_height;
      int              m_leftclick_tool_id;
	  int				m_position_menu_id;

      int              m_onavsim_dialog_x, m_onavsim_dialog_y;
      int              m_onavsim_dialog_sx, m_onavsim_dialog_sy;

	  double m_cursor_lat;
	  double m_cursor_lon;

      // preference data
      bool              m_bonavsimUseHiDef;
      bool              m_bonavsimUseGradualColors;
	  bool              m_bCopyUseRate;
      bool              m_bCopyUseDirection;
	  bool				m_bCopyUseHighRes;
	  wxString          m_sCopyUseScale;

	  wxString          m_CopyFolderSelected;
	  int               m_CopyIntervalSelected;
	  

      int              m_bTimeZone;
     
      int              m_bStartOptions;
      wxString         m_RequestConfig;
      wxString         *pTC_Dir;
      
      bool             m_bonavsimShowIcon;

      int              m_height;

      bool			   m_bShowonavsim;

	  wxBitmap		   m_panelBitmap;

};

//----------------------------------------------------------------------------------------
// Prefrence dialog definition
//----------------------------------------------------------------------------------------

class onavsimPreferencesDialog : public onavsimPreferencesDialogBase
{
public:
		
	onavsimPreferencesDialog( wxWindow *pparent)
    : onavsimPreferencesDialogBase(pparent) {}
    ~onavsimPreferencesDialog() {}

private:
    
};
#endif

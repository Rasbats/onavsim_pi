/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  onavsim Object
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 *
 */
#include <wx/intl.h>
#include "wx/wx.h"
#include "wx/datetime.h"
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/debug.h>
#include <wx/graphics.h>
#include <wx/stdpaths.h>

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "onavsim_pi.h"
#include "folder.xpm"
#include "icons.h"
#include <wx/arrimpl.cpp>

#ifdef __WXMSW__
#include <windows.h>
#endif
#include <memory.h> 

#include <wx/colordlg.h>
#include <wx/event.h>
#include "onavsim_pi.h"

using namespace std;


#define FAIL(X) do { error = X; goto failed; } while(0)


//date/time in the desired time zone format
static wxString TToString( const wxDateTime date_time, const int time_zone )
{
    wxDateTime t( date_time );
    t.MakeFromTimezone( wxDateTime::UTC );
    if( t.IsDST() ) t.Subtract( wxTimeSpan( 1, 0, 0, 0 ) );
    switch( time_zone ) {
        case 0: return t.Format( _T(" %a %d-%b-%Y  %H:%M LOC"), wxDateTime::Local );
        case 1:
        default: return t.Format( _T(" %a %d-%b-%Y %H:%M  UTC"), wxDateTime::UTC );
    }
}

onavsimUIDialog::onavsimUIDialog(wxWindow *parent, onavsim_pi *ppi, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
: onavsimUIDialogBase(parent, id, title, pos, size, style), m_ptcmgr(0), m_vp(0)
{
    pParent = parent;
    pPlugIn = ppi;

    wxFileConfig *pConf = GetOCPNConfigObject();

    if(pConf) {
        pConf->SetPath ( _T ( "/Plugins/onavsim" ) );

		pConf->Read ( _T ( "onavsimUseRate" ), &m_bUseRate, 1 );
        pConf->Read ( _T ( "onavsimUseDirection" ), &m_bUseDirection, 1);
		pConf->Read(_T("onavsimUseHighResolution"), &m_bUseHighRes, 1);
		pConf->Read ( _T ( "onavsimUseFillColour" ), &m_bUseFillColour, 1);
		pConf->Read(_T("onavsimUseScale"), &m_sUseScale, _T("1"));

		pConf->Read ( _T ( "onavsimInterval" ), &m_IntervalSelected, 20L);
		pConf->Read ( _T ( "onavsimFolder" ), &m_FolderSelected);

		pConf->Read( _T("VColour0"), &myVColour[0], myVColour[0] );
		pConf->Read( _T("VColour1"), &myVColour[1], myVColour[1] );
		pConf->Read( _T("VColour2"), &myVColour[2], myVColour[2] );
		pConf->Read( _T("VColour3"), &myVColour[3], myVColour[3] );
		pConf->Read( _T("VColour4"), &myVColour[4], myVColour[4] );
		
		myUseColour[0] = myVColour[0];
		myUseColour[1] = myVColour[1];
		myUseColour[2] = myVColour[2];
		myUseColour[3] = myVColour[3];
		myUseColour[4] = myVColour[4];
		


    }

    

    this->Connect( wxEVT_MOVE, wxMoveEventHandler( onavsimUIDialog::OnMove ) );

	frigateLat = 50.0;
	frigateLon = -4.0;
	frigateSpd = 0;

	DimeWindow( this );
	
}

onavsimUIDialog::~onavsimUIDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    if(pConf) {
        pConf->SetPath ( _T ( "/Plugins/onavsim" ) );

		pConf->Write ( _T ( "onavsimUseRate" ), m_bUseRate );
		pConf->Write ( _T ( "onavsimUseDirection" ), m_bUseDirection );
		pConf->Write(_T("onavsimUseHighResolution"), m_bUseHighRes);
		pConf->Write ( _T ( "onavsimUseFillColour" ), m_bUseFillColour );
		pConf->Write(_T("onavsimUseScale"), m_sUseScale);

		pConf->Write( _T("VColour0"), myVColour[0] );
		pConf->Write( _T("VColour1"), myVColour[1] );
		pConf->Write( _T("VColour2"), myVColour[2] );
		pConf->Write( _T("VColour3"), myVColour[3] );
		pConf->Write( _T("VColour4"), myVColour[4] );	

    }
    
    this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( onavsimUIDialog::OnMove ) );
    m_timePickerTime->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( onavsimUIDialog::OnDateTimeChanged ), NULL, this );
        
}

void onavsimUIDialog::OnContextMenu(double m_lat, double m_lon) {

	frigateLat = m_lat;
	frigateLon = m_lon;

	//wxMessageBox(wxString::Format("%f", frigateLat));

}



void onavsimUIDialog::SetViewPort( PlugIn_ViewPort *vp )
{
    if(m_vp == vp)  return;

    delete m_vp;
    m_vp = new PlugIn_ViewPort(*vp);
}

void onavsimUIDialog::OnClose( wxCloseEvent& event )
{
    pPlugIn->OnonavsimDialogClose();
}

void onavsimUIDialog::OnMove( wxMoveEvent& event )
{
    //    Record the dialog position
    wxPoint p = GetPosition();
    pPlugIn->SetonavsimDialogX( p.x );
    pPlugIn->SetonavsimDialogY( p.y );

    event.Skip();
}

void onavsimUIDialog::OnSize( wxSizeEvent& event )
{
    //    Record the dialog size
    wxSize p = event.GetSize();
    pPlugIn->SetonavsimDialogSizeX( p.x );
    pPlugIn->SetonavsimDialogSizeY( p.y );

    event.Skip();
}


void onavsimUIDialog::OnTimer(wxTimerEvent& event) {

	Notify();
}


void onavsimUIDialog::Notify() {

	

	frigateSpd /= 7200;

	int dir = m_sliderDirection->GetValue();
	double ddir;
	ddir = (double)dir;

	int spd = m_sliderSpeed->GetValue();
	double dspd;
	dspd = (double)spd;
	frigateSpd = dspd;
	frigateSpd /= 7200;  // m_interval = 500

	double newFrigateLat;
	double newFrigateLon;

	PositionBearingDistanceMercator_Plugin(frigateLat, frigateLon, ddir, frigateSpd, &newFrigateLat, &newFrigateLon);

	frigateLat = newFrigateLat;
	frigateLon = newFrigateLon;
	frigateDir = ddir;

	RequestRefresh(pParent);


}

void onavsimUIDialog::OnStartDriving(wxCommandEvent& event) {

	startDriving();
}

void onavsimUIDialog::OnStopDriving(wxCommandEvent& event) {

	if (m_timerFrigate.IsRunning()) m_timerFrigate.Stop();

}

void onavsimUIDialog::startDriving() {

	//wxMessageBox("here");

	//wxMessageBox(wxString::Format("%f", frigateLat));

	double scale_factor = GetOCPNGUIToolScaleFactor_PlugIn();
	JumpToPosition(frigateLat, frigateLon, scale_factor);

	int m_interval = 500;
	m_timerFrigate.Start(m_interval, wxTIMER_CONTINUOUS); // start timer
}


wxString onavsimUIDialog::MakeDateTimeLabel(wxDateTime myDateTime)
{			
    const wxString dateLabel(myDateTime.Format( _T( "%a") ));
    m_staticTextDatetime->SetLabel(dateLabel);
    
    m_datePickerDate->SetValue(myDateTime.GetDateOnly());
    m_timePickerTime->SetTime(myDateTime.GetHour(),myDateTime.GetMinute(), myDateTime.GetSecond());

    return dateLabel;
}

void onavsimUIDialog::About(wxCommandEvent& event)
{
	m_pControlDialog = new ControlDialog(this);


	m_pControlDialog->Plugin_Dialog = this;
	m_pControlDialog->Show();
	m_pControlDialog->Fit();
	/*
	plugin->myControlDialog = new ControlDialogBase(this,wxID_ANY, _("Test Control"), { 100, 100 }, wxDefaultSize, 0);
	if (plugin->myControlDialog->ShowModal() == wxID_OK)
	{
		wxMessageBox("here");
	}
	*/
	event.Skip();
}

void onavsimUIDialog::startTest()
{
	

}

ControlDialog::ControlDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : ControlDialogBase(parent, id, title, pos, size, style)
{

}

void ControlDialog::OnTestControl(wxCommandEvent& event) {

	//wxMessageBox("here at test");
	Plugin_Dialog->startDriving();
	Plugin_Dialog->m_sliderSpeed->SetValue(50);

}

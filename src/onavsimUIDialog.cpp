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
: onavsimUIDialogBase(parent, id, title, pos, size, style), m_vp(0)
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
	goodToGo = true;
	itemChecked = "";

	m_unitCourse = 0;
	m_unitSpeed = 0;

	myNavObjects.clear();

	inControl = false;
	dirChange = 0;

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

void onavsimUIDialog::OnCheckNavalUnit(wxCommandEvent& event) {

	int c = 0;
	int itemC;
	int s;
	for (int c = 0; c < m_checkListNavalUnits->GetCount(); c++) {
		if (m_checkListNavalUnits->IsSelected(c)) {
			m_checkListNavalUnits->Check(c, true);
			itemC = c;
			itemChecked = m_checkListNavalUnits->GetString(c);					
		}
		else {
			m_checkListNavalUnits->Check(c, false);
		}
	}

	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		if (it->name == itemChecked) {
			if (inControl) {
				myDir = it->sliderDirValue;
			    m_pControlDialog->m_sliderSpeed->SetValue(it->sliderSpdValue);
			}
			
			RequestRefresh(this);
			break;
		}
	}

	
}

void onavsimUIDialog::Notify() {

	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		if (it->name == itemChecked) {

			initRudder = m_pControlDialog->m_sliderRudder->GetValue();
			double myRudder = initRudder - 30;
			if (myRudder < 0) {
				initRudder -= 30.0;
				myRudder = std::abs(initRudder);
				myDir -= myRudder;
				double myPortRudder = 30 - std::abs(myRudder);
				m_pControlDialog->m_gaugeRudderPort->SetValue(myPortRudder);
				m_pControlDialog->m_textCtrlRudderPort->SetValue(wxString::Format(_T("%.0f"), myRudder) + _T(" P"));
				m_pControlDialog->m_gaugeRudderStbd->SetValue(0);
				m_pControlDialog->m_textCtrlRudderStbd->SetValue(_T(""));
			}
			else if (myRudder >= 0) {

				initRudder -= 30;
				myDir += initRudder;
				m_pControlDialog->m_gaugeRudderStbd->SetValue(myRudder);
				if (myRudder == 0) {
					m_pControlDialog->m_textCtrlRudderStbd->SetValue(_T(""));
				}
				else {
					m_pControlDialog->m_textCtrlRudderStbd->SetValue(wxString::Format(_T("%.0f"), myRudder) + _T(" S"));
				}
				m_pControlDialog->m_gaugeRudderPort->SetValue(0);
				m_pControlDialog->m_textCtrlRudderPort->SetValue(_T(""));

			}

			if (myDir < 0) {
				myDir += 360;
			}
			else if (myDir > 360) {
				myDir -= 360;
			}

			myDir += dirChange;
			dirChange = 0;
			it->sliderDirValue = myDir;
			m_pControlDialog->m_stHeading->SetLabel(wxString::Format(_T("%003.0f"), (double)myDir));

			it->sliderSpdValue = m_pControlDialog->m_sliderSpeed->GetValue();
			int thisSpeed = m_pControlDialog->m_sliderSpeed->GetValue();
			m_pControlDialog->m_stSpeed->SetLabel(wxString::Format(_T("%3.0f"), (double)thisSpeed));

			break;
		}

	}

	//PositionBearingDistanceMercator_Plugin(frigateLat, frigateLon, ddir, frigateSpd, &newFrigateLat, &newFrigateLon);

	wxString timeStamp = wxString::Format(_T("%i"), wxGetUTCTime());
	int newMMSI = 123;
	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		wxString myNMEAais = myAIS->nmeaEncode(_T("18"), newMMSI, _T("5"), it->sliderSpdValue, it->lat, it->lon, it->sliderDirValue, it->sliderDirValue, _T("B"), timeStamp);
		PushNMEABuffer(myNMEAais + "\n");

		newMMSI++;
	}


	//wxString myNMEAais = myAIS->nmeaEncode(_T("18"), 12345, _T("5"), dspd, it->lat, it->lon, ddir, ddir, _T("B"), timeStamp);
	//PushNMEABuffer(myNMEAais + "\n");

		

	
	
	RequestRefresh(pParent);

}

void onavsimUIDialog::OnStartDriving(wxCommandEvent& event) {

	StartControlDriving();
}

void onavsimUIDialog::OnStopDriving(wxCommandEvent& event) {

	if (m_timerFrigate.IsRunning()) m_timerFrigate.Stop();

	if (inControl) {
		m_pControlDialog->Hide();
		m_pControlDialog->Destroy();
		inControl = false;
	}
	else {
		wxMessageBox("Unit Controller not active");
	}

}

void onavsimUIDialog::startDriving() {
	
	int m_interval = 500;
	m_timerFrigate.Start(m_interval, wxTIMER_CONTINUOUS); // start timer

}

void onavsimUIDialog::StartControlDriving() {

	if (myNavObjects.size() == 0) {
		wxMessageBox("Please create a unit to drive");
		return;
	}

	bool unitSelected = false;

	for (int c = 0; c < m_checkListNavalUnits->GetCount(); c++) {
		if (m_checkListNavalUnits->IsSelected(c)) {
			unitSelected = true;
		}
	}

	if (!unitSelected) {
		wxMessageBox("No unit selected");
		return;
	}

	if (inControl) {
		wxMessageBox("Already in control");
		return;
	}


	m_pControlDialog = new ControlDialog(this);


	inControl = true;

	m_pControlDialog->Plugin_Dialog = this;

	m_pControlDialog->Show();
	m_pControlDialog->Fit();

	int c = 0;
	int itemC;

	for (c = 0; c < m_checkListNavalUnits->GetCount(); c++) {
		if (m_checkListNavalUnits->IsSelected(c)) {			
			itemChecked = m_checkListNavalUnits->GetStringSelection();
			break;
		}		
	}

	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		if (it->name == itemChecked) {
			myDir = it->sliderDirValue;
			mySpd = it->sliderSpdValue;
			m_pControlDialog->SetUnitControls(it->sliderSpdValue);			
			break;
		}
	}

	double scale_factor = GetOCPNGUIToolScaleFactor_PlugIn();
	JumpToPosition(frigateLat, frigateLon, scale_factor);

	int m_interval = 500;
	m_timerFrigate.Start(m_interval, wxTIMER_CONTINUOUS); // start timer



	myAIS = new AisMaker();
}


void onavsimUIDialog::About(wxCommandEvent& event)
{
	
	wxMessageBox("Not yet implemented");
	event.Skip();
}

void onavsimUIDialog::OnCreateNavObject(wxCommandEvent& event) {

	if (inControl) {
		wxMessageBox("Unable to create a unit while the controller is in use");
		return;
	}
	
	m_pNavUnitDialog = new NavUnitDialog(this);

	m_pNavUnitDialog->Plugin_Dialog = this;
	m_pNavUnitDialog->Show();
	m_pNavUnitDialog->Fit();

	if (m_pNavUnitDialog->ShowModal() == wxID_OK)
	{

		wxString name = m_pNavUnitDialog->m_textNavUnitName->GetValue();
		wxString type = m_pNavUnitDialog->m_choiceNavUnitType->GetStringSelection();

		m_pNavUnitDialog->Plugin_Dialog->CreateNavUnit(name, type);
	}

	event.Skip();
	
	RequestRefresh(pParent);

}

template< typename TContainer >
static bool EraseFromUnorderedByIndex(TContainer& inContainer, size_t inIndex)
{
	if (inIndex < inContainer.size())
	{
		if (inIndex != inContainer.size() - 1)
			inContainer[inIndex] = inContainer.back();
		inContainer.pop_back();
		return true;
	}
	return false;
}

void onavsimUIDialog::OnRemoveNavObject(wxCommandEvent& event) {

	if (inControl) {
		wxMessageBox("Unable to remove a unit while the controller is in use");
		return;
	}

	int pos = 0;
	int c;

	for (c = 0; c < m_checkListNavalUnits->GetCount(); c++) {
		if (m_checkListNavalUnits->IsSelected(c)) {
			itemChecked = m_checkListNavalUnits->GetStringSelection();
			break;
		}
	}

	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		if (it->name == itemChecked) {			
			break;
		}
		pos++;
	}

	EraseFromUnorderedByIndex(myNavObjects, pos);

	m_checkListNavalUnits->Delete(c);
	
	event.Skip();

	RequestRefresh(pParent);
}

void onavsimUIDialog::CreateNavUnit(wxString unitname, wxString unittype) {

	
	NavObject newNavObj;
	newNavObj.name = unitname;
	newNavObj.type = unittype;
	newNavObj.lat = frigateLat;
	newNavObj.lon = frigateLon;
	newNavObj.spd = 0.;
	newNavObj.dir = 0.;
	newNavObj.mmsi = 122345;
	newNavObj.sliderSpdValue = 0.;
	newNavObj.sliderDirValue = 0.;

	myNavObjects.push_back(newNavObj);

	//wxMessageBox(unitname);

	wxArrayString myItems;
	myItems.Add(unitname);

	int c;
	for (c = 0; c < m_checkListNavalUnits->GetCount(); c++) {
		m_checkListNavalUnits->Check(c, false);
	}

	m_checkListNavalUnits->InsertItems(myItems, 0);
	m_checkListNavalUnits->SetSelection(0);
	m_checkListNavalUnits->Check(0, true);

	RequestRefresh(pParent);

}
//
// The controller for the units
//
ControlDialog::ControlDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : UnitControlDialogBase(parent, id, title, pos, size, style)
{

}

void ControlDialog::OnSpeedChanged(wxCommandEvent& event) {

	Plugin_Dialog->m_unitSpeed = m_sliderSpeed->GetValue();
}


void ControlDialog::OnButtonStart(wxCommandEvent& event) {

	Plugin_Dialog->startDriving();

}

void ControlDialog::OnButtonStop(wxCommandEvent& event) {

	if (Plugin_Dialog->m_timerFrigate.IsRunning()) Plugin_Dialog->m_timerFrigate.Stop();	
	
	
}

void ControlDialog::OnMidships(wxCommandEvent& event) {

	m_sliderRudder->SetValue(30);

}

void ControlDialog::OnMinus1(wxCommandEvent& event) {

	Plugin_Dialog->dirChange = -1;

}

void ControlDialog::OnMinus10(wxCommandEvent& event) {

	Plugin_Dialog->dirChange = -10;

}

void ControlDialog::OnPlus10(wxCommandEvent& event) {

	Plugin_Dialog->dirChange = 10;

}

void ControlDialog::OnPlus1(wxCommandEvent& event) {

	Plugin_Dialog->dirChange = 1;

}


void ControlDialog::OnClose(wxCloseEvent& event) {

	if (Plugin_Dialog->m_timerFrigate.IsRunning()) Plugin_Dialog->m_timerFrigate.Stop();

	Plugin_Dialog->inControl = false;

	Hide();
	
	Destroy();
}

void ControlDialog::SetUnitControls(int newSpeed) {
	
	m_sliderSpeed->SetValue(newSpeed);
}



//
// The input dialog for setting up a unit
//
NavUnitDialog::NavUnitDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : NavUnitDialogBase(parent, id, title, pos, size, style)
{

}

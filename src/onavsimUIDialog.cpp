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

void onavsimUIDialog::OnListNavalUnit(wxListEvent& event) {

	long lSelectedItem = m_listNavalUnits->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (lSelectedItem != -1) {
		itemChecked = m_listNavalUnits->GetItemText(lSelectedItem);	
		m_listNavalUnits->SetItemState(lSelectedItem, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	}
	else {
		wxMessageBox("No unit selected");
		return;
	}

	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		if (it->name == itemChecked) {
			if (inControl) {				
				myDir = it->sliderDirValue;
			    m_pControlDialog->m_sliderSpeed->SetValue(it->sliderSpdValue);
			}			
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

	long lSelectedItem = m_listNavalUnits->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (lSelectedItem != -1) {
		itemChecked = m_listNavalUnits->GetItemText(lSelectedItem);
	} else {
		wxMessageBox("No unit selected");
		return;
	}

	if (inControl) {
		wxMessageBox("Already in control");
		return;
	}


	m_pControlDialog = new ControlDialog(this);

	wxPoint p = wxPoint(plugin->m_onavsim_dialog_x, plugin->m_onavsim_dialog_y + 300);
	m_pControlDialog->Move(p);


	inControl = true;

	m_pControlDialog->Plugin_Dialog = this;

	m_pControlDialog->Show();
	m_pControlDialog->Fit();
	
	double startLat, startLon;
	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		if (it->name == itemChecked) {
			myDir = it->sliderDirValue;
			mySpd = it->sliderSpdValue;
			m_pControlDialog->SetUnitControls(it->sliderSpdValue);	
			startLat = it->lat;
			startLon = it->lon;
			break;
		}
	}

	double scale_factor = GetOCPNGUIToolScaleFactor_PlugIn();
	JumpToPosition(startLat, startLon, scale_factor);

	int m_interval = 500;
	m_timerFrigate.Start(m_interval, wxTIMER_CONTINUOUS); // start timer



	myAIS = new AisMaker();
}


void onavsimUIDialog::About(wxCommandEvent& event)
{
	SaveNavUnitsToXml(myNavObjects, "theFleet.xml");
	//wxMessageBox("Not yet implemented");
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

	
	long lSelectedItem = m_listNavalUnits->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	itemChecked = m_listNavalUnits->GetItemText(lSelectedItem);
	//wxMessageBox(itemChecked);
	
	int c = 0;
	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {

		if (it->name == itemChecked) {			
			EraseFromUnorderedByIndex(myNavObjects, c);
			break;
		}
		c++;
	}	
	
	long index = lSelectedItem;
	long count = m_listNavalUnits->GetItemCount();

	if (count == 1)//if there is only one item in the list, deleted even if not selected
	{
		m_listNavalUnits->DeleteItem(0);
		m_listNavalUnits->Refresh();
		return;
	}
	if (index < 0) //No item selected or empty list
	{
		return;
	}

	m_listNavalUnits->DeleteItem(index);
	m_listNavalUnits->Refresh();

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

	long c = m_listNavalUnits->GetItemCount();
	
	m_listNavalUnits->InsertItem(c, newNavObj.name);		
	m_listNavalUnits->SetItemState(c, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);

	RequestRefresh(pParent);
}

double AttributeDouble(TiXmlElement *e, const char *name, double def)
{
	const char *attr = e->Attribute(name);
	if (!attr)
		return def;
	char *end;
	double d = strtod(attr, &end);
	if (end == attr)
		return def;
	return d;
}

int AttributeInt(TiXmlElement *e, const char *name, int def)
{
	const char *attr = e->Attribute(name);
	if (!attr)
		return def;
	char *end;
	long d = strtol(attr, &end, 10);
	if (end == attr)
		return def;
	return d;
}

#define FAIL(X) do { error = X; goto failed; } while(0)


void onavsimUIDialog::SaveNavUnitsToXml(vector<NavObject> &myNavObjects, wxString filename)
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "utf-8", "");
	doc.LinkEndChild(decl);

	TiXmlElement * root = new TiXmlElement("FleetData");
	doc.LinkEndChild(root);

	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {
		TiXmlElement *c = new TiXmlElement("Unit");

		c->SetAttribute("UnitName", it->name. mb_str());
		c->SetAttribute("UnitType", it->type.mb_str());		
		c->SetAttribute("Lat", wxString::Format(_T("%.5f"), it->lat).mb_str());
		c->SetAttribute("Lon", wxString::Format(_T("%.5f"), it->lon).mb_str());
		c->SetAttribute("Spd", wxString::Format(_T("%.5f"), it->spd).mb_str());
		c->SetAttribute("Cse", wxString::Format(_T("%.5f"), it->dir).mb_str());
		c->SetAttribute("MMSI", wxString::Format(_T("%i"), it->mmsi).mb_str());
		c->SetAttribute("sliderSpdValue", wxString::Format(_T("%i"), it->sliderSpdValue).mb_str());
		c->SetAttribute("sliderDirValue", wxString::Format(_T("%i"), it->sliderDirValue).mb_str());

		root->LinkEndChild(c);
	}

	wxString layer_path = plugin->StandardPath();

	if (!doc.SaveFile((layer_path + filename).mb_str()))
		wxLogMessage(_("oNavSim") + wxString(_T(": ")) + _("Failed to save xml file: ") + filename);
}

void onavsimUIDialog::LoadNavUnitsFromXml(vector<NavObject> &myFleetObjects, wxString fleetUnits)
{
	TiXmlDocument doc;
	wxString name;
	wxString error;
	wxString fleetUnits_path = plugin->StandardPath();

	//wxMessageBox(fleetUnits_path + fleetUnits);
	myFleetObjects.clear();

	if (!doc.LoadFile((fleetUnits_path + fleetUnits).mb_str()))
		FAIL(_("Failed to load fleet units"));
	else {
		TiXmlElement* root = doc.RootElement();

		if (strcmp(root->Value(), "FleetData"))
			FAIL(_("Invalid xml file"));

		for (TiXmlElement* e = root->FirstChildElement(); e; e = e->NextSiblingElement()) {
			if (!strcmp(e->Value(), "Unit")) {
				name = wxString::FromUTF8(e->Attribute("UnitName"));
				NavObject myUnit;
				myUnit.name = name;
				myUnit.type = wxString::FromUTF8(e->Attribute("UnitType"));				
				myUnit.lat = AttributeDouble(e, "Lat", 0);
				myUnit.lon = AttributeDouble(e, "Lon", 0);
				myUnit.spd = AttributeDouble(e, "Spd", 0);
				myUnit.dir = AttributeDouble(e, "Cse", 0);
				myUnit.mmsi = AttributeInt(e, "MMSI", 0);
				myUnit.sliderSpdValue = AttributeInt(e, "sliderSpdValue", 0);
				myUnit.sliderDirValue = AttributeInt(e, "sliderDirValue", 0);				

				myFleetObjects.push_back(myUnit);

			}
			else
				FAIL(_("Unrecognized xml node: ") + wxString::FromUTF8(e->Value()));
		}
	}
	return;
failed:
	wxLogMessage(_("onavsimuidialog") + wxString(_T(" : ")) + error);
}

void onavsimUIDialog::OnPopulate(wxCommandEvent& event) {

	LoadNavUnitsFromXml(myFleetObjects, "theFleet.xml");		
	
	m_listNavalUnits->DeleteAllItems();

	myNavObjects.clear();

	
	for (std::vector<NavObject>::iterator it = myFleetObjects.begin(); it != myFleetObjects.end(); it++) {
	
		myNavObjects.push_back(*it);
		//wxMessageBox(it->name);
	
	}

	int c = myNavObjects.size();
	wxString sz = wxString::Format("%i", c);
	//wxMessageBox(sz);

	
	for (std::vector<NavObject>::iterator it = myNavObjects.begin(); it != myNavObjects.end(); it++) {			
		long c = m_listNavalUnits->GetItemCount();
		m_listNavalUnits->InsertItem(c,it->name);
		m_listNavalUnits->SetItemState(c, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);		
	}

	//m_listNavalUnits->SetItemState(0, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	

	
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

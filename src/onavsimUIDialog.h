/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  onavsim Plugin Friends
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
 */

#ifndef __onavsimUIDIALOG_H__
#define __onavsimUIDIALOG_H__
#endif

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/fileconf.h>
#include <wx/glcanvas.h>

#include "onavsimUIDialogBase.h"

#include "tinyxml.h"
#include <wx/progdlg.h>
#include <list>
#include <vector>

#include "tcmgr.h"
#include "wx/dateevt.h"
#include "wx/stattext.h"
#include "ocpn_plugin.h"
#include "wx/dialog.h"
#include <wx/calctrl.h>
#include "wx/window.h"
#include "timectrl.h"
#include <wx/colordlg.h>
#include <wx/event.h>
#include <algorithm>

using namespace std;

#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */


#if !defined(NAN)
static const long long lNaN = 0xfff8000000000000;
#define NAN (*(double*)&lNaN)
#endif



#ifdef __WXOSX__
#define onavsim_DIALOG_STYLE wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP
#else
#define onavsim_DIALOG_STYLE wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER
#endif

class onavsimOverlayFactory;
class PlugIn_ViewPort;

class wxFileConfig;
class onavsim_pi;
class wxGraphicsContext;
class onavsimUIDialog;

class NavObject {
public:
	wxString name;
	int id;
	double lat, lon, dir, spd;
	bool isDead;
};


class ControlDialog: public ControlDialogBase
{
public:
	ControlDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Add Tidal Data"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxCAPTION | wxDEFAULT_DIALOG_STYLE | wxMAXIMIZE_BOX | wxRESIZE_BORDER);
	
	onavsimUIDialog *Plugin_Dialog;
	void OnTestControl(wxCommandEvent& event);

	
private:


};




class onavsimUIDialog: public onavsimUIDialogBase {
public:

    onavsimUIDialog(wxWindow* parent, onavsim_pi *ppi, wxWindowID id = wxID_ANY, const wxString& title = _("oNavSim"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,300 ), long style = onavsim_DIALOG_STYLE);
    ~onavsimUIDialog();
    
    
	void OnContextMenu(double m_lat, double m_lon);
    void SetViewPort( PlugIn_ViewPort *vp );
	PlugIn_ViewPort *vp;

	
	bool m_bUseRate;    
	bool m_bUseDirection; 
	bool m_bUseHighRes;
	bool m_bUseFillColour;
	wxString m_sUseScale;

	wxString myUseColour[5];

	wxDateTime m_dtNow;
	double m_dInterval;

	bool onNext;
	bool onPrev;

    wxString m_FolderSelected;
	int m_IntervalSelected;
	
	time_t myCurrentTime; 

	
	wxString MakeDateTimeLabel(wxDateTime myDateTime);    

	//naval simulation
	double frigateLat;
	double frigateLon;
	double frigateDir;
	double frigateSpd;

	void OnTimer(wxTimerEvent& event);
	void Notify();

	void OnStartDriving(wxCommandEvent& event);
	void OnStopDriving(wxCommandEvent& event);
	void startDriving();
	void startTest(wxString myTimer);
	
	void OnCreateNavObject(wxCommandEvent& event);

	
	onavsim_pi *plugin;
	void About(wxCommandEvent& event);

	ControlDialog *m_pControlDialog;

	std::vector<NavObject>myNavObjects;
	
	wxArrayClassInfo myInfo;
	
     wxWindow *pParent;

private:

    void OnClose( wxCloseEvent& event );
    void OnMove( wxMoveEvent& event );
    void OnSize( wxSizeEvent& event );	
	


    //    Data
    
    onavsim_pi *pPlugIn;

    PlugIn_ViewPort  *m_vp;
 
    double m_cursor_lat, m_cursor_lon;
	wxString         g_SData_Locn;
	wxString        *pTC_Dir;

	bool isNowButton;
	wxTimeSpan  myTimeOfDay;

};


#endif
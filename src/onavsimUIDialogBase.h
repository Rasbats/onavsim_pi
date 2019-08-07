///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/clrpicker.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class onavsimUIDialogBase
///////////////////////////////////////////////////////////////////////////////
class onavsimUIDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticTextDatetime;
		wxDatePickerCtrl* m_datePickerDate;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnDateTimeChanged( wxDateEvent& event ) { event.Skip(); }
		virtual void About( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreateNavObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStartDriving( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStopDriving( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimer( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxTimePickerCtrl* m_timePickerTime;
		wxButton* m_buttonHelp;
		wxButton* m_buttonCreate;
		wxChoice* m_choiceNavObject;
		wxButton* m_buttonStart;
		wxButton* m_buttonStop;
		wxSlider* m_sliderDirection;
		wxSlider* m_sliderSpeed;
		wxTextCtrl* m_textCtrlTest;
		wxTimer m_timerFrigate;

		onavsimUIDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~onavsimUIDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class onavsimPreferencesDialogBase
///////////////////////////////////////////////////////////////////////////////
class onavsimPreferencesDialogBase : public wxDialog
{
	private:
		wxStaticText* staticTextLess05;
		wxStaticText* staticText0515;
		wxStaticText* staticText1525 ;
		wxStaticText* staticText2535;
		wxStaticText* m_staticTextMore35;

	protected:
		wxStaticText* m_staticText8;
		wxStdDialogButtonSizer* m_sdbSizerButtons;
		wxButton* m_sdbSizerButtonsOK;
		wxButton* m_sdbSizerButtonsCancel;

		// Virtual event handlers, overide them in your derived class
		virtual void OnChoice( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxCheckBox* m_cbUseRate;
		wxCheckBox* m_cbUseDirection;
		wxCheckBox* m_cbFillColour;
		wxCheckBox* m_cbUseHighRes;
		wxColourPickerCtrl* myColourPicker0;
		wxColourPickerCtrl* myColourPicker1;
		wxColourPickerCtrl* myColourPicker2;
		wxColourPickerCtrl* myColourPicker3;
		wxColourPickerCtrl* myColourPicker4;
		wxChoice* m_cScale;

		onavsimPreferencesDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 410,440 ), long style = wxCAPTION|wxRESIZE_BORDER );
		~onavsimPreferencesDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ControlDialogBase
///////////////////////////////////////////////////////////////////////////////
class ControlDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText12;
		wxSlider* m_sliderSpeed;

		// Virtual event handlers, overide them in your derived class
		virtual void OnTestControl( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxSlider* m_sliderDirection;
		wxButton* m_buttonTest;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Cancel;

		ControlDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~ControlDialogBase();

};


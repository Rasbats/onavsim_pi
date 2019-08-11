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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/checklst.h>
#include <wx/timer.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/clrpicker.h>
#include <wx/choice.h>
#include <wx/gauge.h>
#include <wx/slider.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class onavsimUIDialogBase
///////////////////////////////////////////////////////////////////////////////
class onavsimUIDialogBase : public wxDialog
{
	private:

	protected:

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void About( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreateNavObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveNavObject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStartDriving( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStopDriving( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckNavalUnit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimer( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxButton* m_buttonHelp;
		wxButton* m_buttonCreate;
		wxButton* m_buttonRemove;
		wxButton* m_buttonStart;
		wxButton* m_buttonStop;
		wxCheckListBox* m_checkListNavalUnits;
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
/// Class UnitControlDialogBase
///////////////////////////////////////////////////////////////////////////////
class UnitControlDialogBase : public wxDialog
{
	private:

	protected:
		wxButton* m_buttonStop;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText16;
		wxStaticText* m_staticText17;
		wxStaticText* m_staticText18;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMidships( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSpeedChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMinus1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMinus10( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlus10( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPlus1( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxGauge* m_gaugeRudderPort;
		wxGauge* m_gaugeRudderStbd;
		wxSlider* m_sliderRudder;
		wxTextCtrl* m_textCtrlRudderPort;
		wxButton* m_buttonMid;
		wxTextCtrl* m_textCtrlRudderStbd;
		wxButton* m_buttonStart;
		wxStaticText* m_stHeading;
		wxStaticText* m_stSpeed;
		wxSlider* m_sliderSpeed;
		wxButton* m_buttonMinus1;
		wxButton* m_buttonMinus10;
		wxButton* m_buttonPlus10;
		wxButton* m_buttonPlus1;

		UnitControlDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~UnitControlDialogBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class NavUnitDialogBase
///////////////////////////////////////////////////////////////////////////////
class NavUnitDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText11;

	public:
		wxChoice* m_choiceNavUnitType;
		wxTextCtrl* m_textNavUnitName;
		wxStdDialogButtonSizer* m_sdbSizerNavUnit;
		wxButton* m_sdbSizerNavUnitOK;
		wxButton* m_sdbSizerNavUnitCancel;

		NavUnitDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~NavUnitDialogBase();

};


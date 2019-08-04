///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "onavsimUIDialogBase.h"

///////////////////////////////////////////////////////////////////////////

onavsimUIDialogBase::onavsimUIDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizerDateTime;
	sbSizerDateTime = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Date/Time") ), wxHORIZONTAL );

	m_staticTextDatetime = new wxStaticText( sbSizerDateTime->GetStaticBox(), wxID_ANY, _("Day"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextDatetime->Wrap( -1 );
	sbSizerDateTime->Add( m_staticTextDatetime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_datePickerDate = new wxDatePickerCtrl( sbSizerDateTime->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
	sbSizerDateTime->Add( m_datePickerDate, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_timePickerTime = new wxTimePickerCtrl( sbSizerDateTime->GetStaticBox(), wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerDateTime->Add( m_timePickerTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	sbSizerDateTime->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizerMain->Add( sbSizerDateTime, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizerControls;
	sbSizerControls = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Help") ), wxHORIZONTAL );


	sbSizerControls->Add( 5, 0, 1, wxEXPAND, 5 );

	m_button1 = new wxButton( sbSizerControls->GetStaticBox(), wxID_ANY, _("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button1->SetBackgroundColour( wxColour( 255, 255, 0 ) );

	sbSizerControls->Add( m_button1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerMain->Add( sbSizerControls, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizerDirection;
	bSizerDirection = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonStart = new wxButton( this, wxID_ANY, _("Start Driving"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonStart->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_buttonStart->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_buttonStart->SetBackgroundColour( wxColour( 0, 255, 0 ) );

	bSizer6->Add( m_buttonStart, 0, wxALL, 5 );

	m_buttonStop = new wxButton( this, wxID_ANY, _("Stop Driving"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonStop->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_buttonStop->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	m_buttonStop->SetBackgroundColour( wxColour( 255, 0, 0 ) );

	bSizer6->Add( m_buttonStop, 0, wxALL, 5 );


	bSizerDirection->Add( bSizer6, 1, wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Direction"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizerDirection->Add( m_staticText9, 0, wxALL, 5 );

	m_sliderDirection = new wxSlider( this, wxID_ANY, 0, 0, 359, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizerDirection->Add( m_sliderDirection, 0, wxALL, 5 );

	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizerDirection->Add( m_staticText10, 0, wxALL, 5 );

	m_sliderSpeed = new wxSlider( this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizerDirection->Add( m_sliderSpeed, 0, wxALL, 5 );

	m_textCtrlTest = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerDirection->Add( m_textCtrlTest, 0, wxALL, 5 );


	bSizerMain->Add( bSizerDirection, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	m_timerFrigate.SetOwner( this, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( onavsimUIDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( onavsimUIDialogBase::OnSize ) );
	m_datePickerDate->Connect( wxEVT_DATE_CHANGED, wxDateEventHandler( onavsimUIDialogBase::OnDateTimeChanged ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::About ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStartDriving ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStopDriving ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( onavsimUIDialogBase::OnTimer ) );
}

onavsimUIDialogBase::~onavsimUIDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( onavsimUIDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( onavsimUIDialogBase::OnSize ) );
	m_datePickerDate->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( onavsimUIDialogBase::OnDateTimeChanged ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::About ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStartDriving ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStopDriving ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( onavsimUIDialogBase::OnTimer ) );

}

onavsimPreferencesDialogBase::onavsimPreferencesDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 400,400 ), wxDefaultSize );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizerCheckboxes;
	bSizerCheckboxes = new wxBoxSizer( wxVERTICAL );

	m_cbUseRate = new wxCheckBox( this, wxID_ANY, _("Display tidal rates (knots)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerCheckboxes->Add( m_cbUseRate, 0, wxALL, 5 );

	m_cbUseDirection = new wxCheckBox( this, wxID_ANY, _("Display tidal direction"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerCheckboxes->Add( m_cbUseDirection, 0, wxALL, 5 );

	m_cbFillColour = new wxCheckBox( this, wxID_ANY, _("Fill Colour"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerCheckboxes->Add( m_cbFillColour, 0, wxALL, 5 );

	m_cbUseHighRes = new wxCheckBox( this, wxID_ANY, _("High Resolution Display"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerCheckboxes->Add( m_cbUseHighRes, 0, wxALL, 5 );


	bSizerMain->Add( bSizerCheckboxes, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizerColours;
	sbSizerColours = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tidal Current Arrow Colour") ), wxVERTICAL );

	wxFlexGridSizer* fgSizerColours;
	fgSizerColours = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizerColours->AddGrowableCol( 1 );
	fgSizerColours->SetFlexibleDirection( wxBOTH );
	fgSizerColours->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	staticTextLess05 = new wxStaticText( sbSizerColours->GetStaticBox(), wxID_ANY, _("      < 0.5 knots"), wxDefaultPosition, wxDefaultSize, 0 );
	staticTextLess05->Wrap( -1 );
	fgSizerColours->Add( staticTextLess05, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	myColourPicker0 = new wxColourPickerCtrl( sbSizerColours->GetStaticBox(), wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizerColours->Add( myColourPicker0, 1, wxALL|wxEXPAND, 5 );

	staticText0515 = new wxStaticText( sbSizerColours->GetStaticBox(), wxID_ANY, _(">= 0.5 and < 1.5"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText0515->Wrap( -1 );
	fgSizerColours->Add( staticText0515, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	myColourPicker1 = new wxColourPickerCtrl( sbSizerColours->GetStaticBox(), wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizerColours->Add( myColourPicker1, 1, wxALL|wxEXPAND, 5 );

	staticText1525  = new wxStaticText( sbSizerColours->GetStaticBox(), wxID_ANY, _(">= 1.5 and < 2.5"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText1525 ->Wrap( -1 );
	fgSizerColours->Add( staticText1525 , 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	myColourPicker2 = new wxColourPickerCtrl( sbSizerColours->GetStaticBox(), wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizerColours->Add( myColourPicker2, 1, wxALL|wxEXPAND, 5 );

	staticText2535 = new wxStaticText( sbSizerColours->GetStaticBox(), wxID_ANY, _(">= 2.5 and < 3.5"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText2535->Wrap( -1 );
	fgSizerColours->Add( staticText2535, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	myColourPicker3 = new wxColourPickerCtrl( sbSizerColours->GetStaticBox(), wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizerColours->Add( myColourPicker3, 1, wxALL|wxEXPAND, 5 );

	m_staticTextMore35 = new wxStaticText( sbSizerColours->GetStaticBox(), wxID_ANY, _(">= 3.5 knots    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextMore35->Wrap( -1 );
	fgSizerColours->Add( m_staticTextMore35, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	myColourPicker4 = new wxColourPickerCtrl( sbSizerColours->GetStaticBox(), wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizerColours->Add( myColourPicker4, 1, wxALL|wxEXPAND, 5 );


	sbSizerColours->Add( fgSizerColours, 1, wxEXPAND, 5 );


	bSizer4->Add( sbSizerColours, 1, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Arrow Scaling") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText8 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, _("Scale   x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer2->Add( m_staticText8, 0, wxALL, 5 );

	wxString m_cScaleChoices[] = { _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("8"), _("9"), _("10") };
	int m_cScaleNChoices = sizeof( m_cScaleChoices ) / sizeof( wxString );
	m_cScale = new wxChoice( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cScaleNChoices, m_cScaleChoices, 0 );
	m_cScale->SetSelection( 0 );
	fgSizer2->Add( m_cScale, 0, wxALL|wxEXPAND, 5 );


	sbSizer5->Add( fgSizer2, 1, wxEXPAND, 5 );


	bSizer4->Add( sbSizer5, 1, wxALL|wxEXPAND, 5 );


	bSizerMain->Add( bSizer4, 1, wxEXPAND, 5 );

	m_sdbSizerButtons = new wxStdDialogButtonSizer();
	m_sdbSizerButtonsOK = new wxButton( this, wxID_OK );
	m_sdbSizerButtons->AddButton( m_sdbSizerButtonsOK );
	m_sdbSizerButtonsCancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizerButtons->AddButton( m_sdbSizerButtonsCancel );
	m_sdbSizerButtons->Realize();

	bSizerMain->Add( m_sdbSizerButtons, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_cScale->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( onavsimPreferencesDialogBase::OnChoice ), NULL, this );
}

onavsimPreferencesDialogBase::~onavsimPreferencesDialogBase()
{
	// Disconnect Events
	m_cScale->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( onavsimPreferencesDialogBase::OnChoice ), NULL, this );

}

ControlDialogBase::ControlDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Direction"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer7->Add( m_staticText11, 0, wxALL, 5 );

	m_sliderDirection = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer7->Add( m_sliderDirection, 0, wxALL, 5 );

	m_buttonTest = new wxButton( this, wxID_ANY, _("TestControl"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_buttonTest, 0, wxALL, 5 );

	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();

	bSizer7->Add( m_sdbSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnTestControl ), NULL, this );
}

ControlDialogBase::~ControlDialogBase()
{
	// Disconnect Events
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnTestControl ), NULL, this );

}

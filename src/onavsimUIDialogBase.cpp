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

	wxStaticBoxSizer* sbSizerControls;
	sbSizerControls = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Help") ), wxHORIZONTAL );

	m_buttonHelp = new wxButton( sbSizerControls->GetStaticBox(), wxID_ANY, _("Help"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonHelp->SetBackgroundColour( wxColour( 255, 255, 0 ) );

	sbSizerControls->Add( m_buttonHelp, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerMain->Add( sbSizerControls, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizerDirection;
	bSizerDirection = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonCreate = new wxButton( this, wxID_ANY, _("Create Units"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCreate->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer8->Add( m_buttonCreate, 0, wxALL, 5 );

	m_buttonRemove = new wxButton( this, wxID_ANY, _("Remove Unit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonRemove->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer8->Add( m_buttonRemove, 0, wxALL, 5 );


	bSizerDirection->Add( bSizer8, 1, wxEXPAND, 5 );

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


	bSizerMain->Add( bSizerDirection, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	wxArrayString m_checkListNavalUnitsChoices;
	m_checkListNavalUnits = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_checkListNavalUnitsChoices, wxLB_SINGLE );
	m_checkListNavalUnits->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer9->Add( m_checkListNavalUnits, 0, wxALL|wxEXPAND, 5 );


	bSizerMain->Add( bSizer9, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	m_timerFrigate.SetOwner( this, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( onavsimUIDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( onavsimUIDialogBase::OnSize ) );
	m_buttonHelp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::About ), NULL, this );
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnCreateNavObject ), NULL, this );
	m_buttonRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnRemoveNavObject ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStartDriving ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStopDriving ), NULL, this );
	m_checkListNavalUnits->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( onavsimUIDialogBase::OnCheckNavalUnit ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( onavsimUIDialogBase::OnTimer ) );
}

onavsimUIDialogBase::~onavsimUIDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( onavsimUIDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( onavsimUIDialogBase::OnSize ) );
	m_buttonHelp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::About ), NULL, this );
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnCreateNavObject ), NULL, this );
	m_buttonRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnRemoveNavObject ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStartDriving ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( onavsimUIDialogBase::OnStopDriving ), NULL, this );
	m_checkListNavalUnits->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( onavsimUIDialogBase::OnCheckNavalUnit ), NULL, this );
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

UnitControlDialogBase::UnitControlDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -300,250 ), wxDefaultSize );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	m_gaugeRudderPort = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gaugeRudderPort->SetValue( 0 );
	bSizer13->Add( m_gaugeRudderPort, 0, wxALL, 5 );

	m_gaugeRudderStbd = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gaugeRudderStbd->SetValue( 0 );
	bSizer13->Add( m_gaugeRudderStbd, 0, wxALL, 5 );


	bSizer12->Add( bSizer13, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	m_sliderRudder = new wxSlider( this, wxID_ANY, 30, 0, 60, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer15->Add( m_sliderRudder, 0, wxALL|wxEXPAND, 5 );


	bSizer12->Add( bSizer15, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );


	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );

	m_textCtrlRudderPort = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_textCtrlRudderPort, 0, wxALIGN_CENTER|wxALL, 0 );

	m_buttonMid = new wxButton( this, wxID_ANY, _("|"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonMid, 0, wxALL, 5 );

	m_textCtrlRudderStbd = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_textCtrlRudderStbd, 0, wxALIGN_CENTER|wxALL, 0 );


	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer12->Add( bSizer14, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonStart = new wxButton( this, wxID_ANY, _("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonStart->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_buttonStart->SetBackgroundColour( wxColour( 0, 255, 64 ) );

	bSizer16->Add( m_buttonStart, 0, wxALL, 5 );

	m_buttonStop = new wxButton( this, wxID_ANY, _("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonStop->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	m_buttonStop->SetBackgroundColour( wxColour( 255, 0, 0 ) );

	bSizer16->Add( m_buttonStop, 0, wxALL, 5 );


	bSizer16->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer12->Add( bSizer16, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );


	bSizer19->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Heading:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	m_staticText12->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer19->Add( m_staticText12, 0, wxALL, 5 );

	m_stHeading = new wxStaticText( this, wxID_ANY, _("000"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stHeading->Wrap( -1 );
	m_stHeading->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer19->Add( m_stHeading, 0, wxALL, 5 );

	m_staticText14 = new wxStaticText( this, wxID_ANY, _("Speed: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	m_staticText14->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer19->Add( m_staticText14, 0, wxALL, 5 );

	m_stSpeed = new wxStaticText( this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stSpeed->Wrap( -1 );
	m_stSpeed->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer19->Add( m_stSpeed, 0, wxALL, 5 );

	m_staticText16 = new wxStaticText( this, wxID_ANY, _("         Kts"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	m_staticText16->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer19->Add( m_staticText16, 0, wxALL, 5 );


	bSizer19->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer12->Add( bSizer19, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText17 = new wxStaticText( this, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	m_staticText17->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer18->Add( m_staticText17, 0, wxALL, 5 );

	m_sliderSpeed = new wxSlider( this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxSize( 300,-1 ), wxSL_HORIZONTAL );
	bSizer18->Add( m_sliderSpeed, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );

	m_staticText18 = new wxStaticText( this, wxID_ANY, _("100"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	m_staticText18->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer18->Add( m_staticText18, 0, wxALL, 5 );


	bSizer12->Add( bSizer18, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );


	bSizer12->Add( bSizer17, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonMinus1 = new wxButton( this, wxID_ANY, _("-1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonMinus1->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer20->Add( m_buttonMinus1, 0, wxALL, 5 );

	m_buttonMinus10 = new wxButton( this, wxID_ANY, _("-10"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonMinus10->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer20->Add( m_buttonMinus10, 0, wxALL, 5 );

	m_buttonPlus10 = new wxButton( this, wxID_ANY, _("+10"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonPlus10->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer20->Add( m_buttonPlus10, 0, wxALL, 5 );

	m_buttonPlus1 = new wxButton( this, wxID_ANY, _("+1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonPlus1->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer20->Add( m_buttonPlus1, 0, wxALL, 5 );


	bSizer12->Add( bSizer20, 1, wxEXPAND, 5 );


	bSizer7->Add( bSizer12, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( UnitControlDialogBase::OnClose ) );
	m_buttonMid->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnMidships ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnButtonStart ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnButtonStop ), NULL, this );
	m_sliderSpeed->Connect( wxEVT_SLIDER, wxCommandEventHandler( UnitControlDialogBase::OnSpeedChanged ), NULL, this );
	m_buttonMinus1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnMinus1 ), NULL, this );
	m_buttonMinus10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnMinus10 ), NULL, this );
	m_buttonPlus10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnPlus10 ), NULL, this );
	m_buttonPlus1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnPlus1 ), NULL, this );
}

UnitControlDialogBase::~UnitControlDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( UnitControlDialogBase::OnClose ) );
	m_buttonMid->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnMidships ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnButtonStart ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnButtonStop ), NULL, this );
	m_sliderSpeed->Disconnect( wxEVT_SLIDER, wxCommandEventHandler( UnitControlDialogBase::OnSpeedChanged ), NULL, this );
	m_buttonMinus1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnMinus1 ), NULL, this );
	m_buttonMinus10->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnMinus10 ), NULL, this );
	m_buttonPlus10->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnPlus10 ), NULL, this );
	m_buttonPlus1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( UnitControlDialogBase::OnPlus1 ), NULL, this );

}

NavUnitDialogBase::NavUnitDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Unit type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer7->Add( m_staticText12, 0, wxALL, 5 );

	wxString m_choiceNavUnitTypeChoices[] = { _("frigate"), _("destroyer") };
	int m_choiceNavUnitTypeNChoices = sizeof( m_choiceNavUnitTypeChoices ) / sizeof( wxString );
	m_choiceNavUnitType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceNavUnitTypeNChoices, m_choiceNavUnitTypeChoices, 0 );
	m_choiceNavUnitType->SetSelection( 0 );
	bSizer7->Add( m_choiceNavUnitType, 0, wxALL, 5 );

	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Name of the unit:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer7->Add( m_staticText11, 0, wxALL, 5 );

	m_textNavUnitName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_textNavUnitName, 0, wxALL, 5 );


	bSizer7->Add( 0, 0, 1, wxEXPAND, 5 );

	m_sdbSizerNavUnit = new wxStdDialogButtonSizer();
	m_sdbSizerNavUnitOK = new wxButton( this, wxID_OK );
	m_sdbSizerNavUnit->AddButton( m_sdbSizerNavUnitOK );
	m_sdbSizerNavUnitCancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizerNavUnit->AddButton( m_sdbSizerNavUnitCancel );
	m_sdbSizerNavUnit->Realize();

	bSizer7->Add( m_sdbSizerNavUnit, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );

	this->Centre( wxBOTH );
}

NavUnitDialogBase::~NavUnitDialogBase()
{
}

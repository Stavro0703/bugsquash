/**
 * @file CodeDlg.cpp
 *
 * @author Spencer Russell
 */
#include "pch.h"
#include "CodeDlg.h"
#include "Game.h"

/**
 * Constructor for CodeDlg
 * @param code Text to set the wxTextCtrl object to display
 * @param window Pointer to the parent window
 */
CodeDlg::CodeDlg(GameView* window, std::string code) : mWindow(window), mCode(code)
{
	Create(mWindow, wxID_ANY, "Bug Squash IDE",wxDefaultPosition,wxDefaultSize);
	SetSize(0, 0, 600, 480);

	auto vsizer = new wxBoxSizer( wxVERTICAL );

	mWindow->StopStopwatch();

	Bind(wxEVT_CLOSE_WINDOW, &CodeDlg::OnClose, this, wxID_EXIT);

	mCodeText = new wxTextCtrl(this, wxID_ANY, code, wxDefaultPosition, wxDefaultSize,
							   wxNO_BORDER | wxTE_MULTILINE  | wxTE_RICH);

	mCodeText->SetMinSize(wxSize(400, 380));

	vsizer->Add(&(*mCodeText), wxSizerFlags().Border(wxALL, 10));

	wxButton* okButton = new wxButton(this, wxID_OK, "OK");

	okButton->SetMinSize(wxDefaultSize);

	// Bind an event handler to the button
	okButton->Bind(wxEVT_BUTTON, &CodeDlg::OnOK, this, wxID_ANY);

	// Add the button to the vertical sizer and set its position
	vsizer->Add(okButton, 0, wxALIGN_CENTER_HORIZONTAL, 0);

	SetSizer(vsizer);
}

/**
 * Show the Modal window for this Dialog object
 * @return int representing the ID of the way the modal was closed
 */
int CodeDlg::ShowModal()
{
	CenterOnParent();
	return wxDialog::ShowModal();
}

/**
 *Destructor for CodeDlg
 */
CodeDlg::~CodeDlg()
{
	delete mCodeText;
}
/**
 * Event to update the parent window when this wxDialog is done
 * @param event Command event triggering this modal to end
 */
void CodeDlg::OnOK(wxCommandEvent& event)
{
	mWindow->ResumeStopwatch();
	EndModal(wxID_OK);
}
/**
 * Event to update the parent window when this wxDialog closes
 * @param event Command event triggering the close
 */
void CodeDlg::OnClose(wxCloseEvent& event)
{
	mWindow->ResumeStopwatch();
	EndModal(wxID_CANCEL);
}
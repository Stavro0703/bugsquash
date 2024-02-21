/**
 * @file MainFrame.cpp
 *
 * @author Spencer Russell
 */
#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"


/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
	Create(nullptr, wxID_ANY, L"Bug Squash", wxDefaultPosition,  wxSize( 1000,800 ));

	// Create a sizer that will lay out child windows vertically
	// one above each other
	auto sizer = new wxBoxSizer( wxVERTICAL );

	// Create the view class object as a child of MainFrame
	auto gameView = new GameView();
	gameView->Initialize(this);

	// Add it to the sizer
	sizer->Add(gameView,1, wxEXPAND | wxALL );

	// Set the sizer for this frame
	SetSizer( sizer );

	// Layout (place) the child windows.
	Layout();

	auto menuBar = new wxMenuBar( );
	auto helpMenu = new wxMenu();
	auto fileMenu = new wxMenu();
	auto viewMenu = new wxMenu();
	auto levelMenu = new wxMenu();

	menuBar->Append(fileMenu, L"&File" );
	menuBar->Append(levelMenu, L"&Level");
	menuBar->Append(viewMenu, L"&View");
	menuBar->Append(helpMenu, L"&Help");

	SetMenuBar( menuBar );

	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

	helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

	levelMenu->Append(IDM_LEVEL0, "&Level 0", "Start Level 0");
	levelMenu->Append(IDM_LEVEL1, "&Level 1", "Start Level 1");
	levelMenu->Append(IDM_LEVEL2, "&Level 2", "Start Level 2");
	levelMenu->Append(IDM_LEVEL3, "&Level 3", "Start Level 3");

	viewMenu->Append(IDM_SHRINK, "&Shrink", "Shrink Screen");

	CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(L"Welcome to the Game!",
				 L"About Hornet",
				 wxOK,
				 this);
}

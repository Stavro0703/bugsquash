/**
 * @file GameApp.cpp
 *
 * @author Spencer Russell
 */
#include "pch.h"
#include "GameApp.h"
#include "Mainframe.h"

/**
 * gameapp oninit
 * @return true
 */
bool GameApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	// Add image type handlers
	wxInitAllImageHandlers();

	auto frame = new MainFrame();
	frame->Initialize();
	frame->Show(true);

	return true;
}
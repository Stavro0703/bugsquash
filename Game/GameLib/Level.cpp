/**
 * @file Level.cpp
 * @author QZH
 */
#include "pch.h"
#include "Level.h"
#include <iostream>

using namespace std;

/**
 * Begins the level by drawing the level title on the specified graphics context
 *
 * @param graphics
 */
void Level::begin(std::shared_ptr<wxGraphicsContext> graphics) {

	graphics->PushState();
	wxFont font(wxSize(0,125),wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD);
	graphics->SetFont(font,wxColour(0,0,125));
	graphics->DrawText("Level Begin",-wid/2,hit);
	Sleep(1800);

	graphics->PopState();
}

/**
 * Indicate the end of level by drawing to graphics context
 * @param graphics
 */
void Level::completed(std::shared_ptr<wxGraphicsContext> graphics) {
	graphics->PushState();
	wxFont font(wxSize(0,125),wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD);
	graphics->SetFont(font,wxColour(0,0,125));
	graphics->DrawText("Level Completed",wid,hit);
	Sleep(1800);
	graphics->PopState();
}
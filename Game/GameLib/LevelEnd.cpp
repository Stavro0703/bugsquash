/**
 * @file LevelEnd.cpp
 *
 * @author Spencer Russell
 */

#include "pch.h"
#include "LevelEnd.h"

/// The clock image
const std::wstring ClockImageName = L"clock.png";

/**
 * draw
 * @param graphics
 */
void LevelEnd::Draw(std::shared_ptr<wxGraphicsContext> graphics) {

	if(mTimeSinceInit < 1.8)
	{
		double wid = 0.0;
		double hit = 0.0;

		graphics->PushState();
		wxFont font(wxSize(0, 125), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		graphics->SetFont(font, wxColour(0, 0, 125));
		graphics->GetTextExtent(L"Level Completed", &wid, &hit);
		graphics->DrawText(L"Level Completed", Game::Width / 2 - wid / 2, Game::Height / 2 - hit / 2);
		graphics->PopState();
	}
}
/**
 * Levelend
 * @param game
 */
LevelEnd::LevelEnd(Game* game) : Item(game, ClockImageName) { mGame = game; }
/**
 * update
 * @param elapsed
 */
void LevelEnd::Update(double elapsed)
{
	mTimeSinceInit += elapsed;
	if(mTimeSinceInit >= 1.8)
		mGame->Remove(this);
}
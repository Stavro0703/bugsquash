/**
 * @file Level.cpp
 * @author QZH
 */
#include "pch.h"
#include "LevelBegin.h"

/// The clock image
const std::wstring ClockImageName = L"clock.png";

/**
 * Draw the LevelBegin
 * @param graphics The graphics context to draw on
 */
void LevelBegin::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	if(mTimeSinceInit < 1.8)
	{
		double wid = 0.0;
		double hit = 0.0;

		graphics->PushState();
		wxFont font(wxSize(0,125),wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD);
		graphics->SetFont(font,wxColour(0,0,125));
		graphics->GetTextExtent(L"Level Begin", &wid, &hit);
		graphics->DrawText("Level Begin", Game::Width/2-wid/2, Game::Height/2+hit/2);
		graphics->PopState();
	}
}
/**
 * LevelBegin
 * @param game
 */
LevelBegin::LevelBegin(Game* game) : Item(game, ClockImageName) { mGame = game; }


/**
 * update
 * @param elapsed
 */
void LevelBegin::Update(double elapsed)
{
	mTimeSinceInit += elapsed;
	if(mTimeSinceInit >= 1.8)
		mGame->Remove(this);
}

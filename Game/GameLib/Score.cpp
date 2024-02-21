/**
 * @file Score.cpp
 * @author QZH
 */
#include "pch.h"
#include "Score.h"
#include "Game.h"

///Image filenames
const std::wstring LaptopImageName = L"laptop.png";



/// Score font size to use
const int ScoreSize = 85;

/// Lable for score font size to use
const int LabelSize = 40;

/// The font color to use
const wxColour FontColor = wxColour(0, 200, 200);

/// Left score X location. The right score is
/// the width minus this value.
const int LeftScoreX = 150;

/// Score Y location
const int ScoreY = 20;

/// Score label Y location
const int ScoreLabelY = 100;

/**
 * Score constructor
 * @param game
 */
Score::Score(Game* game): Item(game, LaptopImageName )
{
	mGame = game;

}

/**
 * Draws the score to the given graphics context
 * @param gc
 */
void Score::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
	gc->PushState();

	//
	// Measuring text and drawing centered
	//
	wxFont fontLabel(LabelSize,
					 wxFONTFAMILY_SWISS,
					 wxFONTSTYLE_NORMAL,
					 wxFONTWEIGHT_BOLD);

	wxFont fontScore(ScoreSize,
					 wxFONTFAMILY_SWISS,
					 wxFONTSTYLE_NORMAL,
					 wxFONTWEIGHT_BOLD);

	gc->SetFont(fontScore, FontColor);

	double wid, hit;

	gc->GetTextExtent(std::to_string(mFixed), &wid, &hit);
	gc->DrawText(std::to_string(mFixed), LeftScoreX - wid/2, ScoreY);

	gc->GetTextExtent(std::to_string(mMissed), &wid, &hit);
	gc->DrawText(std::to_string(mMissed), Game::Width / 2 - wid/2, ScoreY);

	gc->GetTextExtent(std::to_string(mOops), &wid, &hit);
	gc->DrawText(std::to_string(mOops), Game::Width - LeftScoreX - wid/2 , ScoreY);

	gc->SetFont(fontLabel, FontColor);

	gc->GetTextExtent(L"Fixed", &wid, &hit);
	gc->DrawText("Fixed", LeftScoreX - wid/2, ScoreLabelY  + hit/2);

	gc->GetTextExtent(L"Missed", &wid, &hit);
	gc->DrawText("Missed",Game::Width / 2 - wid/2, ScoreLabelY  + hit/2);

	gc->GetTextExtent(L"Oops", &wid, &hit);
	gc->DrawText("Oops", Game::Width - LeftScoreX - wid/2 , ScoreLabelY + hit/2);

	gc->PopState();

}
/**
 * Accepts visitor for fixed score
 * @param visitor
 */
void Score::Accept(FixedScoreVisitor* visitor)
{
	mFixed++;
}
/**
 * Accepts visitor for oops score
 * @param visitor
 */
void Score::Accept(OopsScoreVisitor* visitor)
{
	mOops++;
}
/**
 * Accepts visitor for missed score
 * @param visitor
 */
void Score::Accept(MissedScoreVisitor* visitor)
{
	mMissed++;
}
/**
 * @file FeatureBug.cpp
 *
 * @author Yufan Ai
 */

#include "pch.h"
#include "FeatureBug.h"
#include "OopsScoreVisitor.h"
/// The feature sprite image
const std::wstring FeatureImageName = L"feature.png";

/// The Clicked image
const std::wstring FeatureSplatImageName = L"feature-splat.png";

/// Number of sprite images
const int FeatureNumSpriteImages = 6;


/**
 * constructor
 * @param game The game this is a member of bug
 */
FeatureBug::FeatureBug(Game *game) : Bug(game, FeatureImageName, FeatureSplatImageName,
										 FeatureNumSpriteImages)
{
	mGame = game;
}

/**
 * Override virtual function to update the Oops Score counter in game
 */
void FeatureBug::Clicked()
{
	if(!GetSplat())
	{
		SetSplat();
		OopsScoreVisitor visitor;
		mGame->Accept(&visitor);
	}
}

/**
 * Override virtual function to remove the bug but not update missed score
 */
void FeatureBug::Missed()
{
	mGame->SetNumOfBugs(mGame->GetNumOfBugs() - 1);
	mGame->Remove(this);
}
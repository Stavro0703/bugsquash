/**
 * @file Bug.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "Bug.h"
#include "Game.h"

using namespace std;

/// The bug range
const double BugHitRange = 25.0;
/// The slow multiplier
const double SlowMultiplier = .5;

/**
 * Constructor
 * @param game The bug this item is a member of
 * @param file The name of the file to display for this item
 * @param splatFile The name of the file to display splat for this item
 * @param numOfImages The number of images
 */
Bug::Bug(Game *game, const std::wstring &file, const std::wstring &splatFile, int numOfImages) : Item(game, file)
{
	mGame = game;
	std::wstring fileName = mGame->GetImagesDirectory() + L"/" + file;
	std::wstring splatFileName = mGame->GetImagesDirectory() + L"/" + splatFile;
	mBugImage = std::make_unique<wxImage>(fileName, wxBITMAP_TYPE_ANY);
	mBugSplatImage = std::make_unique<wxImage>(splatFileName, wxBITMAP_TYPE_ANY);
	mBugBitmapSplat = wxGraphicsBitmap();
	for(int i = 0; i < numOfImages - 1; i++)
	{
		mBugBitmaps.push_back(wxGraphicsBitmap());
	}
}

/**
 * Override draw function for bugs
 * @param gc
 */
void Bug::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
	if(mBugBitmaps[0].IsNull())
	{
		wxGraphicsBitmap BugBitmap = gc->CreateBitmapFromImage(*mBugImage);
		for(int i = 0; i <= mBugBitmaps.size(); i++)
		{
			if(i == mBugBitmaps.size())
				mBugBitmapStationary = gc->CreateSubBitmap(BugBitmap, 0, 100*(i+1), 100, 100);
			else
				mBugBitmaps[i] = gc->CreateSubBitmap(BugBitmap, 0, 100*i, 100, 100);
		}
		mBugBitmapSplat = gc->CreateBitmapFromImage(*mBugSplatImage);

		double dx = mProgram->GetX() - GetX();
		double dy = mProgram->GetY() - GetY();

		mFacingAngle = -std::atan2(dy, dx);
	}
	double wid = 0.0;
	double hit = 0.0;

	if(GetSplat())
	{
		wid = mBugBitmapSplat.ConvertToImage().GetWidth();
		hit = mBugBitmapSplat.ConvertToImage().GetHeight();
		gc->PushState();
		gc->Translate(GetX(), GetY());
		gc->Rotate(-mFacingAngle);
		gc->DrawBitmap(mBugBitmapSplat, -wid/2, -hit/2, wid, hit);
		gc->PopState();
		return;
	}

	wid = mBugBitmaps[mSpriteIndex].ConvertToImage().GetWidth();
	hit = mBugBitmaps[mSpriteIndex].ConvertToImage().GetHeight();
	gc->PushState();
	gc->Translate(GetX(), GetY());
	gc->Rotate(-mFacingAngle);
	gc->DrawBitmap(mBugBitmaps[mSpriteIndex], -wid/2, -hit/2, wid, hit);
	gc->PopState();
}


/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Bug::Update(double elapsed)
{
	SetTotalTime(GetTotalTime() + elapsed);

	if(GetTotalTime() > mStartTime)
	{
		double spriteChangeTime = 3.0 / mSpeed;

		mRotateTime += elapsed;

		if(mRotateTime > spriteChangeTime * 5)
		{
			mRotateTime = 0.0;
			std::uniform_real_distribution<> distributionDeltaAngle(-.4, .4);
			mDesiredDeltaAngle = distributionDeltaAngle(mGame->GetRandom());
		}

		double deltaAngle = (.1 + mRotateTime) * (mDesiredDeltaAngle);

		double dx = mProgram->GetX() - GetX();
		double dy = mProgram->GetY() - GetY();

		if(!GetSplat())
		{
			mFacingAngle += deltaAngle;

			double correctionAngle = -std::atan2(dy, dx) - mFacingAngle;

			double correctionScale = 0.3;

			if(correctionAngle > 5)
			{
				correctionAngle = 0.0;
			}

			mFacingAngle += correctionAngle * correctionScale;

		}



		if(GetSplat())
		{
			SetSpeed(0);
		}

		if(sqrt((dx) * (dx) + (dy) * (dy)) <= 20)
		{
			Missed();
		}

		mTimeChange += elapsed;
		if(mTimeChange > spriteChangeTime)
		{
			mTimeChange = 0.0;
			mSpriteIndex++;
			if(mSpriteIndex >= mBugBitmaps.size())
				mSpriteIndex = 0;
		}

		if(mSlowed)
			mSlowTime -= elapsed;

		if(mSlowTime <= 0){
			mSlowed = false;
			mSlowTime = 5.0;
		}

		double newX = 0.0;
		double newY = 0.0;

		if(mSlowed)
		{
			newX = GetX() + elapsed * GetSpeed() * SlowMultiplier * std::cos(-mFacingAngle);
			newY = GetY() + elapsed * GetSpeed() * SlowMultiplier * std::sin(-mFacingAngle);
		}
		else
		{
			newX = GetX() + elapsed * GetSpeed() * std::cos(-mFacingAngle);
			newY = GetY() + elapsed * GetSpeed() * std::sin(-mFacingAngle);
		}
		SetLocation(newX, newY);
	}
}

/**
* Handle updates for hit test
* @param x the x-axis
* @param y  y axis
* @return BugHitRange the range of hit test
*/
bool Bug::HitTest(double x, double y)
{
	double dx = x - GetX();
	double dy = y - GetY();

	return sqrt(dx * dx + dy * dy) < BugHitRange;
}

/**
 * Handle updates for loading xml
 * @param node The node need to load
 */
void Bug::XmlLoad(wxXmlNode *node)
{
	Item::XmlLoad(node);
	node->GetAttribute(L"speed", L"0").ToDouble(&mSpeed);
	node->GetAttribute(L"start", L"0").ToDouble(&mStartTime);
}

/**
 *  Handles the event of the bug being clicked by the player
 *
 */
void Bug::Clicked()
{
	if(!GetSplat()){
		mSplat = true;
		FixedScoreVisitor visitor;
		mGame->Accept(&visitor);
	}
}


/**
 * Handles the event of the bug escaping the screen without being clicked
 *
 */
void Bug::Missed()
{
	SetSpeed(0);
	MissedScoreVisitor visitor;
	mGame->Accept(&visitor);
	mGame->Remove(this);
}

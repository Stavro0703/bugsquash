/**
 * @file BugRedundancy.cpp
 * @author Stavro Polis
 */

#include "pch.h"
#include "BugRedundancy.h"
#include "Game.h"
using namespace std;
/// The bug base image
const std::wstring RedundancyFlyImageName = L"redundancy-fly-base.png";

/// The bug top image
const std::wstring RedundancyFlyTopImageName = L"redundancy-fly-top.png";

/// The left wing image
const std::wstring RedundancyFlyLeftWingImageName = L"redundancy-fly-lwing.png";

/// The right wing image
const std::wstring RedundancyFlyRightWingImageName = L"redundancy-fly-rwing.png";

/// The Clicked image
const std::wstring RedundancyFlySplatImageName = L"redundancy-fly-splat.png";

/// Wing flapping period in seconds
const double WingPeriod = .21;

/// Starting rotation angle for wings in radians
const double WingRotateStart = 0.0;

/// End rotation angle for wings in radians
const double WingRotateEnd = 1.5;

/// How many sets of wings does this bug have?
const int NumberOfSetsOfWings = 4;

/// Number of virtual pixels between each of the wing sets
const int WingSetXOffset = 12;

/// X position relative to center of bug for the first (back) wing set
const int FirstWingSetX = -36;

/// Y position relative to center of bug for the right wings. The negative
/// of this is the Y position for the left wings.
const int WingSetY = 5;

/**
 * BugRedundancy Draw Class
 * @param gc
 * */
void BugRedundancy::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
	if(mBugBitmaps[0].IsNull())
	{
		wxGraphicsBitmap BugBitmap = gc->CreateBitmapFromImage(*mBugImage);

		std::wstring fileName = mGame->GetImagesDirectory() + L"/" + RedundancyFlyTopImageName;
		std::unique_ptr<wxImage> topBugImage = std::make_unique<wxImage>(fileName, wxBITMAP_TYPE_ANY);

		fileName = mGame->GetImagesDirectory() + L"/" + RedundancyFlyLeftWingImageName;
		std::unique_ptr<wxImage> leftWingImage = std::make_unique<wxImage>(fileName, wxBITMAP_TYPE_ANY);

		fileName = mGame->GetImagesDirectory() + L"/" + RedundancyFlyRightWingImageName;
		std::unique_ptr<wxImage> rightWingImage = std::make_unique<wxImage>(fileName, wxBITMAP_TYPE_ANY);

		mBugBitmaps[0] = BugBitmap;
		mBugBitmaps[1] = gc->CreateBitmapFromImage(*topBugImage);
		mBugBitmaps[2] = gc->CreateBitmapFromImage(*leftWingImage);
		mBugBitmaps[3] = gc->CreateBitmapFromImage(*rightWingImage);
		mBugBitmapSplat = gc->CreateBitmapFromImage(*mBugSplatImage);
	}
	double wid = mBugBitmapSplat.ConvertToImage().GetWidth();
	double hit = mBugBitmapSplat.ConvertToImage().GetHeight();

	if(GetSplat())
	{
		gc->PushState();
		gc->Translate(GetX(), GetY());
		gc->Rotate(-mFacingAngle);
		gc->DrawBitmap(mBugBitmapSplat, -wid/2, -hit/2, wid, hit);
		gc->PopState();
		return;
	}

	wid = mBugBitmaps[0].ConvertToImage().GetWidth();
	hit = mBugBitmaps[0].ConvertToImage().GetHeight();

	gc->PushState();
	gc->Translate(GetX(), GetY());
	gc->Rotate(-mFacingAngle);
	gc->DrawBitmap(mBugBitmaps[0], -wid/2, -hit/2, wid, hit);
	gc->DrawBitmap(mBugBitmaps[1], -wid/2, -hit/2, wid, hit);
	gc->PopState();


	wid = mBugBitmaps[2].ConvertToImage().GetWidth();
	hit = mBugBitmaps[2].ConvertToImage().GetWidth();

	//Left wings
	for(int i = 0; i < NumberOfSetsOfWings; i++)
	{
		gc->PushState();
		gc->Translate(GetX(), GetY());
		gc->Rotate(-mFacingAngle);
		gc->Translate(FirstWingSetX + i * WingSetXOffset, WingSetY);
		gc->Rotate(-mWingAngle);
		gc->DrawBitmap(mBugBitmaps[2], -wid/2, -hit/2, wid, hit);
		gc->PopState();
	}

	wid = mBugBitmaps[3].ConvertToImage().GetWidth();
	hit = mBugBitmaps[3].ConvertToImage().GetWidth();

	//Right wings
	for(int i = 0; i < NumberOfSetsOfWings; i++)
	{
		gc->PushState();
		gc->Translate(GetX(), GetY());
		gc->Rotate(-mFacingAngle);
		gc->Translate(FirstWingSetX + i * WingSetXOffset, - WingSetY);
		gc->Rotate(mWingAngle);
		gc->DrawBitmap(mBugBitmaps[3], -wid/2, -hit/2, wid, hit);
		gc->PopState();
	}
}
/**
 * BugRedundancy update Class
 * @param elapsed
 * */
void BugRedundancy::Update(double elapsed)
{
	if(GetTotalTime() > GetStartTime())
		mWingAngle = (WingRotateEnd * std::abs(std::sin(GetTotalTime() / WingPeriod)) + WingRotateEnd);

	Bug::Update(elapsed);
}

/**
 * Constructor
 * @param game Game this bug is a member of
 */
BugRedundancy::BugRedundancy(Game *game) : Bug(game, RedundancyFlyImageName, RedundancyFlySplatImageName, 5)
{
	mGame = game;
	mWingAngle = WingRotateStart;
}
/**
 * Handles when BugRedundancy is single clicked
 *
 * */
void BugRedundancy::Clicked()
{
	if(mIsCopy)
	{
		Bug::Clicked();
	}
	else
	{
		std::uniform_real_distribution<> distributionCount(3, 6);
		int copyCount = distributionCount(mGame->GetRandom());
		std::uniform_real_distribution<> distributionDistance(0, 200);
		std::uniform_real_distribution<> distributionAngle(0, 2 * M_PI);
		double xLoc = 0.0;
		double yLoc = 0.0;
		double distance = 0.0;
		double angle = 0.0;
		for(int i = 0; i < copyCount; i++)
		{
			std::shared_ptr<BugRedundancy> copy = make_shared<BugRedundancy>(mGame);
			distance = distributionDistance(mGame->GetRandom());
			angle = distributionAngle(mGame->GetRandom());
			xLoc = GetX() + distance * std::cos(angle);
			yLoc = GetY() + distance * std::sin(angle);
			copy->SetLocation(xLoc, yLoc);
			copy->SetProgram(mProgram);
			copy->SetSpeed(GetSpeed());
			copy->SetCopy();
			mGame->Add(copy);
		}
		mGame->SetNumOfBugs(mGame->GetNumOfBugs() + copyCount - 1);
		mGame->Remove(this);
	}
}


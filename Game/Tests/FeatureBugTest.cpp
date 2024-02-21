/**
 * @file FeatureBugTest.cpp
 * @author Yufan_Ai
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Bug.h>
#include <FeatureBug.h>
#include <Game.h>

/// The feature sprite image
const std::wstring FeatureImageName = L"feature.png";

/// The Clicked image
const std::wstring FeatureSplatImageName = L"feature-splat.png";

/// Number of sprite images
const int FeatureNumSpriteImages = 6;

/** Mock class for testing the class Feature Bug */
class FeatureBugMock : public Bug {
public:
	FeatureBugMock(Game *game) : Bug(game, FeatureImageName, FeatureSplatImageName, FeatureNumSpriteImages){}
	virtual void Draw(std::shared_ptr<wxGraphicsContext> gc) override {}
};

TEST(FeatureBugTest, Construct) {
	Game game;
	FeatureBugMock Bug(&game);
}

TEST(FeatureBugTest, GettersSetters){
	Game game;
	FeatureBugMock bug(&game);

	// Test initial values
	ASSERT_NEAR(0, bug.GetX(), 0.0001);
	ASSERT_NEAR(0, bug.GetY(), 0.0001);

	// Test SetLocation, GetX, and GetY
	bug.SetLocation(600, 1100);
	ASSERT_NEAR(600, bug.GetX(), 0.0001);
	ASSERT_NEAR(1100, bug.GetY(), 0.0001);

	// Test a second with different values
	bug.SetLocation(-101.1, -500.3);
	ASSERT_NEAR(-101.1, bug.GetX(), 0.0001);
	ASSERT_NEAR(-500.3, bug.GetY(), 0.0001);
}

TEST(FeatureBugTest, HitTest) {
	// Create a bug to test
	Game game;
	FeatureBugMock bug(&game);

	// Give it a location
	// Always make the numbers different, in case they are mixed up
	bug.SetLocation(100, 200);

	// Center of the bug should be a true
	ASSERT_TRUE(bug.HitTest(100, 200));

	// Left of the bug
	ASSERT_FALSE(bug.HitTest(10, 200));

	// Right of the bug
	ASSERT_FALSE(bug.HitTest(200, 200));

	// Above the bug
	ASSERT_FALSE(bug.HitTest(100, 0));

	// Below the bug
	ASSERT_FALSE(bug.HitTest(100, 300));

	// On a fish transparent pixel
	ASSERT_FALSE(bug.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16));

}
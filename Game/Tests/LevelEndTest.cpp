/**
 * @file LevelEndTest.cpp
 * @author Yufan_Ai
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <LevelEnd.h>
#include <Item.h>
#include <Game.h>

/// The clock image
const std::wstring ClockImageName = L"clock.png";

/** Base class for testing the class LevelBegin */
class LevelEndTest : public LevelEnd {
public:
	LevelEndTest(Game* game) : LevelEnd(game)  {}
	void Draw(std::shared_ptr<wxGraphicsContext> gc) override {}
	void Update(double elapsed) {}
};

TEST(LevelEndTest, Construct) {
	Game game;
	LevelEndTest item(&game);
}

TEST(LevelEndTest, GettersSetters){
	Game game;
	LevelEndTest item(&game);

	// Test initial values
	ASSERT_NEAR(0, item.GetX(), 0.0001);
	ASSERT_NEAR(0, item.GetY(), 0.0001);

	// Test SetLocation, GetX, and GetY
	item.SetLocation(10.5, 17.2);
	ASSERT_NEAR(10.5, item.GetX(), 0.0001);
	ASSERT_NEAR(17.2, item.GetY(), 0.0001);

	// Test a second with different values
	item.SetLocation(-72, -107);
	ASSERT_NEAR(-72, item.GetX(), 0.0001);
	ASSERT_NEAR(-107, item.GetY(), 0.0001);
}

TEST(LevelEndTest, HitTest)
{
	// Create a level begin clock to test
	Game game;
	LevelEndTest LevelEnd(&game);

	// Give it a location
	// Always make the numbers different, in case they are mixed up
	LevelEnd.SetLocation(100, 200);

	// Center of the clock should be a true
	ASSERT_TRUE(LevelEnd.HitTest(100, 200));

	// Left of the clock
	ASSERT_FALSE(LevelEnd.HitTest(10, 200));

	// Right of the clock
	ASSERT_FALSE(LevelEnd.HitTest(200, 200));

	// Above the clock
	ASSERT_FALSE(LevelEnd.HitTest(100, 0));

	// Below the clock
	ASSERT_FALSE(LevelEnd.HitTest(100, 300));

	// On a clock transparent pixel
	ASSERT_FALSE(LevelEnd.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));

}
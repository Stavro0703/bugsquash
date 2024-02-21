/**
 * @file ItemTest.cpp
 * @author Yufan_Ai
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>

/// The clock image
const std::wstring ClockImageName = L"clock.png";

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
	ItemMock(Game *game) : Item(game, ClockImageName){}
	virtual void Draw(std::shared_ptr<wxGraphicsContext> gc) override {}
};

TEST(ItemTest, Construct) {
	Game game;
	ItemMock item(&game);
}


TEST(ItemTest, GettersSetters){
	Game game;
	ItemMock item(&game);

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

TEST(ItemTest, ClockTest)
{
	// Create a clock to test
	Game game;
	ItemMock clock(&game);

	// Give it a location
	// Always make the numbers different, in case they are mixed up
	clock.SetLocation(100, 200);

	// Center of the clock should be a true
	ASSERT_TRUE(clock.HitTest(100, 200));

	// Left of the clock
	ASSERT_FALSE(clock.HitTest(10, 200));

	// Right of the clock
	ASSERT_FALSE(clock.HitTest(200, 200));

	// Above the clock
	ASSERT_FALSE(clock.HitTest(100, 0));

	// Below the clock
	ASSERT_FALSE(clock.HitTest(100, 300));

	// On a clock transparent pixel
	ASSERT_FALSE(clock.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));

}
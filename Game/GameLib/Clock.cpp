/**
 * @file Clock.cpp
 * @author Kellen Lear
 */

#include "pch.h"
#include "Clock.h"
#include "Game.h"
#include "ClockVisitor.h"

/// Time in seconds between changing direction
const double DirectionTimeChange = 3.0;

/// The clock image
const std::wstring ClockImageName = L"clock.png";

/**
 * Constructor
 * @param game Game this bug is a member of
 */
Clock::Clock(Game *game) : Item(game, ClockImageName)
{
	mGame = game;
	std::uniform_real_distribution<> distributionDirection(0, 2 * M_PI);
	mDirection = distributionDirection(mGame->GetRandom());
}

/**
 * Handler for if the clock is clicked on
 */
void Clock::Clicked()
{
	ClockVisitor visitor(this);
	mGame->Accept(&visitor);
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Clock::Update(double elapsed)
{
	mTimeChange += elapsed;

	if(mTimeChange > DirectionTimeChange)
	{
		std::uniform_real_distribution<> distributionDirection(0, 2 * M_PI);
		mDirection = distributionDirection(mGame->GetRandom());
		mTimeChange = 0.0;
	}

	double newX = GetX() + elapsed * mSpeed * std::cos(mDirection);
	double newY = GetY() + elapsed * mSpeed * std::sin(mDirection);
	SetLocation(newX, newY);
}

/**
 * Load the attributes for an clock node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Clock::XmlLoad(wxXmlNode *node)
{
	Item::XmlLoad(node);
	node->GetAttribute(L"speed", L"0").ToDouble(&mSpeed);
	node->GetAttribute(L"start", L"0").ToDouble(&mTimeChange);
}
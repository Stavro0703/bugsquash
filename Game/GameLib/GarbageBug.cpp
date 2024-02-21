/**
 * @file GarbageBug.cpp
 *
 * @author Kellen Lear
 */

#include "pch.h"
#include "GarbageBug.h"
#include "Game.h"

/// The bug sprite image
const std::wstring GarbageBugSpriteImageName = L"garbagebug.png";

/// The splat image
const std::wstring GarbageBugSplatImageName = L"garbagebugsplat.png";

/// Number of sprite images
const int GarbageBugNumSpriteImages = 5;

/**
 * Constructor
 * @param game Game this bug is a member of
 */
GarbageBug::GarbageBug(Game *game) : Bug(game, GarbageBugSpriteImageName, GarbageBugSplatImageName, GarbageBugNumSpriteImages)
{

}



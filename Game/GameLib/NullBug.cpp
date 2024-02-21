/**
 * @file NullBug.cpp
 *
 * @author Spencer Russell
 */

#include "pch.h"
#include "NullBug.h"
#include "Game.h"
#include "Bug.h"

using namespace std;

///Image filenames
const std::wstring NullBugImageName = L"scarlet-gray-bug.png";

///Image filenames
const std::wstring NullBugSplatImageName = L"scarlet-gray-splat.png";

///Number of sprites
const int numSprites = 6;

/**
 * Constructor
 * @param game Game this bug is a member of
 */
NullBug::NullBug(Game* game) : Bug(game, NullBugImageName, NullBugSplatImageName, numSprites)
{
}

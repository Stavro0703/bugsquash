/**
 * @file GarbageBug.h
 *
 * @author Kellen Lear
 *
 * Garbage Bug Base Class
 */

#ifndef CSE335PROJECT1HORNET_GAME_GAMELIB_GARBAGEBUG_H
#define CSE335PROJECT1HORNET_GAME_GAMELIB_GARBAGEBUG_H
#include "Bug.h"

/** Garbage Bug Base Class */
class GarbageBug : public Bug
{
private:

public:
	/// Default constructor (disabled)
	GarbageBug() = delete;

	/// Copy constructor (disabled)
	GarbageBug(const GarbageBug &) = delete;

	/// Assignment operator
	void operator=(const GarbageBug &) = delete;

	/// Constructor
	GarbageBug(Game* game);
};

#endif //CSE335PROJECT1HORNET_GAME_GAMELIB_GARBAGEBUG_H

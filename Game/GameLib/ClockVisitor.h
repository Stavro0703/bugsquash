/**
 * @file ClockVisitor.h
 *
 * @author Spencer Russell
 *
 * Clock Visitor Base Class
 */

#ifndef GAME_GAME_GAMELIB_CLOCKVISITOR_H
#define GAME_GAME_GAMELIB_CLOCKVISITOR_H

/// Forward reference to Item class
class Item;

/** Clock Visitor Base Class */
class ClockVisitor
{
private:

public:
	/**
	 * Visit a clock object
	 * @param clock
	 */
	ClockVisitor(Item* clock) { mClock = clock; }

	/// nullptr if not clicked on
	Item* mClock = nullptr;
};

#endif //GAME_GAME_GAMELIB_CLOCKVISITOR_H

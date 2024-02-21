/**
 * @file Level.h
 * @author QZH
 *
 *
 */

#ifndef GAME_GAMELIB_LEVEL_H
#define GAME_GAMELIB_LEVEL_H

#include "Game.h"
/** levelbegin Base Class */
class LevelBegin : public Item
{
private:
	///The game object associated with this item
	Game* mGame;

	/// The number of seconds since this object was initialized
	double mTimeSinceInit = 0.0;
public:
	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	void Update(double elapsed);

	LevelBegin(Game* game);

};

#endif //GAME_GAMELIB_LEVEL_H

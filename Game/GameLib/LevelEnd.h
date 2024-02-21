/**
 * @file LevelEnd.h
 *
 * @author Spencer Russell
 */

#ifndef GAME_GAME_GAMELIB_LEVELEND_H
#define GAME_GAME_GAMELIB_LEVELEND_H

#include "Game.h"
/** levelend Base Class */
class LevelEnd : public Item
{
private:
	///The game object associated with this item

	Game* mGame;

	///mTimeSinceInit
	double mTimeSinceInit = 0.0;
public:
	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

	void Update(double elapsed);

	LevelEnd(Game* game);
};

#endif //GAME_GAME_GAMELIB_LEVELEND_H

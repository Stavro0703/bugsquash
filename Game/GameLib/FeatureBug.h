/**
 * @file FeatureBug.h
 *
 * @author Yufan Ai
 */

#ifndef GAME_GAME_GAMELIB_FEATUREBUG_H
#define GAME_GAME_GAMELIB_FEATUREBUG_H

#include "Bug.h"
#include "Game.h"

/** FeatureBug Base Class */

class FeatureBug : public Bug
{
private:
	///game object
	Game* mGame;
public:
	/// Default constructor (disabled)
	FeatureBug() = delete;

	/// Copy constructor (disabled)
	FeatureBug(const FeatureBug &) = delete;

	/// Assignment operator
	void operator=(const FeatureBug &) = delete;

	FeatureBug(Game* game);

	virtual void Clicked() override;

	virtual void Missed() override;
};

#endif //GAME_GAME_GAMELIB_FEATUREBUG_H

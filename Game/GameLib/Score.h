/**
 * @file Score.h
 * @author QZH
 *
 *
 */

#ifndef GAME_GAME_GAMELIB_SCORE_H
#define GAME_GAME_GAMELIB_SCORE_H

#include "Item.h"
#include "OopsScoreVisitor.h"

/** Score Base Class */

class Score: public Item
{
private:

	/// Number of bugs that were fixed and squashed
	int mFixed = 0;

	/// Number of bugs that reached the program
	int mMissed = 0;

	/// Number of feature bugs that were squashed
	int mOops = 0;

	///Pointer to the game object this score is a part of
	Game *mGame;
public:
	/// Default constructor (disabled)
	Score() = delete;

	/// Copy constructor (disabled)
	Score(const Score &) = delete;

	/// Assignment operator
	void operator=(const Score &) = delete;

	Score(Game* game);

	void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

	virtual void Accept(FixedScoreVisitor* visitor) override;

	virtual void Accept(OopsScoreVisitor* visitor) override;

	virtual void Accept(MissedScoreVisitor* visitor) override;
};

#endif //GAME_GAME_GAMELIB_SCORE_H

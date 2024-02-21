/**
 * @file BugRedundancy.h
 * @author Stavro
 *
 */

#ifndef CSE335PROJECT1HORNET_GAMELIB_BUGREDUNDANCY_H
#define CSE335PROJECT1HORNET_GAMELIB_BUGREDUNDANCY_H

#include "Bug.h"

/** BugRedundancy Base Class */
class BugRedundancy : public Bug
{
private:
	///game object
	Game* mGame;

	///mWingAngle
	double mWingAngle = 0.0;

	///mIsCopy
	bool mIsCopy = false;
public:
	virtual void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

	BugRedundancy(Game *Game);


	virtual void Update(double elapsed) override;


	virtual void Clicked() override;

	/**
 * SetCopy Class
 * */
	void SetCopy() { mIsCopy = true; }
};

#endif //CSE335PROJECT1HORNET_GAMELIB_BUGREDUNDANCY_H

/**
 * @file FatBug.h
 * @author QZH
 *
 */

#ifndef GAME_GAME_GAMELIB_FATBUG_H
#define GAME_GAME_GAMELIB_FATBUG_H

#include "GarbageBug.h"
#include "Game.h"

/** FatBug Base Class */
class FatBug : public Bug
{
private:
	///Game object
	Game* mGame;

	///mType
	std::string mType = "garbage";

	///mCode
	std::string mCode = "";

	///mPass
	std::string mPass = "";

	/// Image filenames
	std::wstring mFatBugImageName = L"garbagebug.png";

	/// Null bug image splat name
	std::wstring mFatBugSplatImageName = L"garbagebugsplat.png";

	/// Number of sprites
	int mFatBugNumSpriteImages = 5;

public:
	/// Default constructor (disabled)
	FatBug() = delete;

	/// Copy constructor (disabled)
	FatBug(const FatBug &) = delete;

	/// Assignment operator
	void operator=(const FatBug &) = delete;

	/// Constructor
	FatBug(Game* game);

	void SetType(std::string type) override;

	/**
 	* Setter for the code attribute
 	* @param code String to set mCode to
 	*/
	virtual void SetCode(std::string code) override { mCode = code; }

	/**
 	* Setter for the pass attribute
 	* @param pass Regular expression to set mPass to
 	*/
	virtual void SetPass(std::string pass) override { mPass = pass; }

	virtual void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

	virtual bool DoubleHitTest(double x, double y) override;

	/**
 	* Handle updates for hit test
 	* @param x the x-axis
	* @param y  the y axis
	 * @return false
 	*/
	virtual bool HitTest(double x, double y) override { return false; }
};

#endif //GAME_GAME_GAMELIB_FATBUG_H

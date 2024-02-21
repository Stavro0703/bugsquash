/**
 * @file Bug.h
 *
 * @author Stavro Polis
 */

#ifndef CSE335PROJECT1HORNET_GAMELIB_BUG_H
#define CSE335PROJECT1HORNET_GAMELIB_BUG_H

#include <wx/graphics.h>
#include <vector>
#include "Item.h"
#include "Program.h"

class Game;


/** Bug Base Class */
class Bug : public Item
{
private:

	/// Current game
	Game* mGame;

	/// Magnitude of the X and Y speeds
	double mSpeed = 100.0;

	/// Time in seconds before starting to move
	double mStartTime = 0.0;

	/// Time in seconds since the last update to the random angle change
	double mRotateTime = 0.0;

	/// The change in angle the bug will randomly move toward
	double mDesiredDeltaAngle = 0.0;

	/// Whether the bug has been clicked or not
	bool mSplat = false;

	/// All of the items to populate our bug
	std::vector<std::shared_ptr<Item>> mItems;

	/// Amount of time left while slowed
	double mSlowTime = 5.0;

	/// Whether the bug is slowed down currently
	bool mSlowed = false;

	/// Total elapsed time since initialization
	double mTotalElapsed = 0.0;
public:
	/// Default constructor (disabled)
	Bug() = delete;

	/// Copy constructor (disabled)
	Bug(const Bug &) = delete;

	/// Assignment operator
	void operator=(const Bug &) = delete;

	/// The underlying bug image
	std::unique_ptr<wxImage> mBugImage;

	/// The bitmaps we can display for this bug
	std::vector<wxGraphicsBitmap> mBugBitmaps;

	/// The bitmap we can display for this bug when stationary
	wxGraphicsBitmap mBugBitmapStationary;

	/// The underlying bug Clicked image
	std::unique_ptr<wxImage> mBugSplatImage;

	/// The bitmap for the Clicked image of the bug
	wxGraphicsBitmap mBugBitmapSplat;

	/// Index of the current sprite in run cycle
	int mSpriteIndex = 0;

	/// Current direction the bug is facing in radians
	double mFacingAngle = 0.0;

	/// Time change in milliseconds since last sprite update
	double mTimeChange = 0.0;

	/// Member program pointer
	std::shared_ptr<Program> mProgram;

	/**
	 * Override draw function for bugs
	 * @param gc
	 */
	void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

	/**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
	virtual void Update(double elapsed) override;

	/**
 	* Handle updates for set program
 	* @param program The time since the last update
 	*/
	virtual void SetProgram(std::shared_ptr<Program> program) { mProgram = program; }
	/**
 	* Handle updates for set Start timer
 	* @param time The time since the last update
 	*/
	void SetStart(double time) { mStartTime = time; }

	/**
 	* Handle updates for get total time
	* @return total elapsed time
 	*/
	double GetTotalTime() { return mTotalElapsed; }

	/**
 	* Handle updates for set total timer
 	* @param time time The time since the last update
 	*/
	void SetTotalTime(double time) { mTotalElapsed = time; }

	/**
 	* Handle updates for get start time
	* @return start elapsed time
 	*/
	double GetStartTime() { return mStartTime; }

	/**
 	* Handle updates for get speed
	* @return mSpeed total
 	*/
	double GetSpeed() { return mSpeed; }

	/**
 	* Handle updates for get speed
 	* @param speed The time since the last update
	*
 	*/
	void SetSpeed(double speed) { mSpeed = speed; }

	/**
 	* Handle updates for get speed
	* @return mSplat
 	*/
	bool GetSplat() { return mSplat; }

	/**
 	* Handle updates for get speed
 	*/
	void SetSplat() { mSplat = true; }

	/**
 	* Handle updates for click
 	*/
	virtual void Clicked();

	/**
 	* Handle updates for get speed
 	*/
	virtual void Missed();

	/**
 	* Handle updates for get speed
 	*/
	void Slow() { mSlowed = true; }

	/**
 	* Handle updates for hit test
 	* @param x the x-axis
	* @param y  y axis
	* @return BugHitRange the range of hit test
 	*/
	bool HitTest(double x, double y) override;

	/**
 	* Handle updates for loading xml
 	* @param node The node need to load
 	*/
	virtual void XmlLoad(wxXmlNode *node);

	/**
 	* Handle updates for set code
 	* @param code the code needed to be set up
 	*/
	virtual void SetCode(std::string code) {}

	/**
 	* Handle updates for set pass
 	* @param pass The string since the last update
 	*/
	virtual void SetPass(std::string pass) {}

	/**
 	* Handle updates for accept
 	* @param visitor The visitor since the last update
 	*/
	virtual void Accept(ClockVisitor* visitor) override { Slow(); }

	/**
 	* Handle updates for set type
 	* @param type The type since the last update
 	*/
	virtual void SetType(std::string type) {};

protected:
	Bug(Game *game, const std::wstring &filename, const std::wstring &splatfilename, int numOfSprites);
};

#endif //CSE335PROJECT1HORNET_GAMELIB_BUG_H

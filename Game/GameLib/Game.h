/**
 * @file Game.h
 *
 * @author Spencer Russell
 */

#ifndef GAME_GAME_GAMELIB_GAME_H
#define GAME_GAME_GAMELIB_GAME_H

#include <memory>
#include <random>
#include "Item.h"
#include "Bug.h"
#include "Program.h"
#include "ClockVisitor.h"


class GameView;

/** Game Base Class */

class Game
{
private:
	/// Pointer to the GameView this game is located in
	GameView* mWindow = nullptr;

	/// All of the bugs to populate the game
	std::vector<std::shared_ptr<Item>> mItems;

	/// Represents whether the window should be shrunk
	bool mShrinked = false;

	/// Offset x location for this game window
	double mXOffset = 0.0;

	/// Offset y location for this game window
	double mYOffset = 0.0;

	/// The scale at which the game window is being drawn at
	double mScale = 1.0;

	/// The current number of non-squashed bugs loaded
	int mNumOfBugs = 0;

	/// The current number of programs loaded
	int mNumOfPrograms = 0;

	/// Current level our game is in
	int mCurrentLevel = 0;

	/// Whether the game should be incrementing the time to change levels
	bool mIncrementTime = false;

	/// Time since a level ended or began
	double mTimeChange = 0.0;

	/// Directory containing the system images
	std::wstring mImagesDirectory;

	/// Directory containing the system images
	std::wstring mLevelsDirectory;

	/// Random number generator
	std::mt19937 mRandom;

	void RemoveItem();

	/// List of items that will be removed at next update
	std::vector<Item*> mItemsToRemove;
public:
	/// Game area width in virtual pixels
	const static int Width = 1250;

	/// Game area height in virtual pixels
	const static int Height = 1000;

	Game();

	/**
	 * Set the GameView pointer member variable for this object
	 * @param window Pointer to the window this game is in
	 */
	void SetWindow(GameView* window) { mWindow = window; }

	/**
	 * Get the pointer to the GameView object this game is in
	 * @return Pointer to the GameView object
	 */
	GameView* GetWindow() { return mWindow; }

	void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

	void Add(std::shared_ptr<Item> item);

	void SetImagesDirectory(const std::wstring &dir);

	void SetLevelsDirectory(const std::wstring &dir);

	/**
	 * Sets the current number of bugs loaded in the game
	 * @param numOfBugs The current number of bugs to set the game to
	 */
	void SetNumOfBugs(int numOfBugs) { mNumOfBugs = numOfBugs; }

	/**
	 * Get the current number of bugs loaded
	 * @return The number of bugs loaded
	 */
	int GetNumOfBugs() { return mNumOfBugs; }

	/**
	 * Get the current number of programs loaded
	 * @return The number of programs loaded
	 */
	int GetNumOfPrograms() { return mNumOfPrograms; }

	/**
	 * Setter for the current level the game is on
	 * @param currentLevel The level to set it to
	 */
	void SetCurrentLevel(int currentLevel) { mCurrentLevel = currentLevel; }

	/**
     * Get the directory the images are stored in
     * @return Images directory path
     */
	const std::wstring &GetImagesDirectory() const { return mImagesDirectory; }

	/**
     * Get the directory the images are stored in
     * @return Levels directory path
     */
	const std::wstring &GetLevelsDirectory() const { return mLevelsDirectory; }

	/**
 	* Get the random number generator
 	* @return Pointer to the random number generator
 	*/
	std::mt19937 &GetRandom() {return mRandom;}

	std::shared_ptr<Item> HitTest(double x, double y);

	std::shared_ptr<Item> DoubleHitTest(double x, double y);

	void OnLeftDown(int x, int y);

	void OnLeftDoubleClick(int x, int y);

	void Update(double elapsed);

	/**
 	* Shrink the window to see all loaded bugs offscreen
 	*/
	void Shrink() { mShrinked = !mShrinked; }

	void Clear();

	void XmlItem(wxXmlNode *node, std::shared_ptr<Program> program, std::vector<std::shared_ptr<Item>> &bugsList);

	void XmlLoad(const wxString &filename);

	void Accept(ClockVisitor* visitor);

	void Accept(FixedScoreVisitor* visitor);

	void Accept(OopsScoreVisitor* visitor);

	void Accept(MissedScoreVisitor* visitor);

	void Remove(Item* item);

	void NextLevel();
};

#endif //GAME_GAME_GAMELIB_GAME_H

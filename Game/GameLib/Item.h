/**
 * @file Item.h
 * @author Stavro
 *
 *
 */

#ifndef GAME_GAME_GAMELIB_ITEM_H
#define GAME_GAME_GAMELIB_ITEM_H

#include <wx/xml/xml.h>
#include "ClockVisitor.h"
#include "FixedScoreVisitor.h"
#include "MissedScoreVisitor.h"
#include "OopsScoreVisitor.h"

class Game;

/**
 * Base class for all objects in our game
 */
class Item
{
private:
	///The game this item is in
	Game *mGame;

	/// Item location in the game
	double  mX = 0;     ///< X location for the center of the item
	double  mY = 0;     ///< Y location for the center of the item

	/// The underlying item image
	std::unique_ptr<wxImage> mItemImage;

	/// The bitmap we can display for this item
	std::unique_ptr<wxBitmap> mItemBitmap;

protected:
	Item(Game *game, const std::wstring &filename);

public:

	/// Default constructor (disabled)
	Item() = delete;

	/// Copy constructor (disabled)
	Item(const Item &) = delete;

	/// Assignment operator
	void operator=(const Item &) = delete;

	/**
     * The X location of the item
     * @return X location in pixels
     */
	double GetX() const { return mX; }

	/**
	 * The Y location of the item
	 * @return Y location in pixels
	 */
	double GetY() const { return mY; }

	/**
	 * Set the item location
	 * @param x X location in pixels
	 * @param y Y location in pixels
	 */
	void SetLocation(double x, double y) { mX = x; mY = y; }

	double DistanceTo(std::shared_ptr<Item> item);

	virtual void Draw(std::shared_ptr<wxGraphicsContext> gc);

	virtual void Update(double elapsed);

	virtual bool HitTest(double x, double y);

	/**
	 * Set the item HitTest
	 * @param x X location in pixels
	 * @param y Y location in pixels
	 * @return false
	 */
	virtual bool DoubleHitTest(double x, double y) { return false; }

	/**
	 * Virtual Function for items that are clicked on
	 */
	virtual void Clicked() {}

	/**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
	Game *GetGame() { return mGame;  }

	virtual void XmlLoad(wxXmlNode *node);

	/**
	 * Virtual accept function for Clock Visitor
	 * @param visitor
	 */
	virtual void Accept(ClockVisitor* visitor) {}

	/**
	 * Virtual accept function for Missed score visitor
	 * @param visitor
	 */
	virtual void Accept(MissedScoreVisitor* visitor) {}

	/**
	 * Virtual accept function for oops score visitor
	 * @param visitor
	 */
	virtual void Accept(OopsScoreVisitor* visitor) {}

	/**
	 * Virtual accept function for Fixed score visitor
	 * @param visitor
	 */
	virtual void Accept(FixedScoreVisitor* visitor) {}
};

#endif //GAME_GAME_GAMELIB_ITEM_H

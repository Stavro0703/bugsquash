/**
 * @file Item.cpp
 * @author Stavro
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;


/**
 * Constructor for Item
 * @param game
 * @param file
 */
Item::Item(Game *game, const std::wstring &file) : mGame(game)
{
	std::wstring filename = mGame->GetImagesDirectory() + L"/" + file;
	mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
	mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
}

/**
 * Draw Function for items
 * @param gc
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
	double wid = mItemBitmap->GetWidth();
	double hit = mItemBitmap->GetHeight();
	gc->DrawBitmap(*mItemBitmap,
				   int(GetX() - wid / 2),
				   int(GetY() - hit / 2), wid, hit);
}

/**
 * Updates the drawn images
 * @param elapsed
 */
void Item::Update(double elapsed)
{

}

/**
 * Compute the distance from this item to another item
 * @param item Item we are computing the distance to
 * @return Distance in pixels
 */
double Item::DistanceTo(std::shared_ptr<Item> item)
{
	auto dx = item->GetX() - GetX();
	auto dy = item->GetY() - GetY();
	return sqrt(dx * dx + dy * dy);
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(double x, double y)
{
	double wid = mItemBitmap->GetWidth();
	double hit = mItemBitmap->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to the image top corner
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	// If the location is transparent, we are not in the drawn
	// part of the image
	return !mItemImage->IsTransparent((int)testX, (int)testY);
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
	node->GetAttribute(L"x", L"0").ToDouble(&mX);
	node->GetAttribute(L"y", L"0").ToDouble(&mY);
}


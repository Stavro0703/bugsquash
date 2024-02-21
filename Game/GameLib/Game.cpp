/**
 * @file Game.cpp
 *
 * @author Spencer Russell
 */

#include "pch.h"
#include "Game.h"
#include "GarbageBug.h"
#include "NullBug.h"
#include "BugRedundancy.h"
#include "FeatureBug.h"
#include "FatBug.h"
#include "Clock.h"
#include "Score.h"
#include "LevelBegin.h"
#include "LevelEnd.h"
#include <algorithm>
#include <wx/string.h>
#include <string>

using namespace std;

/// Scale to shrink to when in shrink mode
const double ShrinkScale = 0.75;

/// Initial bug X location
const int InitialX = 0;

/// Initial bug Y location
const int InitialY = -100;

/// Directory containing the project images
/// relative to the resources directory.
const std::wstring ImagesDirectory = L"/images";

/// Directory containing the project images
/// relative to the resources directory.
const std::wstring LevelsDirectory = L"/levels";

/**
 * Draw the game area
 * @param graphics The graphics context to draw on
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
	//
	// Automatic Scaling
	//
	auto scaleX = double(width) / double(Width);
	auto scaleY = double(height) / double(Height);
	mScale = std::min(scaleX, scaleY);

	if(mShrinked)
	{
		mScale *= ShrinkScale;
	}

	mXOffset = (width - Width * mScale) / 2;
	mYOffset = (height - Height * mScale) / 2;

	graphics->PushState();

	graphics->Translate(mXOffset, mYOffset);
	graphics->Scale(mScale, mScale);

	// From here on you are drawing virtual pixels


	graphics->SetBrush(*wxWHITE_BRUSH);
	graphics->DrawRectangle(0,0,Game::Width, Game::Height);
	wxFont font(wxSize(0, 20),
				wxFONTFAMILY_SWISS,
				wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_NORMAL);
	if(!mShrinked)
		graphics->Clip(0,0,Game::Width, Game::Height);

	for (auto item : mItems)
	{
		item->Draw(graphics);
	}

	graphics->PopState();



}

/**
 * Game Constructor
 */
Game::Game()
{
	// Default is the current directory (for testing)
	SetImagesDirectory(L".");
	SetLevelsDirectory(L".");

	// Seed the random number generator
	std::random_device rd;
	mRandom.seed(rd());
}

/**
* Handle a mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDown(int x, int y)
{
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;
	std::shared_ptr<Item> clickedItem = HitTest(oX, oY);
	if(clickedItem != nullptr)
	{
		clickedItem->Clicked();
	}
}

/**
* Handle a double mouse click
* @param x X location clicked on
* @param y Y location clicked on
*/
void Game::OnLeftDoubleClick(int x, int y)
{
	double oX = (x - mXOffset) / mScale;
	double oY = (y - mYOffset) / mScale;
	std::shared_ptr<Item> clickedItem = DoubleHitTest(oX, oY);
	if(clickedItem != nullptr)
	{
		clickedItem->Clicked();
	}
}


/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(double x, double y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}
	return  nullptr;
}


/**
 * Test an x,y click location to see if it double clicked
 * on some item in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::DoubleHitTest(double x, double y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
	{
		if ((*i)->DoubleHitTest(x, y))
		{
			return (*i);
		}
	}
	return nullptr;
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
	if(mIncrementTime)
		mTimeChange += elapsed;

	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
	if(!mItemsToRemove.empty())
		RemoveItem();

	if(mNumOfBugs == 0)
	{
		std::shared_ptr<LevelEnd> levelEnd = make_shared<LevelEnd>(this);
		Add(levelEnd);
		mIncrementTime = true;
		if(mTimeChange > 1.8)
			NextLevel();
	}
}

/**
 * Load the next level
 */
void Game::NextLevel()
{
	mIncrementTime = false;
	mTimeChange = 0.0;
	mCurrentLevel++;
	if(mCurrentLevel == 4)
	{
		mNumOfBugs = 1;
		return;
	}
	std::wstring filename = GetLevelsDirectory() + L"/level" + to_wstring(mCurrentLevel) + L".xml";
	XmlLoad(filename);
}

/**
 * Add an item to this Game's list of items
 * @param item
 */
void Game::Add(std::shared_ptr<Item> item)
{
	mItems.push_back(item);
}


/**
 * Set the directory the images are stored in
 * @param dir The directory path this game is in
 */
void Game::SetImagesDirectory(const std::wstring &dir) {
	mImagesDirectory = dir + ImagesDirectory;
}

/**
 * Set the directory the images are stored in
 * @param dir The directory path this game is in
 */
void Game::SetLevelsDirectory(const std::wstring &dir) {
	mLevelsDirectory = dir + LevelsDirectory;
}

/**
 * Load the game level XML file.
 *
 * Open an XML file and stream the game data to it.
 *
 * @param filename The filename of the file to save the game to
 */
void Game::XmlLoad(const wxString& filename)
{
	wxXmlDocument xmlDoc;
	if (!xmlDoc.Load(filename))
	{
		wxMessageBox(L"Unable to load levels of xml file");
		return;
	}

	Clear();

	wxXmlNode* rootNode = xmlDoc.GetRoot();
	if (rootNode->GetName() != "bug-squash")
	{
		wxMessageBox(L"Invalid level file format");
		return;
	}

	std::shared_ptr<Item> score = std::make_shared<Score>(this);
	Add(score);
	std::vector<std::shared_ptr<Item>> tempItemsList;

	// Get the XML document root node
	auto root = xmlDoc.GetRoot();

	//
	// Traverse the children of the root
	// node of the XML document in memory!!!!
	//
	auto child = root->GetChildren();
	for( ; child; child=child->GetNext())
	{
		auto name = child->GetName();
		if(name == L"program")
		{
			mNumOfPrograms++;
			shared_ptr<Program> program = make_shared<Program>(this);
			Add(program);
			program->XmlLoad(child);
			auto childProgram = child->GetChildren();
			for( ; childProgram; childProgram=childProgram->GetNext())
			{
				name = childProgram->GetName();
				if(name == "clock")
				{
					shared_ptr<Clock> clock = make_shared<Clock>(this);
					clock->XmlLoad(childProgram);
					tempItemsList.push_back(clock);
				}
				else
					XmlItem(childProgram, program, tempItemsList);
			}
		}
	}
	for(auto item : tempItemsList)
	{
		Add(item);
	}
	std::shared_ptr<LevelBegin> levelBegin = make_shared<LevelBegin>(this);
	Add(levelBegin);
}

/**
 * Clear the Game data.
 *
 * Deletes all known items in the game.
 */
void Game::Clear()
{
	mItems.clear();
	mNumOfPrograms = 0;
	mNumOfBugs = 0;
}

/**
 * Handle a node of type item.
 * @param node XML node
 * @param program
 * @param bugsList
 */
void Game::XmlItem(wxXmlNode *node, shared_ptr<Program> program, std::vector<std::shared_ptr<Item>> &itemsList){

	shared_ptr<Bug> item;
	auto type = node->GetAttribute("type");
	auto name = node->GetName();
	auto child = node->GetChildren();

	if(child != nullptr)
	{
		mNumOfBugs++;
		item = make_shared<FatBug>(this);
		item->SetProgram(program);
		item->SetPass(child->GetAttribute("pass").ToStdString());
		item->SetType(type.ToStdString());
		wxString contents = child->GetNodeContent();
		item->SetCode(contents.ToStdString());
	}
	else if(type == L"garbage"){
		mNumOfBugs++;
		item = make_shared<GarbageBug>(this);
		item->SetProgram(program);
	}
	else if(type == L"null"){
		mNumOfBugs++;
		item = make_shared<NullBug>(this);
		item->SetProgram(program);
	}
	if(type == L"redundancy"){
		mNumOfBugs++;
		item = make_shared<BugRedundancy>(this);

		item->SetProgram(program);
	}
	if(name == L"feature"){
		mNumOfBugs++;
		item = make_shared<FeatureBug>(this);
		item->SetProgram(program);
	}
	if (item != nullptr)
	{
		item->XmlLoad(node);
		itemsList.push_back(item);
	}
}


/**
 * Set an item to be removed on the next update
 * @param removeItem The item to remove from the list
 */
void Game::Remove(Item* removeItem)
{
	mItemsToRemove.push_back(removeItem);
}

/**
 * Accept a clock visitor and remove the clock object from this game
 * @param visitor The clock visitor to accept
 */
void Game::Accept(ClockVisitor* visitor)
{
	for(auto item : mItems)
	{
		item->Accept(visitor);
	}
	Remove(visitor->mClock);
}
/**
 * Accept a FixedScoreVisitor to update the fixed game score
 * @param visitor The visitor object we are accepting
 */
void Game::Accept(FixedScoreVisitor* visitor)
{
	mNumOfBugs--;
	for(auto item : mItems)
	{
		item->Accept(visitor);
	}
}
/**
 * Accept a OopsScoreVisitor to update the fixed game score
 * @param visitor The visitor object we are accepting
 */
void Game::Accept(OopsScoreVisitor* visitor)
{
	mNumOfBugs--;
	for(auto item : mItems)
	{
		item->Accept(visitor);
	}
}
/**
 * Accept a MissedScoreVisitor to update the fixed game score
 * @param visitor The visitor object we are accepting
 */
void Game::Accept(MissedScoreVisitor* visitor)
{
	mNumOfBugs--;
	for(auto item : mItems)
	{
		item->Accept(visitor);
	}
}
/**
 * Remove all the marked items from the list
 */
void Game::RemoveItem()
{
	for(auto removeItem : mItemsToRemove){
		for(auto item : mItems)
		{
			if(&(*item) == removeItem)
				mItems.erase(std::find(mItems.begin(), mItems.end(), item));
		}
	}
	mItemsToRemove.clear();
}

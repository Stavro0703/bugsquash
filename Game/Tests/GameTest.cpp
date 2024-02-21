/**
 * @file GameTest.cpp
 * @author Yufan Ai, QZH
 *
 *
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Bug.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>
#include <GarbageBug.h>
#include <FeatureBug.h>
#include <NullBug.h>
#include <BugRedundancy.h>
#include <Item.h>
#include <wx/stdpaths.h>

using namespace std;

class GameTest : public ::testing::Test {

/**
* Read a file into a wstring and return it.
* @param filename Name of the file to read
* @return File contents
*/
	wstring ReadFile(const wxString &filename)
	{
		ifstream t(filename.ToStdString());
		wstring str((istreambuf_iterator<char>(t)),
					istreambuf_iterator<char>());

		return str;
	}

protected:
/**
* Create a path to a place to put temporary files
*/
	wxString TempPath()
	{
		// Create a temporary filename we can use
		auto path = wxFileName::GetTempDir() + L"/game";
		if(!wxFileName::DirExists(path))
		{
			wxFileName::Mkdir(path);
		}

		return path;
	}
};

/**
 * Read a file into a wstring and return it.
 * @param filename Name of the file to read
 * @return File contents
 */
wstring ReadFile(const wxString &filename)
{
	ifstream t(filename.ToStdString());
	wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

	return str;
}
/**
* Test to ensure an game .aqua file is empty
*/
void TestEmpty(wxString filename)
{
	cout << "Temp file: " << filename << endl;

	auto xml = ReadFile(filename);
	cout << xml << endl;
	ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
	ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
}



TEST_F(GameTest, Construct){
	Game game;
}

/**
 * Game Test
 */
TEST_F(GameTest, HitTest) {
	Game game;

	ASSERT_EQ(game.HitTest(100, 200), nullptr) <<
	L"Testing empty bug";

	shared_ptr<GarbageBug> bug1 = make_shared<GarbageBug>(&game);
	bug1->SetLocation(100, 200);
	game.Add(bug1);

	ASSERT_TRUE(game.HitTest(100, 200) == bug1) <<
	L"Testing bug at 100, 200";
	shared_ptr<GarbageBug> bug2 = make_shared<GarbageBug>(&game);
	bug2->SetLocation(100, 200);
	game.Add(bug2);
	ASSERT_TRUE(game.HitTest(100, 200) == bug2) <<
	L"Testing the two bugs at 100, 200,";
	//set up the location to 20, 20 that returns nullptr if test where there is no image.
	ASSERT_TRUE(game.HitTest(20, 20) == nullptr) <<
	L"Testing empty game";
	ASSERT_FALSE(game.HitTest(10, 200));


	ASSERT_FALSE(game.HitTest(200, 200));


	ASSERT_FALSE(game.HitTest(100, 0));


	ASSERT_FALSE(game.HitTest(100, 300));

	ASSERT_FALSE(game.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16));

}


TEST_F(GameTest, Load) {
	// Create a game
	Game game;

	auto file2 = L"levels/level1.xml";

	game.XmlLoad(file2);

	// Check level 1
	ASSERT_EQ(1, game.GetNumOfPrograms());

	ASSERT_EQ(12, game.GetNumOfBugs());

	game.Clear();

	auto file3 = L"levels/level2.xml";

	game.XmlLoad(file3);

	// Check level 2
	ASSERT_EQ(3, game.GetNumOfPrograms());

	ASSERT_EQ(24, game.GetNumOfBugs());
}
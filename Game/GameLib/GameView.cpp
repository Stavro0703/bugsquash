/**
 * @file GameView.cpp
 *
 * @author Spencer Russell
 */

#include "pch.h"

#include <wx/stdpaths.h>

#include "ids.h"
#include "GameView.h"
#include "Bug.h"
#include "GarbageBug.h"
#include "FeatureBug.h"
#include "NullBug.h"
#include "Fatbug.h"
#include "BugRedundancy.h"
#include "Program.h"
#include "Clock.h"
#include "Score.h"



/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
	Create(parent, wxID_ANY,
		   wxDefaultPosition, wxDefaultSize,
		   wxFULL_REPAINT_ON_RESIZE);

	wxStandardPaths& standardPaths = wxStandardPaths::Get();
	std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
	mGame.SetImagesDirectory(resourcesDir);
	mGame.SetLevelsDirectory(resourcesDir);

	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &GameView::OnPaint, this);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelZero, this, IDM_LEVEL0);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOne, this, IDM_LEVEL1);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelTwo, this, IDM_LEVEL2);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelThree, this, IDM_LEVEL3);
	parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnShrink, this, IDM_SHRINK);
	Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
	Bind(wxEVT_LEFT_DCLICK, &GameView::OnLeftDClick, this);
	Bind(wxEVT_TIMER, &GameView::OnTimer, this);

	mTimer.SetOwner(this);
	mTimer.Start(FrameDuration);
	mStopWatch.Start();

	mGame.SetWindow(this);

	wxCommandEvent event;
	OnLevelOne(event);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
	// Compute the time that has elapsed
	// since the last call to OnPaint.
	auto newTime = mStopWatch.Time();
	auto elapsed = (double)(newTime - mTime) * 0.001;
	mTime = newTime;

	mGame.Update(elapsed);

	// Create a double-buffered display context
	wxAutoBufferedPaintDC dc(this);

	// Clear the image to black
	wxBrush background(*wxBLACK);
	dc.SetBackground(background);
	dc.Clear();

	// Create a graphics context
	auto gc =
		std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

	// Tell the game class to draw
	wxRect rect = GetRect();
	mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}


/**
 * Menu handler for Level>Level 0
 * @param event
 */
void GameView::OnLevelZero(wxCommandEvent& event)
{
	std::wstring fileName = mGame.GetLevelsDirectory() + L"/" + L"level0.xml";
	mGame.XmlLoad(fileName);
	mGame.SetCurrentLevel(0);
}

/**
 * Menu handler for Level>Level 1
 * @param event
 */
void GameView::OnLevelOne(wxCommandEvent& event)
{
	std::wstring fileName = mGame.GetLevelsDirectory() + L"/" + L"level1.xml";
	mGame.XmlLoad(fileName);
	mGame.SetCurrentLevel(1);
}

/**
 * Menu handler for Level>Level 2
 * @param event
 */
void GameView::OnLevelTwo(wxCommandEvent& event)
{
	std::wstring fileName = mGame.GetLevelsDirectory() + L"/" + L"level2.xml";
	mGame.XmlLoad(fileName);
	mGame.SetCurrentLevel(2);
}

/**
 * Menu handler for Level>Level 3
 * @param event
 */
void GameView::OnLevelThree(wxCommandEvent& event)
{
	std::wstring fileName = mGame.GetLevelsDirectory() + L"/" + L"level3.xml";
	mGame.XmlLoad(fileName);
	mGame.SetCurrentLevel(3);
}


/**
 * Menu handler for View>Shrink
 * @param event
 */
void GameView::OnShrink(wxCommandEvent& event)
{
	mGame.Shrink();
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
	mGame.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Event handler for a timer event
 * @param event Timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
	Refresh();
}

void GameView::OnLeftDClick(wxMouseEvent &event)
{
	mGame.OnLeftDoubleClick(event.GetX(), event.GetY());
}

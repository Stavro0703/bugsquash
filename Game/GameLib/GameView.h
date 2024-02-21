/**
 * @file GameView.h
 *
 * @author Spencer Russell
 */

#ifndef CSE335PROJECT1HORNET_GAMELIB_GAMEVIEW_H
#define CSE335PROJECT1HORNET_GAMELIB_GAMEVIEW_H

#include "Game.h"
#include "Level.h"
/**
 * gameview class
 *
 */
class GameView : public wxWindow
{
private:
	/// An object that describes our game
	Game mGame;

	/// An object that describes our level
	Level level;

	/// The timer that allows for animation
	wxTimer mTimer;

	/// Stopwatch used to measure elapsed time
	wxStopWatch mStopWatch;

	/// The last stopwatch time
	long mTime = 0;

	/// Shared pointer to the graphics context this window draws with
	std::shared_ptr<wxGraphicsContext> graphics;

public:
	void Initialize(wxFrame* parent);

	void OnPaint(wxPaintEvent& event);

	/**
     * Stop the stopwatch that updates the window
     */
	void StopStopwatch() { mStopWatch.Pause(); }

	/**
     * Resume the stopwatch to update the window
     */
	void ResumeStopwatch() { mStopWatch.Resume(); }

	/**
     * Handle updates for file save
     * @param event The event since the last update
     */
	void OnFileSaveAs(wxCommandEvent &event);

	/**
     * Handle updates for file open
     * @param event The event since the last update
     */
	void OnFileOpen(wxCommandEvent &event);

	/**
     * Handle updates for mouse move
     * @param event The event since the last update
     */
	void OnMouseMove(wxMouseEvent &event);

	/**
     * Handle updates for left up mouse move
     * @param event The event since the last update
     */
	void OnLeftUp(wxMouseEvent &event);

	/**
	 * Handle the left mouse button down event
	 * @param event
	 */
	void OnLeftDown(wxMouseEvent &event);

	/**
	 * Event handler for a timer event
	 * @param event Timer event
	 */
	void OnTimer(wxTimerEvent& event);

	void OnLevelZero(wxCommandEvent& event);

	void OnLevelOne(wxCommandEvent& event);

	void OnLevelTwo(wxCommandEvent& event);

	void OnLevelThree(wxCommandEvent& event);

	void OnShrink(wxCommandEvent& event);

	/**
     * Handle updates for loading levels
     * @param filename The file since the last update
     */
	void LoadLevel(const wxString &filename);

	/**
     * Handle updates for left double click
     * @param event The event since the last update
     */
	void OnLeftDClick(wxMouseEvent &event);
};


#endif //CSE335PROJECT1HORNET_GAMELIB_GAMEVIEW_H

/**
 * @file MainFrame.h
 *
 * @author Spencer Russell
 */

#ifndef CSE335PROJECT1HORNET_GAMELIB_MAINFRAME_H
#define CSE335PROJECT1HORNET_GAMELIB_MAINFRAME_H

/**
 * mainframe class
 *
 */
class MainFrame : public wxFrame
{
private:

public:
	void Initialize();

	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};

#endif //CSE335PROJECT1HORNET_GAMELIB_MAINFRAME_H

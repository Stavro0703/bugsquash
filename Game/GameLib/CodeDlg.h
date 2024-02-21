/**
 * @file CodeDlg.h
 *
 * @author Spencer Russell
 */

#ifndef GAME_GAME_GAMELIB_CODEDLG_H
#define GAME_GAME_GAMELIB_CODEDLG_H

#include <wx/dialog.h>
#include "GameView.h"

/** CodeDialog Base Class */
class CodeDlg : public wxDialog
{
private:
	/// The code attribute to display in the modal window
	std::string mCode = "";

	/// Pointer to the wxTextCtrl object this Dialog window will display
	wxTextCtrl* mCodeText = nullptr;

	/// Pointer to the GameView object this wxDialog is a child of
	GameView* mWindow = nullptr;
public:
	CodeDlg(GameView* window, std::string code);

	~CodeDlg();

	int ShowModal() override;


	/**
	 * Get the text from the wxTextCtrl object in this Dialog object
	 * @return
	 */
	std::string GetText() { return mCodeText->GetValue().ToStdString(); }

	void OnOK(wxCommandEvent& event);

	void OnClose(wxCloseEvent& event);
};

#endif //GAME_GAME_GAMELIB_CODEDLG_H

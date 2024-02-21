/**
 * @file Program.cpp
 * @author Kellen Lear
 */

#include "pch.h"
#include "Program.h"
#include "Game.h"

using namespace  std;
/// The Program image
const wstring LaptopImageName = L"laptop.png";


/// Program name font size/
const int ProgramNameFontSize = 18;
/**
 * Constructor
 * @param game Game this bug is a member of
 */
Program::Program(Game *game) : Item(game, LaptopImageName)
{

}

/**
 * Draw the program
 * @param gc program context to draw on
 */
void Program::Draw(std::shared_ptr<wxGraphicsContext> gc)
{
	Item::Draw(gc);
	wxFont fontlaptop(ProgramNameFontSize,
					 wxFONTFAMILY_SWISS,
					 wxFONTSTYLE_NORMAL,
					 wxFONTWEIGHT_LIGHT);
	gc->SetFont(fontlaptop, *wxWHITE);
	gc->GetTextExtent(mName, &mWidth, &mHeight);
	gc->DrawText(mName, GetX()-mWidth/2, GetY()-mHeight/2);
}

/**
 * Load the xml file
 * @param node load xml file
 */
void Program::XmlLoad(wxXmlNode *node)
{
	Item::XmlLoad(node);
	mName = node->GetAttribute(L"name", L"");
}
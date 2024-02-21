/**
 * @file Program.h
 * @author Kellen Lear
 *
 *
 */

#ifndef GAME_GAME_GAMELIB_PROGRAM_H
#define GAME_GAME_GAMELIB_PROGRAM_H

#include "Item.h"

/**
 * program file
 *
 */
class Program : public Item
{
private:
	/// string name
	std::string mName;

	/// Width of this program's text
	double mWidth = 0;
	/// Height of this program's text
	double mHeight = 0;

public:
	/// Default constructor (disabled)
	Program() = delete;

	/// Copy constructor (disabled)
	Program(const Program &) = delete;

	/// Assignment operator
	void operator=(const Program &) = delete;

	Program(Game* game);

	void XmlLoad(wxXmlNode *node);

	/**
	 * Draw the program
	 * @param gc program context to draw on
	 */
	void Draw(std::shared_ptr<wxGraphicsContext> gc) override;

};

#endif //GAME_GAME_GAMELIB_PROGRAM_H

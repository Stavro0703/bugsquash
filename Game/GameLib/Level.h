/**
 * @file Level.h
 * @author QZH
 *
 *
 */

#ifndef GAME_GAMELIB_LEVEL_H
#define GAME_GAMELIB_LEVEL_H

/** Level Base Class */

class Level
{
private:
	///width
	double wid;

	///height
	double hit;
public:
	void begin(std::shared_ptr<wxGraphicsContext> grahpics);
	void completed(std::shared_ptr<wxGraphicsContext> grahpics);

};

#endif //GAME_GAMELIB_LEVEL_H

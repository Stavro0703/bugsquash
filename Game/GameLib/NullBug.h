/**
 * @file NullBug.h
 *
 * @author Spencer Russell
 */

#ifndef CSE335PROJECT1HORNET_GAMELIB_NULLBUG_H
#define CSE335PROJECT1HORNET_GAMELIB_NULLBUG_H

#include "Bug.h"

/** NullBug Base Class */
class NullBug : public Bug
{
private:

public:
	/// Default constructor (disabled)
	NullBug() = delete;

	/// Copy constructor (disabled)
	NullBug(const NullBug &) = delete;

	/// Assignment operator
	void operator=(const NullBug &) = delete;

	/// Constructor
	NullBug(Game *game);
};

#endif //CSE335PROJECT1HORNET_GAMELIB_NULLBUG_H

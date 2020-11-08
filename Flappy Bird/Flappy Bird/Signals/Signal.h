#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <functional>
#include "SFML/System/Time.hpp"
#include "Signals_Category.h"

// Further declaration
class NodeScene;


/**
* \brief Signals are a special function, which is implicitly performed on elements of a given scene.
* 
* This works in such a way that it starts with 'root_scene', which interprets
* whether or not a given signal is intended to continue by using prepared for 
* this category. If it is intended for it, it performs on itself the function
* contained in the signal and regardless of whether the signal was intended 
* for it or not, it passes it on for all scenes pinned to it. They do the same.
*/
struct Signal
{
	/** Initializes the variables */
	Signal();

	/** It specifies what kind of work should the targeted node do */
	std::function<void(NodeScene&, sf::Time)> emit;

	/** Category of the signal */
	Signals::Category category_id;
};



#endif
/* A state where the bird hits the pipe */
#ifndef HITSTATE_H_
#define HITSTATE_H_

#include "../Bird_State.h"
#include "../../Signals/Signals_Queue.h"
#include "../../Nodes/Specified Nodes/Bird.h"


/**
* \brief This is a condition that starts when a player hits a pipe with a bird.
* 
* The player is deprived of all bird control here. The bird is 
* facing the ground and moving at high speed towards it.
*/
class HitState : public Bird_State
{
public:
	/**
	* Initializes variables.
	* @param statestack The state stack to which this state belongs.
	* @param gamedata Data to be transmitted to the states
	*/
	HitState(StateStack<Bird_State>& statestack, Game_Data gamedata);

	/** Draws this state */
	virtual void draw();

	/**
	* Updates the status of this state (informations in it)
	* @param dt The time elapsed between the previous and the new frame.
	* @return If false, this is information to stop the update on the lower layers of the stack.
	*/
	virtual bool update(sf::Time dt);

	/**
	* Handles all events for this state
	* @param event Events stored in the window.
	* @return If false, this is information to stop to handle events on the lower layers of the stack.
	*/
	virtual bool handleEvent(const sf::Event& event);

private:
	/** Reference of the pointer to the object of the bird, which the player controls.*/
	Bird*& thePlayer;
};


#endif

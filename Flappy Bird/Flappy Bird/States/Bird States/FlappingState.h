/* A state where the bird is "jumping" by the user */
#ifndef FLAPPINGSTATE_H_
#define FLAPPINGSTATE_H_

#include "../Bird_State.h"
#include "../../Signals/Signals_Queue.h"
#include "../../Nodes/Specified Nodes/Bird.h"
#include "../../Nodes/Specified Nodes/Score.h"

/**
* \brief The state of play when the player controls the bird.
* 
* In this state gravity acts on the bird and notoriously pushes
* it down. The player can interact with the bird and "flap" it.
*/
class FlappingState : public Bird_State
{
public:
	/**
	* \brief It prepares the interactive part of the game, in which the player fights for the score.
	* 
	* It sends a signal to the pipe generator to start working. 
	* It also sets the position where the result is displayed. 
	* It also initializes the variables.
	* @param statestack The state stack to which this state belongs.
	* @param gamedata Data to be transmitted to the states
	*/
	FlappingState(StateStack<Bird_State>& statestack, Game_Data gamedata);
	
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
	/** Pointer to the signal queue. */
	Signals_Queue* _queue;

	/** Reference of the pointer to the object of the bird, which the player controls.*/
	Bird*& bird;

	/** Button used to make the bird flap. */
	sf::Keyboard::Key flap_key = sf::Keyboard::Space;

	/** An object that displays the player's current score. */
	Score score_displayer;

};

#endif
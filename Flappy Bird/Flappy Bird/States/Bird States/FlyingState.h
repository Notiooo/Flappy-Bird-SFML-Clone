/** A state where bird is flying and waiting for user interaction */
#ifndef FLYINGSTATE_H_
#define FLYINGSTATE_H_

#include "../Bird_State.h"
#include "../../Signals/Signals_Queue.h"
#include "../../Nodes/Specified Nodes/Bird.h"

/**
* \brief The state in which the bird is waiting in 
*			the air for the player's first flap.
* 
* In this state, incoming pipes are not yet generated. 
* The bird flies up and down and the screen shows 
* instructions on how to make the first jump, and
* waits for interaction with the player.
*/
class FlyingState : public Bird_State
{
public:
	/**
	* Loads necessary textures and initializes variables.
	* @param statestack The state stack to which this state belongs.
	* @param gamedata Data to be transmitted to the states
	*/
	FlyingState(StateStack<Bird_State>& statestack, Game_Data gamedata);

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

	/** Button used to make the player's first flap. */
	sf::Keyboard::Key flap_key = sf::Keyboard::Space;

	/** Image telling the player to prepare for the game*/
	sf::Sprite get_ready;

	/** Image with instructions on how to interact with the bird.*/
	sf::Sprite instructions;

	/* Sinus function interval. (PI) */
	float the_interval = -3.14159265f;

	/** What is the amplitude of the sinus on which the bird moves. */
	float flyingRange = 10;

};


#endif
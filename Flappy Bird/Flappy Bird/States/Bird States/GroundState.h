/* A state where the bird actually falls to the ground */
#ifndef GROUNDSTATE_H_
#define GROUNDSTATE_H_

#include "../Bird_State.h"
#include "../../Signals/Signals_Queue.h"
#include "../../Nodes/Specified Nodes/Bird.h"

#include "SFML/System/Clock.hpp"

/**
* \brief This is the condition in which the bird hit the ground.
* 
* In this state the player cannot control the bird. This state 
* displays "Game Over", and waits a few seconds after which it
* changes State to "ScoreState".
*/
class GroundState : public Bird_State
{
	public:
		/**
		* It loads the necessary texture and sets the "game over" sign.
		* @param statestack The state stack to which this state belongs.
		* @param gamedata Data to be transmitted to the states
		*/
		GroundState(StateStack<Bird_State>& statestack, Game_Data gamedata);

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
		/** Window to which we render the image / display the game */
		sf::RenderWindow& window;

		/** Reference of the pointer to the object of the bird, which the player controls.*/
		Bird*& thePlayer;

		/** A clock that measures the time that is used to determine the duration of this state*/
		sf::Clock clock;
		
		/** Image with the text "Game Over".*/
		sf::Sprite game_over;
};


#endif // !GROUNDSTATE_H_

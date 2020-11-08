#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_
/* A state of paused game */

#include "../Application_State.h"
#include "SFML/Graphics/Text.hpp"
#include "../../Resources/Resources.h"
#include "../../Resources/ResourceManager.h"


/**
* \brief A state that allows the player to stop the game
*			and then resume it again or leave the game.
* 
* This state is rather superimposed on other states. 
* It draws a semi-transparent and dark colour on the screen, 
* and displays information about the game state and how to get out.
* 
* It also blocks the states that have been superimposed underneath it,
* so that time does not flow in the game.
*/
class PauseState : public Application_State
{
public:
	/**
	* Initializes variables and prepares a graphical pause screen scene.
	* @param state The state stack to which this state belongs.
	* @param game_data Data to be transmitted to the states
	*/
	PauseState(StateStack<Application_State>& state, Game_Data game_data);

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
		/** A message that is displayed during a paused game. */
		sf::Text pause_message;

		/** Big "Paused" text during a paused game.*/
		sf::Text paused;

		/** Window to which we render the image / display the game */
		sf::RenderWindow& window;

		/** The manager that holds the fonts */
		FontManager& fonts;
};

#endif
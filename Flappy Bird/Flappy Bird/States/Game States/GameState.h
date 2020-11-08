#ifndef GAMESTATE_H_
#define GAMESTATE_H_
/** A state where the actual game starts */

#include "../Application_State.h"
#include "../../World.h"
#include "../StateStack.h"
#include "../Bird_State.h"

/**
* \brief The target game that the player can interact with and have fun.
* 
* The whole mechanics of the game takes place here. The game world and
* its objects are kept in this state. There is also another StateStack 
* here which controls flow of states of the bird.
*/
class GameState : public Application_State
{
public:
	/**
	* \brief Initializes variables and prepares the game state.
	* 
	* It loads fonts, also loads states to the StateStack bird,
	* which is controlled by the player. It sets the default state
	* of the StateStack of the bird to "Flying".
	*
	* @param stack The state stack to which this state belongs.
	* @param game_data Data to be transmitted to the states
	*/
	GameState(StateStack<Application_State>& stack, Game_Data game_data);

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

	/** 
	* Loads the fonts used inside this state 
	* @param fonts The font manager to which we load the fonts
	*/
	void loadFonts(FontManager& fonts);

private:
	/** The whole game world with all objects and scenes*/
	World world;

	/** Pointer to the object of the bird, which the player controls.*/
	Bird* thePlayer;

	/** The state stack for the bird behaviour */
	StateStack<Bird_State> state_Bird;
};



#endif
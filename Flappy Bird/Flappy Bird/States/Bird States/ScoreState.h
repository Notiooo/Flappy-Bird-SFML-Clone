/* A state to display the score */
#ifndef SCORESTATE_H_
#define SCORESTATE_H_

#include "../Bird_State.h"
#include "../../Signals/Signals_Queue.h"
#include "../../Nodes/Specified Nodes/Bird.h"
#include "SFML/Graphics/Text.hpp"

/**
* \brief In this state, the score that the player has achieved is displayed.
* 
* It is also given the opportunity to play the game again by clicking any button.
*/
class ScoreState : public Bird_State
{
public:
	/**
	* \brief Initializes variables and prepares the player's score
	*
	* It chooses after the player's score which medal should be
	* displayed to him. It composes the whole scene with the
	* result that the player has got.
	*
	* @param statestack The state stack to which this state belongs.
	* @param gamedata Data to be transmitted to the states
	*/
	ScoreState(StateStack<Bird_State>& statestack, Game_Data gamedata);

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

	/** The manager that holds the fonts */
	FontManager& fonts;

	/** Reference of the pointer to the object of the bird, which the player controls.*/
	Bird*& thePlayer;

	/** The image of the scoreboard displayed after a player has lost. */
	sf::Sprite score_panel;

	/** The image of the medal that was assigned to the player (if any).*/
	sf::Sprite the_medal;

	/** The score the player scored during this game*/
	sf::Text score_text;

	/** The best score that a player has scored since the beginning of the whole game (stored as text)*/
	sf::Text best_score;

	/** The best score that a player has scored since the beginning of the whole game (stored as number) */
	static int best_result;



};


#endif

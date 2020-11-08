#ifndef TITLESTATE_H_
#define TITLESTATE_H_
/* A state when the game is loading */

#include "SFML/Graphics/Sprite.hpp"

#include "../Application_State.h"
#include <vector>
#include <memory>
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/Texture.hpp"

/**
* \brief A state displaying animated image of the creator
* 
* This state is pushed only at beginning of the program,
* as a kind of representation of the author. It displays
* an animated image for few seconds, and then it moves
* to the Game State.
*/

class TitleState : public Application_State
{
	public:
		/**
		* Initializes variables and extracts individual frames 
		* from the spritesheet and pushes them into the "background" vector.
		* @param stack The state stack to which this state belongs.
		* @param game_data Data to be transmitted to the states
		*/
		TitleState(StateStack<Application_State>& stack, Game_Data game_data);

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
		/** A clock used to count the time between animated frames. */
		sf::Clock clock_draw;

		/** Clock used to count down the time to change state.*/
		sf::Clock clock_update;

		/** Window to which we render the image / display the game */
		sf::RenderWindow& window;

		/** Vector of all frames of animated graphics displayed during this state. */
		std::vector<sf::Sprite> background;

		/** Graphics holding a spritesheet with all animation frames of this state. */
		sf::Texture background_tex;

		/** How quickly the frames of an animated image change. */
		float image_change_interval = 0.1f;
};

#endif TITLESTATE_H_
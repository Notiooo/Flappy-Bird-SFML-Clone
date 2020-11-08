#ifndef BIRD_STATE_H_
#define BIRD_STATE_H_

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "States_List.h"
#include "../Resources/ResourceManager.h"
#include "../Resources/Resources.h"

#include "General_State.h"

#include "../Signals/Signals_Queue.h"

#include "StateStack.h"

// Further declaration
class Bird;

// Further declaration
namespace sf
{
	class RenderWindow;
}


/**
* \brief State of bird behaviour.
* 
* This state allows to control behaviour of a specific in-game object.
* Fully developed to break down the bird's behaviour into individual parts.
* In-game bird has a specific flow, for example:
* 1) It starts with Flying State waiting for user input
* 2) As it gets input it switches to Flapping State that applies gravity
*	 and allows player to "flap" the bird with another click.
* 3) It can now go to Hit State -- when it hit a pipe, or go to Ground State --
*	 when it hits ground. Both states take away the player's ability to control
*	 the bird. The state of impact additionally forces the bird to fall down 
*	 and go to Ground State.
* 4) Ground State displays game over, and after a while switches to Score State
* 5) In Score State it displays the score, and wait for player input so it can
*	 restart the game.
* 
* @warning It is created inside GameState, so actually the main StateStack created
*		in window class still controls the whole application with this stack itself.
*		It means if there is Application_State pushed onto the stack it has the priority.
*/
class Bird_State : virtual protected General_State<Bird_State>
{
	public:
		/** 
		* Type we should use in context of States. 
		* This is essential for an inheritance from the General_State class. 
		*/
		typedef std::unique_ptr<Bird_State> Pointer;

		/** 
		* Informations we want to send through states of the stack 
		* This struct is used to generate the StateStack template function.
		*/
		struct Game_Data
		{
			/** Initializes all data we want to transfer to the states in the stack. */
			Game_Data(sf::RenderWindow& window, Signals_Queue& queue, FontManager& fonts, Bird*& bird);

			/** Window we draw image into*/
			sf::RenderWindow* window;

			/** Font holder that holds fonts to use*/
			FontManager* fonts;

			/** Pointer to queue of signals*/
			Signals_Queue* queue;

			/** Reference to pointer to the object of the bird, which the player controls.*/
			Bird*& thePlayer;
		};

		/**
		* Initializes variables and loads the textures needed in this stack.
		* @param stack The state stack to which this state belongs.
		* @param game_data Data to be transmitted to the states
		*/
		Bird_State(StateStack<Bird_State>& stack, Game_Data game_data);

		/** Declared for the purpose of correct implementation of the inheritance*/
		virtual ~Bird_State();


		// ==== Typical SFML cyclic functions ==== //

		/**
		* Updates the status of this state
		* @param dt The time elapsed between the previous and the new frame.
		* @return If false, this is information to stop the update on the lower layers of the stack.
		*/
		virtual bool update(sf::Time dt) = 0;

		/** Draws this state */
		virtual void draw() = 0;

		/**
		* Handles all events for this state
		* @param event Events stored in the window.
		* @return If false, this is information to stop to handle events on the lower layers of the stack.
		*/
		virtual bool handleEvent(const sf::Event& event) = 0;

		// ==== End of typical SFML cyclic functions ==== //

		/** Loads the textures used inside this state of the stack. */
		void loadTextures();


	protected:

		/** @return Informations that those states store for all states */
		Game_Data getGameData() const;

		/** The manager that holds the textures */
		TextureManager textures;

		/** Window to which we render the image / display the game */
		sf::RenderWindow& window;

		/** The camera we look through at the game*/
		sf::View camera;

	private:
		/** Informations we want to send through states of the stack */
		Game_Data game_data;

};


#endif
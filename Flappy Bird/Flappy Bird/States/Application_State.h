#ifndef APPLICATION_STATE_H_
#define APPLICATION_STATE_H_

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "States_List.h"
#include "../Resources/Resources.h"
#include "General_State.h"

#include "StateStack.h"


// Further declaration for RenderWindow (it is enough as there is only a pointer here)
namespace sf
{
	class RenderWindow;
}

/**
* \brief Application that controls flow of the game
* 
* Main application state. Allows to switch between the states you would expect 
* in the application itself. This are not related with game itself, but this is 
* a state more related to the application, which only mediates with the game.
* 
* For example: it won't control behaviour of the bird itself - as it is
* game object. But it allows us to control behaviour of the application.
* Go from Title Screen to Game Screen, then to Menu, and also pause a game.
* 
* It passes further RenderWindow, TextureManager and FontManager.
*/
class Application_State : virtual protected General_State<Application_State>
{
	public:
		/**
		* Type we should use in context of States.
		* This is essential for an inheritance from the General_State class.
		*/
		typedef std::unique_ptr<Application_State> Pointer;

		/**
		* Informations we want to send through states of the stack
		* This struct is used to generate the StateStack template function.
		*/
		struct Game_Data
		{
			/** Initializes all data we want to transfer to the states in the stack. */
			Game_Data(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts);

			/** Window we draw image into*/
			sf::RenderWindow* window;

			/** Texture Holder that holds textures to use*/
			TextureManager* textures;

			/** Font holder that holds fonts to use*/
			FontManager* fonts;
		};

		/**
		* Initializes variables.
		* @param stack The state stack to which this state belongs.
		* @param game_data Data to be transmitted to the states
		*/
		Application_State(StateStack<Application_State>& stack, Game_Data game_data);

		/** Declared for the purpose of correct implementation of the inheritance*/
		virtual ~Application_State();


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


	protected:
		/** @return Informations that those states store for all states */
		Game_Data getGameData() const;

	private:
		/** Informations we want to send through states of the stack */
		Game_Data game_data;

};


#endif
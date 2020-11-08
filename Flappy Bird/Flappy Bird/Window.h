/** This file is everything that is related to the window application - for example handle exit buttons, resizing the window etc. */
#ifndef WINDOW_H_
#define WINDOW_H_

#include <fstream>

#include "Resources/ResourceManager.h"

#include "Resources/Resources.h"

#include "States/StateStack.h"
#include "States/Application_State.h"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"

/**
 * A window where the game should be displayed.
 *
 * The window deals with displaying the game. 
 * It does not manage anything related to the game gameplay itself, 
 * and its maximum interference with the game itself is displaying
 * the StateStack, and loading states used in the StateStack.
 * 
 * It also holds Manager for Texture and Fonts -- so they can be used
 * anywhere inside the window.
 */
class Window
{
public:
	/**
	* \brief It prepares the window for proper operation.
	* 
	* In its current form, it creates a window with a resolution
	* of 432 x 768 and sets the window positions to the top left of
	* the screen. It also loads the states to the state and sets the
	* window icon. It applies a lock of 60 frames per second. 
	* Initializes most variables.
	*/
	Window();

	/** Properly closes the log file */
	~Window();

	/**
	* \brief It launches the main processes of the game, which last for the entire duration of the game.
	* 
	* It calls functions that process inputs and update the game state.
	* Calculates the correct time between frames and generates game status
	* updates no faster than 60 times per second. It also controls the state
	* of the game and closes the window when the game is finished.
	*/
	void run();

private:

	/** 
	* \brief Process inputs passed to the window 
	* 
	* This is a function that poll all events from the window,
	* then it passes them in to the statestack
	*/
	void processInput();

	/** 
	* \brief Updates everything related to the game/window 
	* 
	* In its current form, it passes deltatime to statestack
	* and calls its update(). It also takes care of receiving 
	* the logs and writing them to the logs.txt file.
	* 
	* @param dt The time elapsed between the previous and the new frame.
	*/
	void update(sf::Time dt);

	/** 
	* \brief Renders everything related with displaying to the window 
	* 
	* In its current form it cleans the window preparing it for a new frame,
	* and draws the result of the statestack drawing on the window.
	* The whole effect is displayed.
	*/
	void render();

	/** 
	* \brief Loads all possible states in game, so StateStack can use them
	* 
	* It loads all states into the StateStack so that a new class object
	* can be created from them only by passing on the appropriate state identifier.
	*/
	void loadStates();

	/** Time for frame - for example 1/60 of second will give us max 60 frame per second */
	static const sf::Time TimePerFrame;

	/** Window to which we render the image / display the game */
	sf::RenderWindow window;

	/** The manager that will hold the textures */
	TextureManager textures;

	/** The manager that will hold the fonts */
	FontManager font;

	/** Simpler version of Finite State Machine called State Stack (works like std::stack)*/
	StateStack<Application_State> statestack;

	/** A file used to contain logs of the game */
	std::ofstream log_file;

};

#endif WINDOW_H_
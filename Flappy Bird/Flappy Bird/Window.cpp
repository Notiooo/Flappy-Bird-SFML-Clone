#include "Window.h"

#include "States/States_List.h"
#include "States/Application_State.h"

// ICON
#include "bird_ico.c"

// GAME STATES
#include "States/Game States/GameState.h"
#include "States/Game States/PauseState.h"
#include "States/Game States/TitleState.h"

Window::Window():
	window(sf::VideoMode(144, 256), "Flappy Bird", sf::Style::Close),
	textures(),
	font(),
	statestack(Application_State::Game_Data(window, textures, font)),
	log_file("logs.txt")
{
	//...
	window.setFramerateLimit(60);

	// makes the window bigger
	window.setSize({ 144 * 3, 256 * 3 });

	// sets window to the left up corner
	window.setPosition({0, 0});

	loadStates();
	//statestack.pushState(States::ID::Title);
	statestack += States::ID::Title;

	window.setIcon(gimp_image.width, gimp_image.height, gimp_image.pixel_data);
}

Window::~Window()
{
	log_file.close();
}

const sf::Time Window::TimePerFrame = sf::seconds(1.f / 60.f);

void Window::run()
{
	sf::Clock clock;
	sf::Time timePassed = sf::Time::Zero;

	while (window.isOpen())
	{
		timePassed += clock.restart();

		// We want specified amount of frames per second
		// so we won't "update" the gameplay more than 60 times
		// per second
		while (timePassed > TimePerFrame)
		{
			timePassed -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			if (statestack.isEmpty())
				window.close();
		}
		render();
	}
}

void Window::processInput()
{
	sf::Event event;
	
	// Poll the event -- it means pull all the informations passed to the
	// window by the user, for example key press
	while (window.pollEvent(event))
	{
		// the event is passed to the stack so it can be send
		// to all object in the game
		statestack.handleEvent(event);


		// the only event type we care about in SPECIFIC WINDOW CLASS
		// is the closing window event -- otherwise we would make this
		// function way too big
		if (event.type == sf::Event::Closed)
			window.close();

	}
}

void Window::update(sf::Time dt)
{
	// actually statestack is the only thing we should update in our
	// main, and big class
	statestack.update(dt);

	// It takes log from the stack and print them to the logs.txt
	std::string log = statestack.getLogs();
	if(!log.empty())
		log_file << log << std::endl;
	
}

void Window::render()
{
	// clear the window, so there are no previous frames
	window.clear();

	// draw all objects on the stack
	statestack.draw();

	window.setView(window.getDefaultView());
	window.display();
}

void Window::loadStates()
{
	// GAME STATES
	statestack.loadState<GameState>(States::ID::Game);
	statestack.loadState<PauseState>(States::ID::Pause);
	statestack.loadState<TitleState>(States::ID::Title);


}

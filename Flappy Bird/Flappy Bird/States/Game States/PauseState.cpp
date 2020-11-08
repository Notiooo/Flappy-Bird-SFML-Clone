#include "PauseState.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

PauseState::PauseState(StateStack<Application_State>& stack, Game_Data game_data) :
	Application_State(stack, game_data), General_State(stack),
	window(*game_data.window),
	fonts(*game_data.fonts)
{
	sf::Vector2f theViewSize = window.getView().getSize();

	// The message to close the game
	pause_message.setString("Press ENTER\nto close the game");
	pause_message.setFont(fonts.get_resource(Resources::Flappy_Font));
	pause_message.setCharacterSize(10);
	pause_message.setOrigin(pause_message.getLocalBounds().width / 2, pause_message.getLocalBounds().height / 2);
	pause_message.setPosition(window.getView().getCenter());

	// PAUSED label
	paused.setString("PAUSED");
	paused.setFont(fonts.get_resource(Resources::Flappy_Font));
	paused.setCharacterSize(32);
	paused.setOrigin(paused.getLocalBounds().width / 2, paused.getLocalBounds().height / 2);
	paused.setPosition(theViewSize.x / 2, theViewSize.y / 4);



}

void PauseState::draw()
{
	sf::RectangleShape darkerScreen;
	darkerScreen.setFillColor(sf::Color(0,0,0,135));
	darkerScreen.setSize(window.getView().getSize());

	window.draw(darkerScreen);
	window.draw(pause_message);
	window.draw(paused);
	
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			requestStackClear();
		}
		else
		{
			requestStackPop();
		}
	}

	return false;
}

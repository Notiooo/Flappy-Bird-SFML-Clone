#include "TitleState.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

TitleState::TitleState(StateStack<Application_State>& stack, Game_Data game_data):
	Application_State(stack, game_data), General_State(stack),
	window(*game_data.window)
{
	background_tex.loadFromFile("Media/Textures/TitleScreen.png");
	int background_x = window.getView().getSize().x;
	int background_y = window.getView().getSize().y;

	for (int i = 0; i < 4; ++i)
	{
		background.push_back(sf::Sprite(background_tex, sf::IntRect(background_x * i, 0, background_x, background_y)));
	}

}

void TitleState::draw()
{
	static auto beg = background.cbegin();
	static auto end = background.cend();
	float timePassed = clock_draw.getElapsedTime().asSeconds();

	if (timePassed> image_change_interval)
	{
		++beg;
		clock_draw.restart();
	}

	if (beg == end)
		beg = background.cbegin();

	window.draw(*beg);
}

bool TitleState::update(sf::Time dt)
{
	if (clock_update.getElapsedTime().asSeconds() > 4)
	{
		requestStackPop();
		requestStackPush(States::ID::Game);
	}
	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	return true;
}

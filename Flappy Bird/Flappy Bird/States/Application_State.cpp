#include "Application_State.h"
#include "StateStack.h"

Application_State::Game_Data::Game_Data(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts):
	window(&window),
	textures(&textures),
	fonts(&fonts)
{
}

Application_State::Application_State(StateStack<Application_State>& stack, Game_Data game_data):
	General_State<Application_State>(stack),
	game_data(game_data)
{
}

Application_State::~Application_State()
{
}


Application_State::Game_Data Application_State::getGameData() const
{
	return game_data;
}



#include "Bird_State.h"
#include "StateStack.h"
#include "SFML/Graphics/RenderWindow.hpp"


Bird_State::Game_Data::Game_Data(sf::RenderWindow& window, Signals_Queue& queue, FontManager& fonts, Bird*& bird):
	queue(&queue),
	window(&window),
	thePlayer(bird),
	fonts(&fonts)
{
}

Bird_State::Bird_State(StateStack<Bird_State>& stack, Game_Data game_data):
	General_State<Bird_State>(stack),
	game_data(game_data),
	window(*game_data.window),
	textures(),
	camera(window.getDefaultView())

{
	loadTextures();
}

Bird_State::~Bird_State()
{
}


void Bird_State::loadTextures()
{
	/*
	textures.load_resource(Resources::Get_Ready_Label, "Media/Textures/GUI/label_get_ready.png");
	textures.load_resource(Resources::Instructions, "Media/Textures/GUI/instructions.png");
	*/
	/*
	textures.load_resource(Resources::Panel_Score, "Media/Textures/GUI/panel_score.png");
	textures.load_resource(Resources::Medal_Bronze, "Media/Textures/GUI/medal_bronze.png");
	textures.load_resource(Resources::Medal_Gold, "Media/Textures/GUI/medal_gold.png");
	textures.load_resource(Resources::Medal_Platinum, "Media/Textures/GUI/medal_platinum.png");
	textures.load_resource(Resources::Medal_Silver, "Media/Textures/GUI/medal_silver.png");
	*/
}

Bird_State::Game_Data Bird_State::getGameData() const
{
	return game_data;
}



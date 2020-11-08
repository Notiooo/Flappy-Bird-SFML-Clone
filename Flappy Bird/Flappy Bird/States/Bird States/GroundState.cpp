#include "GroundState.h"

GroundState::GroundState(StateStack<Bird_State>& statestack, Game_Data gamedata):
	Bird_State(statestack, gamedata), General_State(statestack),
	thePlayer(gamedata.thePlayer),
	window(*gamedata.window)
{
	clock.restart();
	textures.load_resource(Resources::Textures::Game_Over_Label, "Media/Textures/GUI/label_game_over.png");


	game_over.setTexture(textures.get_resource(Resources::Textures::Game_Over_Label));
	game_over.setOrigin(game_over.getLocalBounds().width / 2, game_over.getLocalBounds().height / 2);
	game_over.setPosition(camera.getSize().x / 2, camera.getSize().y / 4);
}

void GroundState::draw()
{
	/* Nothing */
	window.draw(game_over);
	
}

bool GroundState::update(sf::Time dt)
{
	if (clock.getElapsedTime().asSeconds() > 2)
	{
		requestStackPop();
		requestStackPush(States::ID::Score);
	}
	return true;
}

bool GroundState::handleEvent(const sf::Event& event)
{
	/* nothing */
	return true;
}

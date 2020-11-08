#include "GameState.h"

// BIRD STATES
#include "../Bird States/FlappingState.h"
#include "../Bird States/FlyingState.h"
#include "../Bird States/GroundState.h"
#include "../Bird States/HitState.h"
#include "../Bird States/ScoreState.h"

#include "../Bird_State.h"


GameState::GameState(StateStack<Application_State>& stack, Game_Data game_data) :
	Application_State(stack, game_data), General_State(stack),
	world(*game_data.window, thePlayer),
	state_Bird(Bird_State::Game_Data(*game_data.window, world.getSignalQueue(), *game_data.fonts, thePlayer))
{

	loadFonts(*game_data.fonts);
	//loadTextures(*game_data.textures);

	state_Bird.loadState<FlyingState>(States::ID::Flying);
	state_Bird.loadState<FlappingState>(States::ID::Flapping);
	state_Bird.loadState<GroundState>(States::ID::Ground);
	state_Bird.loadState<HitState>(States::ID::Hit);
	state_Bird.loadState<ScoreState>(States::ID::Score);


	state_Bird.pushState(States::ID::Flying);
}

void GameState::loadFonts(FontManager& fonts)
{
	fonts.load_resource(Resources::Fonts::Flappy_Font, "Media/Fonts/FlappyBirdy.ttf");
}

void GameState::draw()
{
	world.draw();
	state_Bird.draw();
}

bool GameState::update(sf::Time dt)
{
	world.update(dt);
	state_Bird.update(dt);

	if (state_Bird.isEmpty())
	{
		world.resetWorld();
		state_Bird.pushState(States::ID::Flying);
	}

	// The control by "player" has been removed.
	// The controls were distributed between the bird states.
	// player.handleRealTimeInput(signals);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// The control by "player" has been removed.
	// The controls were distributed between the bird states.
	// player.handleEvent(event, signals);

	state_Bird.handleEvent(event);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::ID::Pause);
	return true;
}

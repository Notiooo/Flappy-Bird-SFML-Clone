#include "FlappingState.h"
#include "../../Nodes/Specified Nodes/Pipe_Spawner.h"
#include "SFML/System/Time.hpp"

#include <memory>

FlappingState::FlappingState(StateStack<Bird_State>& statestack, Game_Data gamedata) :
	Bird_State(statestack, gamedata), General_State<Bird_State>(statestack),
	_queue(gamedata.queue),
	bird(gamedata.thePlayer),
	score_displayer(*gamedata.fonts)
{
	// ==== Score ==== //
	score_displayer.setPosition(camera.getSize().x / 2, camera.getSize().y / 4);

	Signal start_spawning;
	start_spawning.category_id = Signals::Pipe_Spawner;
	start_spawning.emit = [](NodeScene& spawner, sf::Time)
	{
		Pipe_Spawner& pipe_spawner = static_cast<Pipe_Spawner&>(spawner);
		pipe_spawner.start_spawning();
	};
	_queue->push(start_spawning);
}

void FlappingState::draw()
{
	/* nothing */
	score_displayer.draw(window);
}

bool FlappingState::update(sf::Time dt)
{
	score_displayer.update();
	score_displayer.set_score(bird->score);

 	//Check for collision
	if (bird->colliding)
	{
		requestStackPop();
		if (bird->colliding & Signals::Ground)
		{
			bird->setVelocity({ 0, 0 });
			requestStackPush(States::ID::Ground);
		}
		else if (bird->colliding & Signals::Pipe)
		{
			bird->setVelocity({ 0, 300.f });
			bird->setRotation(90);
			requestStackPush(States::ID::Hit);
		}
		
		return true;
	}


	// In this state the bird "flaps", so player is pressing
	// the button to make it fly, and try not to lose
	sf::Vector2f velocity = bird->getVelocity();

	// The gravity here
	bird->setVelocity(0.f, velocity.y + (std::abs(velocity.y * bird->gravityMultiplier) + bird->gravityStrength));

	bird->move(bird->getVelocity() * dt.asSeconds());

	// Rotate the bird
	bird->rotationAngle = bird->getVelocity().y * 0.5 - 40;
	if (bird->rotationAngle > 30)
		bird->setRotation(30);
	else if (bird->rotationAngle < -30)
		bird->setRotation(-30);
	else
		bird->setRotation(bird->rotationAngle);

	return true;
}

bool FlappingState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == flap_key)
	{
		bird->flap();
	}

	return true;
}

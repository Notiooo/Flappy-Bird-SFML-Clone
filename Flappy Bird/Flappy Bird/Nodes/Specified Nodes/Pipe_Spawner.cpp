#include "Pipe_Spawner.h"
#include <random>

Pipe_Spawner::Pipe_Spawner(const TextureManager& textures, sf::Vector2f spawn_position, Bird& thePlayer):
	textures(textures),
	spawn_position(spawn_position),
	thePlayer(thePlayer)
{

}

void Pipe_Spawner::start_spawning()
{
	spawning = true;
}

void Pipe_Spawner::stop_spawning()
{
	spawning = false;
}

unsigned int Pipe_Spawner::getCategory() const
{
	return Signals::Pipe_Spawner;
}

void Pipe_Spawner::spawnPipes()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> offsetX_generator(0, offset_X);
	std::uniform_int_distribution<int> offsetY_generator(-offset_Y, offset_Y);

	int offsetX = offsetX_generator(generator);
	int offsetY = offsetY_generator(generator);




	// Bottom Pipe
	std::unique_ptr<Pipe> bottom_pipe(std::make_unique<Pipe>(textures));
	bottom_pipe->setVelocity({ -scrollingSpeed, 0.f });
	bottom_pipe->setPosition({ spawn_position.x + distance_between_pipes + offsetX, 82.f + offsetY});
	list_of_pipes.push_back(bottom_pipe.get());
	this->pin_Node(std::move(bottom_pipe));

	// Upper Pipe
	std::unique_ptr<Pipe> up_pipe(std::make_unique<Pipe>(textures));
	up_pipe->setVelocity({ -scrollingSpeed, 0.f });
	up_pipe->setPosition({ spawn_position.x + distance_between_pipes + offsetX, -132.f + offsetY });
	up_pipe->setRotation(180);
	list_of_pipes.push_back(up_pipe.get());

	// I attach coin to the upper pipe
	std::unique_ptr<Coin> coin(std::make_unique<Coin>(sf::Vector2f(2.f, 500.f), thePlayer));
	up_pipe->pin_Node(std::move(coin));

	// And as previous attach it to the scene
	this->pin_Node(std::move(up_pipe));



}

void Pipe_Spawner::updateThis(sf::Time dt)
{
	// Spawn only if the spawning flag is turned on
	if (!spawning)
		return;

	if (list_of_pipes.empty() || list_of_pipes.back()->getPosition().x + distance_between_pipes < spawn_position.x)
	{
		spawnPipes();
	}
	if (!list_of_pipes.empty() && (list_of_pipes.front()->GetAbsoluteTransform() * sf::Vector2f()).x + list_of_pipes.front()->getBoundingRect().width < 0 )
	{
		this->unpin_Node(*list_of_pipes.front());
		list_of_pipes.pop_front();
	}
}

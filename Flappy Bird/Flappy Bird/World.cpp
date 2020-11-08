#include "World.h"
#include "Nodes/NodeSprite.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "Nodes/Specified Nodes/GroundNode.h"
#include "Nodes/Specified Nodes/Pipe_Spawner.h"
#include "Nodes/Specified Nodes/Score.h"

World::World(sf::RenderWindow& window, Bird*& bird):
	window(window),
	camera(window.getDefaultView()),
	textures(),
	root_scene(),
	sceneLayers(),
	GroundLevel(0.85f),
	thePlayer(bird)
{
	loadTextures();
	createScene();
}

Signals_Queue& World::getSignalQueue()
{
	return signal_queue;
}

void World::resetWorld()
{
	root_scene.removePinnedNodes();
	
	createScene();
}

void World::update(sf::Time dt)
{
	
	while (!signal_queue.isEmpty())
		root_scene.interpretSignal(signal_queue.pop(), dt);

	// If the birds collides -- freeze all game here!
	if (!handleCollisions())
		return;

	root_scene.update(dt);
}

void World::draw()
{
	window.setView(camera);
	window.draw(root_scene);
}

bool World::handleCollisions()
{
	unsigned int collisions = root_scene.checkNodeCollision(*thePlayer);
	if (collisions)
	{
		thePlayer->setCollision(collisions);
		if(collisions & Signals::Ground)
			return false;
	}
	return true;
}

void World::loadTextures()
{
	textures.load_resource(Resources::Textures::Bird, "Media/Textures/Bird/bird_orange_0.png");
	textures.load_resource(Resources::Textures::Bird_Spritesheet, "Media/Textures/Bird/bird_orange.png");

	textures.load_resource(Resources::Textures::Pipe_Green, "Media/Textures/Pipe/pipe_green_bottom.png");
	textures.load_resource(Resources::Textures::Background, "Media/Textures/Background/background_day.png");
	textures.load_resource(Resources::Textures::Ground, "Media/Textures/Background/ground.png");

}

void World::createScene()
{

	// We create as many layers as there are in SceneLayer
	// then we pin them to root_node so we can pin objects to them later
	for (std::size_t i = 0; i < Number_of_Layers; ++i)
	{
		NodeScene::Node layer(new NodeScene());
		sceneLayers[i] = layer.get();

		root_scene.pin_Node(std::move(layer));
	}


	// ====== Background code ======= ///

	// The sky
	sf::Texture& background = textures.get_resource(Resources::Textures::Background);
	sf::IntRect backgroundRect(0, 0, camera.getSize().x, camera.getSize().y);
	std::unique_ptr<NodeSprite> backgroundSprite(new NodeSprite(background, backgroundRect));
	sceneLayers[Background]->pin_Node(std::move(backgroundSprite));

	// The ground
	sf::IntRect groundRect(0, 0, camera.getSize().x * 2, camera.getSize().y * (1- GroundLevel));
	std::unique_ptr<GroundNode> GroundSprite(new GroundNode(textures, groundRect));
	GroundSprite->setPosition(0, camera.getSize().y * GroundLevel);
	sceneLayers[Middle]->pin_Node(std::move(GroundSprite));

	// Create the player
	// I need to assign it to additional pointer to use it in other functions
	std::unique_ptr<Bird> bird(new Bird(textures));
	thePlayer = bird.get();
	thePlayer->setPosition(camera.getSize().x / 4, camera.getSize().y / 2);
	sceneLayers[Front]->pin_Node(std::move(bird));

	// ===== Pipes ===== //
	std::unique_ptr<Pipe_Spawner> test_pipe(std::make_unique<Pipe_Spawner>(textures, sf::Vector2f(camera.getSize().x, 0), *thePlayer));
	test_pipe->setPosition(camera.getSize().x /2, camera.getSize().y/2);
	sceneLayers[Background]->pin_Node(std::move(test_pipe));

}

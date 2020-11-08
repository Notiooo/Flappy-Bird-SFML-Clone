#include "FlyingState.h"
#include "SFML/Graphics/RenderWindow.hpp"

FlyingState::FlyingState(StateStack<Bird_State>& statestack, Game_Data gamedata) :
	Bird_State(statestack, gamedata), General_State<Bird_State>(statestack),
	thePlayer(gamedata.thePlayer)
{
	textures.load_resource(Resources::Textures::Get_Ready_Label, "Media/Textures/GUI/label_get_ready.png");
	textures.load_resource(Resources::Textures::Instructions, "Media/Textures/GUI/instructions.png");
}

void FlyingState::draw()
{
	sf::FloatRect boundaries = get_ready.getLocalBounds();
	get_ready.setOrigin(boundaries.width / 2.f, boundaries.height / 2.f);

	boundaries = instructions.getLocalBounds();
	instructions.setOrigin(boundaries.width / 2.f, boundaries.height / 2.f);

	get_ready.setTexture(textures.get_resource(Resources::Textures::Get_Ready_Label));
	instructions.setTexture(textures.get_resource(Resources::Textures::Instructions));

	instructions.setPosition(camera.getCenter().x, camera.getSize().y / 2.5);
	get_ready.setPosition(camera.getCenter().x, camera.getSize().y / 4);


	window.draw(get_ready);
	window.draw(instructions);

	
}

bool FlyingState::update(sf::Time dt)
{
	if (the_interval > 3.14159265)
		the_interval = -3.14159265f;
	the_interval += 0.05f;
	
	
	thePlayer->setVelocity({ 0.f, sin(the_interval) * flyingRange});

	return true;
}

bool FlyingState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == flap_key)
	{
		thePlayer->flap();

		requestStackPop();
		requestStackPush(States::ID::Flapping);
	
	}
	return true;
}

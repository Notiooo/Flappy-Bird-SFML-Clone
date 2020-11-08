#include "HitState.h"

HitState::HitState(StateStack<Bird_State>& statestack, Game_Data gamedata):
	Bird_State(statestack, gamedata), General_State(statestack),
	thePlayer(gamedata.thePlayer)
{
}

void HitState::draw()
{
}

bool HitState::update(sf::Time dt)
{
	if (thePlayer->colliding & Signals::Ground)
	{
		requestStackPop();
		thePlayer->setVelocity({ 0, 0 });
		requestStackPush(States::ID::Ground);
	}

	return true;
}

bool HitState::handleEvent(const sf::Event& event)
{
	return true;
}

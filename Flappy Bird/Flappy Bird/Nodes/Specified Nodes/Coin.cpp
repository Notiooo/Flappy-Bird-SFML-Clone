#include "Coin.h"
#include "SFML/Graphics/RenderTarget.hpp"

Coin::Coin(sf::Vector2f vec, Bird& thePlayer):
	rect(vec),
	thePlayer(thePlayer)
{
	rect.setFillColor(sf::Color::Blue);
	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
}

sf::FloatRect Coin::getBoundingRect() const
{
	return GetAbsoluteTransform().transformRect(rect.getGlobalBounds());
}

void Coin::setPosition(sf::Vector2f vec)
{
	rect.setPosition(vec);
}

void Coin::updateThis(sf::Time dt)
{
	if (!collected)
	{
		if (getBoundingRect().intersects(thePlayer.getBoundingRect()))
		{
			// In next update it will remove itself (no time now)
			// Now after collected is true it is unnecessary here
			thePlayer.gainScore();
			collected = true;
		}
	}
}

void Coin::drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(rect, states);
}

#include "NodeSprite.h"

#include <SFML/Graphics/RenderTarget.hpp>

NodeSprite::NodeSprite(const sf::Texture& texture):
	sprite(texture)
{
}

NodeSprite::NodeSprite(const sf::Texture& texture, const sf::IntRect& rect) :
	sprite(texture, rect)
{
}

sf::FloatRect NodeSprite::getLocalBounds()
{
	return sprite.getLocalBounds();
}

sf::FloatRect NodeSprite::getBoundingRect() const
{
	return GetAbsoluteTransform().transformRect(sprite.getGlobalBounds());
}

void NodeSprite::drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);

}

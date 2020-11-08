#include "GroundNode.h"

GroundNode::GroundNode(TextureManager& textures, const sf::IntRect& rect): NodeSprite(textures.get_resource(Resources::Textures::Ground), rect)
{
	sf::Texture& texture = textures.get_resource(Resources::Textures::Ground);
	texture.setRepeated(true);
	
}

void GroundNode::updateThis(sf::Time dt)
{
	// Scroll
	move({ -scrollingSpeed * dt.asSeconds(), 0 });

	// Teleport back if too far
	if (-(getPosition().x) > (getLocalBounds().width / 2))
		setPosition(0.f, getPosition().y);

}

unsigned int GroundNode::getCategory() const
{
	return (Signals::Scene | Signals::CollideObject | Signals::Ground);
}

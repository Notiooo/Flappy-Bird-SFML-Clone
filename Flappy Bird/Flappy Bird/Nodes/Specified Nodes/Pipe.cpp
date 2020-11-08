#include "Pipe.h"
#include "SFML/Graphics/RenderTarget.hpp"

Pipe::Pipe(const TextureManager& textures, Type type) :
type(type),
sprite(textures.get_resource(Resources::Textures::Pipe_Green))
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	//if (type == Green)
		//sprite.setTexture(textures.get_resource(Resources::Pipe_Green));
}

unsigned int Pipe::getCategory() const
{
	return (Signals::CollideObject |
		Signals::Scene |
		Signals::Pipe);
}

void Pipe::drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

sf::FloatRect Pipe::getBoundingRect() const
{
	return GetAbsoluteTransform().transformRect(sprite.getGlobalBounds());
}

void Pipe::updateThis(sf::Time dt)
{
	move(getVelocity() * dt.asSeconds());
}

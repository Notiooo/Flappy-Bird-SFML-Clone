#include "Bird.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

Bird::Bird(const TextureManager& textures)
{
	const sf::Texture& bird_spritesheet = textures.get_resource(Resources::Textures::Bird_Spritesheet);
	int list_of_textures = bird_spritesheet.getSize().x / bird_sprite_x;

	for (int i = 0; i < list_of_textures; ++i)
	{
		spritesheet.push_back(sf::Sprite(bird_spritesheet, sf::IntRect(bird_sprite_x * i, 0, bird_sprite_x, bird_sprite_y)));

		// Center each of these textures
		auto& pushed_sprite = spritesheet.back();
		sf::FloatRect boundaries = pushed_sprite.getLocalBounds();
		pushed_sprite.setOrigin(boundaries.width / 2.f, boundaries.height / 2.f);
	}
	last_sprite = spritesheet.end();
	current_sprite = spritesheet.begin();

	sprite = &(*current_sprite);
}

unsigned int Bird::getCategory() const
{
	return Signals::Player;
}

sf::FloatRect Bird::getBoundingRect() const
{
	return GetAbsoluteTransform().transformRect(sprite->getGlobalBounds());
}

void Bird::setCollision(unsigned int collision)
{
	colliding = collision;
}

void Bird::gainScore()
{
	++score;
}

void Bird::startAnimate()
{
	animated = true;
}

void Bird::stopAnimate()
{
	animated = false;
	sprite = &spritesheet.front();
}

void Bird::animation()
{

	if (anim_clock.getElapsedTime().asSeconds() > interval_between_frames)
	{
		++current_sprite;
		if (current_sprite == last_sprite)
			current_sprite = spritesheet.begin();
		sprite = &(*current_sprite);
		anim_clock.restart();
	}

}

void Bird::updateThis(sf::Time dt)
{
	if (animated)
		animation();

	move(getVelocity() * dt.asSeconds());
}

void Bird::drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
}

void Bird::flap()
{
	setVelocity({ 0.f, 0.f });
	accelerate({ 0.f, -jumpStrength });
}

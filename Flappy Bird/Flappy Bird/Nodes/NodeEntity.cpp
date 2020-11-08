#include "NodeEntity.h"

void NodeEntity::setVelocity(sf::Vector2f vel)
{
	_velocity = vel;
}

void NodeEntity::setVelocity(float vx, float vy)
{
	_velocity = { vx, vy };
}

sf::Vector2f NodeEntity::getVelocity() const
{
	return _velocity;
}

NodeEntity& NodeEntity::operator+=(sf::Vector2f velocity)
{
	accelerate(velocity);
	return *this;
}

NodeEntity& NodeEntity::operator-=(sf::Vector2f velocity)
{
	accelerate(-velocity);
	return *this;
}

void NodeEntity::accelerate(sf::Vector2f velocity)
{
	_velocity += velocity;
}

void NodeEntity::updateThis(sf::Time dt)
{
	move(_velocity * dt.asSeconds());
}

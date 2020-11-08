#ifndef ENTITY_H_
#define ENTITY_H_

#include "NodeScene.h"


/**
* \brief The kind of scene that contains movement
* A specific type of scene that contains physical elements such as acceleration, speed.
*/
class NodeEntity : public NodeScene
{
	public:
		/** 
		* Set velocity of this object
		* @param vel Vector with velocity applied to this object
		*/
		void setVelocity(sf::Vector2f vel);

		/** 
		* Set velocity of this object
		* @param vx Velocity on the x-axis
		* @param vy Velocity on the y-axis
		*/
		void setVelocity(float vx, float vy);

		/** @return Velocity of this object */
		sf::Vector2f getVelocity() const;

		/**
		* Adds velocity to current velocity
		* @return itself
		*/
		NodeEntity& operator+=(sf::Vector2f velocity);

		/**
		* Decrease velocity to current velocity
		* @return itself
		*/
		NodeEntity& operator-=(sf::Vector2f velocity);


		/** 
		* Adds velocity to current velocity
		* @param velocity Velocity we want to add to this object
		*/
		void accelerate(sf::Vector2f velocity);


	private:
		/**
		* Function that updates everything related to this node
		* @param dt The time elapsed between the previous and the new frame.
		*/
		virtual void updateThis(sf::Time dt);

		/** Velocity of the object at this time */
		sf::Vector2f _velocity;
};


#endif
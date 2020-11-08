#ifndef COIN_H_
#define COIN_H_
#include "../NodeScene.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Bird.h"


/**
* Invisible coin adding a point after collection.
*/
class Coin : public NodeScene
{
public:
	/**
	* Standard object initialization and setting up
	* @param vec Vector that says where this object should be placed
	* @param thePlayer Reference to the object of the bird, which the player controls.
	*/
	Coin(sf::Vector2f vec, Bird& thePlayer);

	/**
	* Give the Rect of the object -- a certain box surrounding this object in size
	* @return The Rect of this object
	*/
	sf::FloatRect getBoundingRect() const;

	/**
	* This function sets the positions of this object
	* @param vec Position at which the object is to be positioned
	*/
	void setPosition(sf::Vector2f vec);

private:
	/**
	* Function that updates everything related to this node
	* @param dt The time elapsed between the previous and the new frame.
	*/
	void updateThis(sf::Time dt);

	/**
	* Function that prints only elements related to this node
	* @param target Canvas on which we draw all objects
	* @param states Any transformations and additional effects (in our case, transformations relative to the scene)
	*/
	virtual void drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const;

	/** Flag saying if this object has already been collected */
	bool collected = false;

	/** Rect of the object -- a certain box surrounding this object in size */
	sf::RectangleShape rect;

	/** Reference to the object of the bird, which the player controls. */
	Bird& thePlayer;
};





#endif
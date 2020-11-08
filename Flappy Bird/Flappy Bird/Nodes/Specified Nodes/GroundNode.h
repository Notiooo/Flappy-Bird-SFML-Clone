#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "../NodeSprite.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"

#include "../../Resources/ResourceManager.h"
#include "../../Resources/Resources.h"


/**
* A node of the floor, which moves continuously to the left. 
* When it is far enough away from the screen, it will return
* to its natural position, thus pretending the endless movement
* of the bird to the right.
*/
class GroundNode : public NodeSprite
{
public:
	/**
	* It loads the object's texture, and sets its infinite repetition.
	* @param textures The Texture Manager that holds textures
	* @param rect The rect size of this object (size of the sprite)
	*/
	GroundNode(TextureManager& textures, const sf::IntRect& rect);
	

private:
	/** How fast the ground moves */
	float scrollingSpeed = 30.2f;

	/**
	* Function that updates everything related to this node
	* @param dt The time elapsed between the previous and the new frame.
	*/
	virtual void updateThis(sf::Time dt);

	/**
	* Returns a category of this specific node used for signals and colisions
	* @return Category of this object
	*/
	virtual unsigned int getCategory() const;


};


#endif
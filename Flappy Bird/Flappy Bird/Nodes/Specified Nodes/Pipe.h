#ifndef PIPE_H_
#define PIPE_H_

#include "../NodeEntity.h"
#include "../../Resources/Resources.h"
#include "../../Resources/ResourceManager.h"

#include "SFML/Graphics/Sprite.hpp"


/**
* A pipe is an object that can move. 
* It has a category for which a collision is displayed.
*/
class Pipe : public NodeEntity
{
public:
	friend class TypicalPipe;

	/** 
	* Different types of pipes were planned 
	* in the game, but have not yet been implemented 
	*/
	enum class Type
	{
		Green,
		Red,
	};

	/**
	* Standardly initializes the pipe
	* @param textures The Texture Manager that holds the textures
	* @param type Type of the pipe
	*/
	Pipe(const TextureManager& textures, Type type = Type::Green);

	/**
	* Returns a category of this specific node used for signals and colisions
	* @return Category of this object
	*/
	virtual unsigned int getCategory() const;

	/**
	* Function that prints only elements related to this node
	* @param target Canvas on which we draw all objects
	* @param states Any transformations and additional effects (in our case, transformations relative to the scene)
	*/
	virtual void drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	* Give the Rect of the object -- a certain box surrounding this object in size
	* @return The Rect of this object
	*/
	sf::FloatRect getBoundingRect() const;

private:
	/**
	* Function that updates everything related to this node
	* @param dt The time elapsed between the previous and the new frame.
	*/
	virtual void updateThis(sf::Time dt);

	/** Type of the pipe*/
	Type type;

	/** Image of the pipe */
	sf::Sprite sprite;
};


#endif // !PIPE_H_

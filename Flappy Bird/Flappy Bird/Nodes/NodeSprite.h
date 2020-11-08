#ifndef NODESPRITE_H_
#define NODESPRITE_H_
#include "NodeScene.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Rect.hpp"


/**
* \brief The kind of scene that includes "Sprite" and the operations associated with it.
* 
* This kind of scene has some kind of graphical robe that we want to draw or manage.
*/
class NodeSprite : public NodeScene
{
	public:
		/**
		* Initializes the texture of this object
		* @param texture The Texture Manager that holds the textures
		*/
		explicit NodeSprite(const sf::Texture& texture);

		/**
		* Initializes the texture and rect of this object
		* @param texture The Texture Manager that holds the textures
		* @param rect The rect size of this object (size of the sprite)
		*/
		NodeSprite(const sf::Texture& texture, const sf::IntRect& rect);

		/** @return local boundaries around this object */
		virtual sf::FloatRect getLocalBounds();

		/**
		* Give the Rect of the object -- a certain box surrounding this object in size
		* @return The Rect of this object
		*/
		virtual sf::FloatRect getBoundingRect() const;


	private:
		/**
		* Function that prints only elements related to this node
		* @param target Canvas on which we draw all objects
		* @param states Any transformations and additional effects (in our case, transformations relative to the scene)
		*/
		virtual void drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		/** Image of this object */
		sf::Sprite sprite;

};


#endif
#ifndef BIRD_H_
#define BIRD_H_

#include "../NodeEntity.h"
#include "../../Resources/Resources.h"
#include "../../Resources/ResourceManager.h"

#include "../../Signals/Signals_Category.h"

#include "SFML/Graphics/Sprite.hpp"
#include <deque>
#include "SFML/System/Clock.hpp"

/**
* \brief The main object of the bird, which the player controls.
* 
* There are many things about control and the player
* himself, as well as things about the bird itself.
*/
class Bird : public NodeEntity
{
	// All States bird can have
	friend class FlappingState;
	friend class FlyingState;
	friend class GroundState;
	friend class HitState;
	friend class ScoreState;

public:
	/**
	* Sets the basic values of the bird, as well as reads its spritesheet
	* and pushes individual animation frames into the deque.
	* 
	* @param textures The Texture Manager that holds all the textures
	*/
	explicit Bird(const TextureManager& textures);

	/**
	* It sets what kind of collision the bird has at that moment
	* @param col Information about collision
	*/
	void setCollision(unsigned int col);

	/** Increments the value of the result*/
	void gainScore();

	/**
	* Returns a category of this specific node used for signals and colisions
	* @return Category of this object
	*/
	virtual unsigned int getCategory() const;

	/**
	* Give the Rect of the object -- a certain box surrounding this object in size
	* @return The Rect of this object
	*/
	sf::FloatRect getBoundingRect() const;

	/** Starts the animation */
	void startAnimate();

	/** Stops the animation */
	void stopAnimate();


private:
	/** Any instructions that you follow to make the animation last */
	void animation();

	/**
	* Function that updates everything related to this node
	* @param dt The time elapsed between the previous and the new frame.
	*/
	virtual void updateThis(sf::Time dt);

	/**
	* Function that prints only elements related to this node
	* @param target Canvas on which we draw all objects
	* @param states Any transformations and additional effects (in our case, transformations relative to the scene)
	*/
	virtual void drawThisNode(sf::RenderTarget & target, sf::RenderStates states) const;

	/** Makes the bird flap */
	void flap();
	
	/** How strongly gravity pulls down */
	float gravityStrength = 3.f;

	/** How high the bird can flap*/
	float jumpStrength = 85.f;

	/** How fast the bird gets the acceleration with the time of falling */
	float gravityMultiplier = 0.04f;

	/** Initial value with which the bird is rotated */
	float rotationAngle = 0.f;

	/** Show what the bird collides with */
	unsigned int colliding = Signals::None;

	/** Current score of the player */
	unsigned int score = 0;

	// Animation & Textures (should be optimized later)

	/** Flag saying if the animation continues and is displayed */
	bool animated = true;

	/** All single bird animation frames. */
	std::deque<sf::Sprite> spritesheet;

	/** Dimensions of one cage in x axis */
	short bird_sprite_x = 17;

	/** Dimensions of one cage in y axis */
	short bird_sprite_y = 12;

	/** Interval between changing frames */
	float interval_between_frames = 0.3f;

	/** Clock used when changing cages in the bird animation (should be later removed)*/
	sf::Clock anim_clock;

	/** Currently displayed bird animation frame */
	std::deque<sf::Sprite>::iterator current_sprite;

	/** Last displayed bird animation frame */
	std::deque<sf::Sprite>::iterator last_sprite;

	/** Pointer for the currently drawn bird animation frame. */
	sf::Sprite* sprite;
};
#endif // ! BIRD_H_

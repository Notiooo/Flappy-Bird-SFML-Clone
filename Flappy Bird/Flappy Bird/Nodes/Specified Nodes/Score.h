#ifndef SCORE_H_
#define SCORE_H_

#include "../../Resources/ResourceManager.h"
#include "../../Resources/Resources.h"
#include "../NodeScene.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


/**
* \brief Text that displays the player's current score.
* 
* It is displayed in the middle of the screen and
* continuously updates the pipes that have been passed.
*/
class Score
{
public:
	/** 
	* Sets the basic values that the text displaying the score should have.
	* @param fonts Font Manager that holds the fonts
	* @param the_font The font that we want to use to display the score
	*/
	Score(FontManager& fonts, Resources::Fonts the_font = Resources::Fonts::Flappy_Font);

	/**
	* Sets the score that this object displays
	* @param score Score to display
	*/
	void set_score(int score);

	/**
	* Changes the position of this object displaying the score.
	* @param pos Vector containing the position on which we want to place an object
	*/
	void setPosition(sf::Vector2f pos);

	/**
	* Changes the position of this object displaying the score.
	* @param pos_x Position on the x-axis on which you want to place the object
	* @param pos_y Position on the y-axis on which you want to place the object
	*/
	void setPosition(float pos_x, float pos_y);

	/**
	* Function that draws this object
	* @param window Window on which we draw an object
	*/
	void draw(sf::RenderWindow& window) const;

	/** Updates the status of this object (informations in it) */
	void update();



private:
	/** The number that this object will textually display */
	sf::Text score_text;
};


#endif
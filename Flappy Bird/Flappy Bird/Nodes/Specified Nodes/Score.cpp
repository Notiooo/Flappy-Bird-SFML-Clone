#include "Score.h"
#include "SFML/Graphics/RenderTarget.hpp"

Score::Score(FontManager& fonts, Resources::Fonts the_font)
{
	score_text.setFont(fonts.get_resource(the_font));
	score_text.setCharacterSize(18);
	score_text.setFillColor(sf::Color::White);
	score_text.setOutlineColor(sf::Color::Black);
	score_text.setOutlineThickness(1.f);
	score_text.setOrigin(score_text.getLocalBounds().width / 2, score_text.getLocalBounds().height / 2);
	
}

void Score::set_score(int score)
{
	score_text.setString(std::to_string(score));
}

void Score::setPosition(sf::Vector2f pos)
{
	score_text.setPosition(pos);
}

void Score::setPosition(float pos_x, float pos_y)
{
	score_text.setPosition(pos_x, pos_y);
}

void Score::draw(sf::RenderWindow& window) const
{
	window.draw(score_text);
}

void Score::update()
{
	score_text.setOrigin(score_text.getLocalBounds().width / 2, score_text.getLocalBounds().height / 2);
}

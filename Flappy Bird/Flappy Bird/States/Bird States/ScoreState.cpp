#include "ScoreState.h"

int ScoreState::best_result = 0;

ScoreState::ScoreState(StateStack<Bird_State>& statestack, Game_Data gamedata):
	Bird_State(statestack, gamedata), General_State(statestack),
	fonts(*gamedata.fonts),
	thePlayer(gamedata.thePlayer),
	window(*gamedata.window)
{

	textures.load_resource(Resources::Textures::Panel_Score, "Media/Textures/GUI/panel_score.png");
	textures.load_resource(Resources::Textures::Medal_Bronze, "Media/Textures/GUI/medal_bronze.png");
	textures.load_resource(Resources::Textures::Medal_Gold, "Media/Textures/GUI/medal_gold.png");
	textures.load_resource(Resources::Textures::Medal_Platinum, "Media/Textures/GUI/medal_platinum.png");
	textures.load_resource(Resources::Textures::Medal_Silver, "Media/Textures/GUI/medal_silver.png");

	score_panel.setTexture(textures.get_resource(Resources::Textures::Panel_Score));
	int score = thePlayer->score;
	if (score > 2 && score <= 6)
		the_medal.setTexture(textures.get_resource(Resources::Textures::Medal_Bronze));
	else if(score > 6 && score <= 11)
		the_medal.setTexture(textures.get_resource(Resources::Textures::Medal_Silver));
	else if(score > 11 && score <= 16)
		the_medal.setTexture(textures.get_resource(Resources::Textures::Medal_Gold));
	else if(score > 16)
		the_medal.setTexture(textures.get_resource(Resources::Textures::Medal_Platinum));

	if (score > ScoreState::best_result)
		ScoreState::best_result = score;


	score_panel.setOrigin(score_panel.getLocalBounds().width / 2, score_panel.getLocalBounds().height / 2);
	score_panel.setPosition(camera.getSize().x / 2, camera.getSize().y / 4);

	the_medal.setOrigin(the_medal.getLocalBounds().width / 2, the_medal.getLocalBounds().height / 2);
	the_medal.setPosition(score_panel.getPosition() + sf::Vector2f(-33.f, 4.f));
	
	score_text.setFont(fonts.get_resource(Resources::Flappy_Font));
	score_text.setCharacterSize(9);
	score_text.setFillColor(sf::Color::White);
	score_text.setOutlineColor(sf::Color::Black);
	score_text.setOutlineThickness(1.f);
	score_text.setOrigin(score_text.getLocalBounds().width / 2.f, score_text.getLocalBounds().height / 2.f);

	score_text.setPosition(score_panel.getPosition() + sf::Vector2f(38.f, -8.f));
	score_text.setString(std::to_string(thePlayer->score));
	
	best_score = score_text;
	best_score.setString(std::to_string(ScoreState::best_result));
	best_score.setPosition(score_panel.getPosition() + sf::Vector2f(38.f, 12.f));


}

void ScoreState::draw()
{
	window.draw(score_panel);
	window.draw(the_medal);
	window.draw(score_text);
	window.draw(best_score);
}

bool ScoreState::update(sf::Time dt)
{
	score_text.setOrigin(score_text.getLocalBounds().width / 2, score_text.getLocalBounds().height / 2);
	best_score.setOrigin(best_score.getLocalBounds().width / 2, best_score.getLocalBounds().height / 2);

	return true;
}

bool ScoreState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code != sf::Keyboard::End)
	{
		requestStackClear();
	}

	return true;
}

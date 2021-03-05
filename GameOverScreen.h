#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "GameState.h"
#include "Menu.h"
#include "Statistic.h"
#include <string>

class GameOverScreen : public State
{
private:
	GameDataRef _data;
	Statistic _stats;

	// Texts
	sf::Text title;
	sf::Text accuracy;
	sf::Text score;

	// Buttons
	sf::Sprite play_button;
	sf::Sprite menu_button;
	sf::Sprite quit_button;

	void InitText(float x, float y, sf::Text& text, unsigned int size, std::string string);

public:
	// Init
	GameOverScreen(GameDataRef data, Statistic stats);
	~GameOverScreen();

	void Init() override;

	// Polling events
	void PollEvents() override;

	// Functions
	void update(float delta) override;
	void render() const override;
};


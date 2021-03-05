#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "GameState.h"

// TODO: make nice background animation of targets
// TODO: add some animation after kill and disappearance of targets

class Menu : public State
{
private:
	GameDataRef _data;

	// Title
	sf::Text title;

	// Buttons
	sf::Sprite play_button;
	sf::Sprite quit_button;

public:
	// Init
	Menu(GameDataRef data);
	~Menu();

	void Init() override;

	// Polling events
	void PollEvents() override;

	// Functions
	void update(float delta) override;
	void render() const override;
};


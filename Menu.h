#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"
#include "GameState.h"
#include "Button.h"
#include "SettingsState.h"

// TODO: make nice background animation of targets

class Menu : public State
{
private:
	GameDataRef _data;

	// Title
	sf::Text title;

	// Buttons
	Engine::Button play_button;
	Engine::Button settings_button;
	Engine::Button quit_button;

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


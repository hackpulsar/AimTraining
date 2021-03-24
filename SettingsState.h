#pragma once

#include "Game.h"
#include "State.h"
#include "Menu.h"
#include "Button.h"

class SettingsState : public State
{
private:
	GameDataRef _data;

	// Title
	sf::Text title;

	// Buttons
	Engine::Button back_button;
	Engine::Button save_button;

	// Cursor colors settings block
	sf::Text ttl;

	Engine::Button previous;
	Engine::Button next;

	Colors clrs;

public:
	// Init
	SettingsState(GameDataRef data);
	~SettingsState();

	void Init() override;

	// Polling events
	void PollEvents() override;

	// Functions
	void update(float delta) override;
	void render() const override;

};


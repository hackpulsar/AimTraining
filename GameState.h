#pragma once

#include "Defenitions.hpp"
#include "Game.h"
#include "State.h"
#include "Spawner.h"
#include "GameOverScreen.h"
#include "Flash.h"
#include "Statistic.h"

class GameState : public State
{
private:
	GameDataRef _data;

	sf::Sprite* cursor;

	// Spawner
	Spawner* spawner;

	// Flash screen
	Flash* flash;

	// Current game state
	GameStates _state;

	sf::Clock _clock;

	// Statistic
	Statistic _stats;

	// Health
	std::vector<sf::Sprite> health;
	unsigned short int hp = 3;

public:
	// Init
	GameState(GameDataRef _data);
	~GameState();

	void Init() override;

	// Polling events
	void PollEvents() override;

	// Functions
	void update(float delta) override;
	void render() const override;

};


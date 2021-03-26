#pragma once

#include "Defenitions.hpp"
#include "Game.h"
#include "State.h"
#include "Spawner.h"
#include "GameOverScreen.h"
#include "Flash.h"
#include "Statistic.h"
#include "ParticleSystem.h"

class GameState : public State
{
private:
	GameDataRef _data;
	sf::Sprite* cursor;

	Spawner* spawner;
	ParticleSystem* particleSystem;

	// Current game state
	GameStates _state;

	sf::Clock _clock;
	Colors _colors;

	// Statistic
	Statistic _stats;
	// Flash screen
	Flash* flash;

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


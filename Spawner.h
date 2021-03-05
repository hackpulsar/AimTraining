#pragma once

#include "Game.h"
#include "Target.h"

class Spawner
{
private:
	GameDataRef _data;

	sf::Clock _clock;
	float fSpawnTimerMax = 1200.0f;
	const float fSpawnTimerMin = 450.0f;
	int nMaxTargets = 10;

	// All targets will be here
	std::vector<Target*> targets;

	bool running = false;

	// Helping functions
	int clamp(int min, int max, int value) const;
public:
	Spawner(GameDataRef data);
	~Spawner();

	// Getters
	std::vector<Target*>& GetTargets();

	void DeleteTarget(std::vector<Target*>::iterator it);

	// Functions
	void start();
	void stop();
	void update(float delta);
	void render() const;
};


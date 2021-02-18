#pragma once

#include <iostream>

#include "Target.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Clock clock;
	sf::Sprite* cursor;
	// Textures
	sf::Texture cursTexture;
	sf::Texture heartTexture;

	sf::Font textFont;
	sf::Text endGameText;

	// health
	std::vector<sf::Sprite> health;

	float fSpawnTimer = 0.0f;
	float fSpawnTimerMax = 500.0f;
	const float fSpawnTimerMin = 250.0f;
	int nMaxTargets = 10;

	// Is game going bool
	bool running = true; // TODO: stop game when false

	std::vector<Target*> targets;

	// Helping functions
	float clamp(float min, float max, float n) const;
public:
	Game(int w, int h, std::string title);
	~Game();

	// Getters
	sf::RenderWindow& GetWindow() const;

	// Functions
	void update();
	void render() const;
};


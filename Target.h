#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"
#include "AssetManager.h"

class Target
{
private:
	sf::Sprite spr;
	
public:
	Target(sf::Vector2f pos, const AssetManager& manager);
	~Target();

	float scale = 0.0f;
	float step = 0.015f;

	// Getters
	sf::Sprite& GetSpr();

	// Functions
	void update(float delta);
	void render(sf::RenderTarget* target) const;
};


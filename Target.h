#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class Target
{
private:
	sf::Sprite spr;
	sf::Texture texture;
	
public:
	Target(sf::Vector2f pos);
	~Target();

	float scale = 0.0f;
	float step = 0.015f;

	// Getters
	sf::Sprite GetSpr() const;

	// Functions
	void update(float delta);
	void render(sf::RenderTarget* target) const;
};


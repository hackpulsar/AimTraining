#pragma once

#include <SFML/Graphics.hpp>
#include "Defenitions.hpp"
#include "Game.h"

class Flash
{
private:
	GameDataRef _data;

	sf::RectangleShape _shape;
	bool _flashOn;

public:
	Flash(GameDataRef data);
	~Flash();

	void show(float delta);
	void render() const;

};


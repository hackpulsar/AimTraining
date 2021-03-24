#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Game.h"
#include <functional>

namespace Engine
{
	class Button
	{
	private:
		GameDataRef _data;

		// Sprite
		sf::Sprite _spr;

		// Sounds
		sf::Sound _onClickSound;
		sf::Sound _onHoverSound;

		bool canPlay = true;
		bool canClick = true;

	public:
		// Init
		Button(float x, float y, GameDataRef data, const sf::Texture &texture, sf::Sound onClickSound, sf::Sound onHoverSound);
		Button() { }; // default constructor
		~Button();

		void Click();

		// Getters
		bool IsClicked(sf::Mouse::Button button) const;
		bool CanClick() const;

		// Functions
		void update(float delta);
		void render() const;

	};
}


#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempObject(object.getPosition().x, object.getPosition().y,
			object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (tempObject.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}

	return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

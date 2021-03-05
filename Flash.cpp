#include "Flash.h"

Flash::Flash(GameDataRef data)
	:_data(data)
{
	_shape = sf::RectangleShape(sf::Vector2f(this->_data->window.getSize()));
	_shape.setFillColor(sf::Color(255, 255, 255, 0));
	_flashOn = true;
}

Flash::~Flash() { }

void Flash::show(float delta)
{
	if (_flashOn)
	{
		int alpha = (int)_shape.getFillColor().a + (FLASH_SPEED * delta);
		if (alpha >= 255)
		{
			alpha = 255;
			_flashOn = false;
		}
		_shape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
	else
	{
		int alpha = (int)_shape.getFillColor().a - (FLASH_SPEED * delta);
		if (alpha <= 0)
		{
			alpha = 0;
			_flashOn = false;
		}
		_shape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
}

void Flash::render() const
{
	this->_data->window.draw(_shape);
}

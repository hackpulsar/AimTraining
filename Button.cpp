#include "Button.h"

Engine::Button::Button(float x, float y, GameDataRef data, const sf::Texture &texture, sf::Sound onClickSound, sf::Sound onHoverSound)
	:_data(data), _spr(sf::Sprite(texture)), _onClickSound(onClickSound), _onHoverSound(onHoverSound)
{
	this->_spr.setScale(0.4f, 0.4f);
	this->_spr.setPosition(x, y);

	_onClickSound.setVolume(50.0f);
	_onHoverSound.setVolume(50.0f);
}

Engine::Button::~Button()
{ }

void Engine::Button::Click()
{
	if (canClick)
	{
		this->_onClickSound.play();
		canClick = false;
	}
}

bool Engine::Button::IsClicked(sf::Mouse::Button button) const
{
	return _data->input.IsSpriteClicked(_spr, button, _data->window);
}

bool Engine::Button::CanClick() const
{
	return this->canClick;
}

void Engine::Button::update(float delta)
{
	sf::Vector2i mouse = this->_data->input.GetMousePosition(this->_data->window);
	if (this->_spr.getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
	{
		if (this->_spr.getColor() != sf::Color::Yellow)
			this->_spr.setColor(sf::Color::Yellow);
		if (canPlay)
		{
			this->_onHoverSound.play();
			canPlay = false;
		}
	}
	else if (!this->_spr.getGlobalBounds().contains(float(mouse.x), float(mouse.y)))
	{
		if (this->_spr.getColor() != sf::Color::White)
			this->_spr.setColor(sf::Color::White);
		canPlay = true;
		canClick = true;
	}
}

void Engine::Button::render() const
{
	this->_data->window.draw(this->_spr);
}

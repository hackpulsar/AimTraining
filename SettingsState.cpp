#include "SettingsState.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

SettingsState::SettingsState(GameDataRef data)
	:_data(data)
{ }

SettingsState::~SettingsState()
{ }

void SettingsState::Init()
{
	this->title.setFont(_data->assets.GetFont("basic font"));
	this->title.setString("Settings");
	this->title.setCharacterSize(45);
	this->title.setPosition(
		float(_data->window.getSize().x / 2 - 70.0f),
		float(5.0f));

	this->ttl.setFont(_data->assets.GetFont("basic font"));
	this->ttl.setString(std::get<1>(clrs[_data->settings.GetSetting("cursor color")]));
	this->ttl.setCharacterSize(45);
	this->ttl.setPosition(
		float(_data->window.getSize().x / 2 - ttl.getString().getSize() * 10),
		float(_data->window.getSize().y / 2 - 200));

	this->back_button = Engine::Button(
		5.0f, 5.0f, _data, _data->assets.GetTexture("back button"), 
		_data->assets.GetSound("click sound"), _data->assets.GetSound("select sound"));

	this->save_button = Engine::Button(
		5.0f, _data->window.getSize().y - 75.0f, _data, _data->assets.GetTexture("save button"),
		_data->assets.GetSound("click sound"), _data->assets.GetSound("select sound")
	);

	this->previous = Engine::Button(
		float(_data->window.getSize().x / 2 - 200), float(_data->window.getSize().y / 2 - 200),
		_data, _data->assets.GetTexture("previous"),
		_data->assets.GetSound("click sound"), _data->assets.GetSound("select sound"));

	this->next = Engine::Button(
		float(_data->window.getSize().x / 2 + 150), float(_data->window.getSize().y / 2 - 200),
		_data, _data->assets.GetTexture("next"),
		_data->assets.GetSound("click sound"), _data->assets.GetSound("select sound"));
}

void SettingsState::PollEvents()
{
	sf::Event ev;
	while (this->_data->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			this->_data->window.close();
		}

		if (sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (previous.IsClicked(sf::Mouse::Left))
				{
					_data->settings.curs_color = this->clrs.Previous();
					this->ttl.setString(std::get<1>(this->clrs.GetActive()));
					this->ttl.setPosition(
						float(_data->window.getSize().x / 2 - ttl.getString().getSize() * 8),
						float(_data->window.getSize().y / 2 - 200));
				}
				else if (next.IsClicked(sf::Mouse::Left))
				{
					_data->settings.curs_color = this->clrs.Next();
					this->ttl.setString(std::get<1>(this->clrs.GetActive()));
					this->ttl.setPosition(
						float(_data->window.getSize().x / 2 - ttl.getString().getSize() * 8),
						float(_data->window.getSize().y / 2 - 200));
				}
				else if (save_button.IsClicked(sf::Mouse::Left) && save_button.CanClick())
				{
					save_button.Click();
					_data->settings.Save();
					MessageBoxA(NULL, "Settings saved successfully!", "Settings", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}
}

void SettingsState::update(float delta)
{
	back_button.update(delta);
	save_button.update(delta);

	previous.update(delta);
	next.update(delta);

	if (back_button.IsClicked(sf::Mouse::Left))
	{
		back_button.Click();
		_data->machine.AddState(StateRef(new Menu(this->_data)), true);
	}
}

void SettingsState::render() const
{
	this->_data->window.clear(sf::Color(87, 89, 93));

	// Titles
	this->_data->window.draw(title);
	this->_data->window.draw(ttl);

	// Buttons
	back_button.render();
	save_button.render();
	previous.render();
	next.render();

	this->_data->window.display();
}

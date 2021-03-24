#include "Menu.h"

Menu::Menu(GameDataRef data)
	:_data(data)
{ }

Menu::~Menu()
{ }

void Menu::Init()
{
	this->_data->window.setMouseCursorVisible(true);
	title.setFont(this->_data->assets.GetFont("basic font"));
	title.setString("Aim Training");
	title.setCharacterSize(72);
	title.setPosition(
		this->_data->window.getSize().x / 2 - 185.0f,
		this->_data->window.getSize().y / 2 - 200.0f);

	// Setting up buttons
	this->play_button = Engine::Button(
		this->_data->window.getSize().x / 2 - 105.0f,
		this->_data->window.getSize().y / 2 - 50.0f,
		this->_data, this->_data->assets.GetTexture("play button"),
		this->_data->assets.GetSound("click sound"), this->_data->assets.GetSound("select sound"));

	this->settings_button = Engine::Button(
		this->_data->window.getSize().x / 2 - 105.0f,
		this->_data->window.getSize().y / 2 + 50.0f,
		this->_data, this->_data->assets.GetTexture("settings button"),
		this->_data->assets.GetSound("click sound"), this->_data->assets.GetSound("select sound"));

	this->quit_button = Engine::Button(
		this->_data->window.getSize().x / 2 - 105.0f,
		this->_data->window.getSize().y / 2 + 150.0f,
		this->_data, this->_data->assets.GetTexture("quit button"),
		this->_data->assets.GetSound("click sound"), this->_data->assets.GetSound("select sound"));
}

void Menu::PollEvents()
{
	sf::Event ev;
	while (this->_data->window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (this->play_button.IsClicked(sf::Mouse::Left))
				{
					this->play_button.Click();
					this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
				}

				if (this->quit_button.IsClicked(sf::Mouse::Left))
				{
					this->quit_button.Click();
					this->_data->window.close();
				}

				if (this->settings_button.IsClicked(sf::Mouse::Left))
				{
					this->settings_button.Click();
					this->_data->machine.AddState(StateRef(new SettingsState(this->_data)), true);
				}
			}
			break;
		default:
			break;
		}
	}
}

// Functions
void Menu::update(float delta)
{
	sf::Vector2i mouse = this->_data->input.GetMousePosition(this->_data->window);
	this->play_button.update(delta);
	this->quit_button.update(delta);
	this->settings_button.update(delta);
}

void Menu::render() const
{
	this->_data->window.clear(sf::Color(87, 89, 93));

	// Title
	this->_data->window.draw(title);

	// Buttons
	this->play_button.render();
	this->quit_button.render();
	this->settings_button.render();

	this->_data->window.display();
}

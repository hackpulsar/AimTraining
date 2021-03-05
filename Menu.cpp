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
	this->play_button.setTexture(this->_data->assets.GetTexture("play button"));
	this->play_button.setScale(0.4f, 0.4f);
	this->play_button.setPosition(this->_data->window.getSize().x / 2 - 105, this->_data->window.getSize().y / 2 - 50);

	this->quit_button.setTexture(this->_data->assets.GetTexture("quit button"));
	this->quit_button.setScale(0.4f, 0.4f);
	this->quit_button.setPosition(this->_data->window.getSize().x / 2 - 105, this->_data->window.getSize().y / 2 + 50);
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
				if (this->_data->input.IsSpriteClicked(play_button, sf::Mouse::Left, this->_data->window))
				{
					this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
				}

				if (this->_data->input.IsSpriteClicked(quit_button, sf::Mouse::Left, this->_data->window))
				{
					this->_data->window.close();
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

	// Checking if player hover buttons with mouse
	if (play_button.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		if (play_button.getColor() != sf::Color::Yellow)
			play_button.setColor(sf::Color::Yellow);
	}
	else if (!play_button.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		if(play_button.getColor() != sf::Color::White)
			play_button.setColor(sf::Color::White);
	}

	if (quit_button.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		if (quit_button.getColor() != sf::Color::Yellow)
			quit_button.setColor(sf::Color::Yellow);
	}
	else if (!quit_button.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		if (quit_button.getColor() != sf::Color::White)
			quit_button.setColor(sf::Color::White);
	}
}

void Menu::render() const
{
	this->_data->window.clear(sf::Color(87, 89, 93));
	this->_data->window.draw(title);
	this->_data->window.draw(play_button);
	this->_data->window.draw(quit_button);
	this->_data->window.display();
}

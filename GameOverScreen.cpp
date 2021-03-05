#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(GameDataRef data, Statistic stats)
	:_data(data), _stats(stats)
{ }

GameOverScreen::~GameOverScreen()
{ }

void GameOverScreen::InitText(float x, float y, sf::Text& text, unsigned int size, std::string string)
{
	text.setFont(this->_data->assets.GetFont("basic font"));
	text.setString(string);
	text.setCharacterSize(size);
	text.setPosition(x, y);
}

void GameOverScreen::Init()
{
	this->_data->window.setMouseCursorVisible(true);

	// Setting up texts
	InitText(
		float(this->_data->window.getSize().x / 2 - 170), 
		float(this->_data->window.getSize().y / 2 - 250),
		title, 72, "Game Over!");
	InitText(
		float(this->_data->window.getSize().x / 2 - 120), 
		float(this->_data->window.getSize().y / 2 - 160),
		score, 36, "Score: " + std::to_string(this->_stats.GetScore()));
	InitText(
		float(this->_data->window.getSize().x / 2 - 120), 
		float(this->_data->window.getSize().y / 2 - 120),
		accuracy, 36, "Accuracy: " + std::to_string(this->_stats.GetAccuracy()).substr(0, 5) + "%");

	// Setting up buttons
	this->play_button.setTexture(this->_data->assets.GetTexture("play button"));
	this->play_button.setScale(0.4f, 0.4f);
	this->play_button.setPosition(
		float(this->_data->window.getSize().x / 2 - 105),
		float(this->_data->window.getSize().y / 2));

	this->menu_button.setTexture(this->_data->assets.GetTexture("menu button"));
	this->menu_button.setScale(0.4f, 0.4f);
	this->menu_button.setPosition(
		float(this->_data->window.getSize().x / 2 - 105),
		float(this->_data->window.getSize().y / 2 + 100));

	this->quit_button.setTexture(this->_data->assets.GetTexture("quit button"));
	this->quit_button.setScale(0.4f, 0.4f);
	this->quit_button.setPosition(
		float(this->_data->window.getSize().x / 2 - 105),
		float(this->_data->window.getSize().y / 2 + 200));
}

void GameOverScreen::PollEvents()
{
	sf::Event ev;
	while (this->_data->window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->_data->window.close();
			break;
		}
	}
}

void GameOverScreen::update(float delta)
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
		if (play_button.getColor() != sf::Color::White)
			play_button.setColor(sf::Color::White);
	}

	if (menu_button.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		if (menu_button.getColor() != sf::Color::Yellow)
			menu_button.setColor(sf::Color::Yellow);
	}
	else if (!menu_button.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		if (menu_button.getColor() != sf::Color::White)
			menu_button.setColor(sf::Color::White);
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

	// Clicking buttons logic
	if (this->_data->input.IsSpriteClicked(play_button, sf::Mouse::Left, this->_data->window))
	{
		this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
	}

	if (this->_data->input.IsSpriteClicked(menu_button, sf::Mouse::Left, this->_data->window))
	{
		this->_data->machine.AddState(StateRef(new Menu(this->_data)), true);
	}

	if (this->_data->input.IsSpriteClicked(quit_button, sf::Mouse::Left, this->_data->window))
	{
		this->_data->window.close();
	}
}

void GameOverScreen::render() const
{
	this->_data->window.clear(sf::Color(87, 89, 93));

	// Texts
	this->_data->window.draw(title);
	this->_data->window.draw(accuracy);
	this->_data->window.draw(score);

	//Buttons
	this->_data->window.draw(play_button);
	this->_data->window.draw(menu_button);
	this->_data->window.draw(quit_button);

	this->_data->window.display();
}

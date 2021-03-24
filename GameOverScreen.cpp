#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(GameDataRef data, Statistic stats)
	:_data(data), _stats(stats)
{
	// Setting up buttons
	this->play_button = Engine::Button(
		float(this->_data->window.getSize().x / 2 - 105),
		float(this->_data->window.getSize().y / 2),
		this->_data, this->_data->assets.GetTexture("play button"),
		this->_data->assets.GetSound("click sound"), this->_data->assets.GetSound("select sound"));

	this->menu_button = Engine::Button(
		float(this->_data->window.getSize().x / 2 - 105),
		float(this->_data->window.getSize().y / 2 + 100),
		this->_data, this->_data->assets.GetTexture("menu button"),
		this->_data->assets.GetSound("click sound"), this->_data->assets.GetSound("select sound"));

	this->quit_button = Engine::Button(
		float(this->_data->window.getSize().x / 2 - 105),
		float(this->_data->window.getSize().y / 2 + 200),
		this->_data, this->_data->assets.GetTexture("quit button"),
		this->_data->assets.GetSound("click sound"), this->_data->assets.GetSound("select sound"));
}

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

	// Clicking buttons logic
	play_button.update(delta);
	menu_button.update(delta);
	quit_button.update(delta);

	if (play_button.IsClicked(sf::Mouse::Left))
	{
		play_button.Click();
		_data->machine.AddState(StateRef(new GameState(_data)), true);
	}

	if (menu_button.IsClicked(sf::Mouse::Left))
	{
		menu_button.Click();
		_data->machine.AddState(StateRef(new Menu(_data)), true);
	}

	if (quit_button.IsClicked(sf::Mouse::Left))
	{
		quit_button.Click();
		_data->window.close();
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
	play_button.render();
	menu_button.render();
	quit_button.render();

	this->_data->window.display();
}

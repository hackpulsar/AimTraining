#include "Game.h"
#include "Menu.h"

Game::Game(int w, int h, std::string title)
{
	this->_data->window.create(sf::VideoMode(w, h), title, sf::Style::Close | sf::Style::Titlebar);
	// loading textures
	this->_data->assets.LoadTexture("cursor", CURSOR_FILEPATH);
	this->_data->assets.LoadTexture("heart", HEART_FILEPATH);
	this->_data->assets.LoadTexture("target", TARGET_FILEPATH);
	this->_data->assets.LoadTexture("play button", PLAY_BUTTON_FILEPATH);
	this->_data->assets.LoadTexture("quit button", QUIT_BUTTON_FILEPATH);
	this->_data->assets.LoadTexture("menu button", MENU_BUTTON_FILEPATH);
	this->_data->assets.LoadTexture("settings button", SETTINGS_BUTTON_FILEPATH);
	this->_data->assets.LoadTexture("back button", BACK_BUTTON_FILEPATH);
	this->_data->assets.LoadTexture("previous", PREV_BUTTON_FILEPATH);
	this->_data->assets.LoadTexture("next", NEXT_BUTTON_FILEPATH);
	this->_data->assets.LoadTexture("save button", SAVE_BUTTON_FILEPATH);
	
	// loading fonts
	this->_data->assets.LoadFont("basic font", BASIC_FONT_FILEPATH);

	// loading sounds
	this->_data->assets.LoadSound("pop sound", POP_SOUND_FILEPATH);
	this->_data->assets.LoadSound("hurt sound", HURT_SOUND_FILEPATH);
	this->_data->assets.LoadSound("select sound", SELECT_SOUND_FILEPATH);
	this->_data->assets.LoadSound("click sound", CLICK_SOUND_FILEPATH);

	// adding first game state (menu)
	this->_data->machine.AddState(StateRef(new Menu(this->_data)), false);
	this->_data->window.setFramerateLimit(60);

	// loading settings
	this->_data->settings.Load();
}

Game::~Game()
{ }

void Game::Run()
{
	while (this->_data->window.isOpen())
	{
		this->_data->machine.ProcessStateChanges();
		this->_data->machine.GetActiveState()->PollEvents();
		this->_data->machine.GetActiveState()->update(1.0f / 60.0f);
		this->_data->machine.GetActiveState()->render();
	}
}

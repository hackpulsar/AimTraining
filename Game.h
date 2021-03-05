#pragma once

#include <iostream>

#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Defenitions.hpp"

#include "AssetManager.h"
#include "StateMachine.h"
#include "InputManager.h"

struct GameData
{
	sf::RenderWindow window;
	AssetManager assets;
	StateMachine machine;
	InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
private:
	sf::Clock clock;

	GameDataRef _data = std::make_shared<GameData>();

public:
	Game(int w, int h, std::string title);
	~Game();

	void Run();
};

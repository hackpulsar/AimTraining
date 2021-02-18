#include "Game.h"

Game::Game(int w, int h, std::string title)
	:window(new sf::RenderWindow(sf::VideoMode(w, h), title, sf::Style::Titlebar | sf::Style::Close)),
	cursor(new sf::Sprite()), health({ sf::Sprite(), sf::Sprite(), sf::Sprite() })
{
	// loading cursor texture
	if (!cursTexture.loadFromFile("./Sprites/scope.png"))
		std::cout << "[!] Failed to load cursor texture." << std::endl;
	else
	{
		window->setMouseCursorVisible(false);
		cursor->setTexture(cursTexture);
		cursor->setScale(0.035f, 0.035f);
		cursor->setOrigin(
			cursor->getTexture()->getSize().x / 2,
			cursor->getTexture()->getSize().y / 2);

		std::cout << "[I] Cursor texture loaded successfully." << std::endl;
	}

	// loading heart texture
	if (!heartTexture.loadFromFile("./Sprites/heart.png"))
		std::cout << "[!] Failed to load heart texture." << std::endl;
	else
	{
		heartTexture.setSmooth(true);
		std::cout << "[I] Heart texture loaded successfully." << std::endl;
	}

	for (int i = 0; i < health.size(); i++)
	{
		health[i].setTexture(heartTexture);
		health[i].setScale(0.035f, 0.035f);
		health[i].setPosition(sf::Vector2f(float(690 + i*35), 0.0f));
	}

	// TODO: LOAD FONT, END GAME SCREEN
	// Loading font
	if (!textFont.loadFromFile("./Fonts/Roboto-Thin.ttf"))
		std::cout << "[!] Failed to load font." << std::endl;
	else
	{
		endGameText.setFont(textFont);
		endGameText.setString("\t\tGAME OVER!\nPress SPACE to restart.");
		std::cout << "[I] Font loaded successfully." << std::endl;
		endGameText.setCharacterSize(32);
		endGameText.setPosition(sf::Vector2f(
			float(window->getSize().x / 2) - 150.0f,
			float(window->getSize().y / 2) - 50.0f));
	}
}

Game::~Game()
{
	delete window;
	for (auto t : targets)
		delete t;
	targets.clear();
}

// Helping function
float Game::clamp(float min, float max, float n) const
{
	if (n < min) n = min;
	else if (n > max) n = max;
	return n;
}

// Getters
sf::RenderWindow& Game::GetWindow() const
{
	return *window;
}

// Functions defenitions
void Game::update()
{
	sf::Event ev;

	sf::Vector2i mouse = sf::Mouse::getPosition(*window); // Mouse position
	// Getting events
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (ev.key.code == sf::Mouse::Button::Left && this->running) // Checking if player clicked on target
			{
				auto i = std::remove_if(targets.begin(), targets.end(), 
					[&](Target* t) { return t->GetSpr().getGlobalBounds().contains(float(mouse.x), float(mouse.y)); });
				if (i != targets.end())
				{
					if (fSpawnTimerMax > fSpawnTimerMin)
						fSpawnTimerMax -= 10.0f;
					targets.erase(i);
				}
			}
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Space && this->running == false)
			{
				for (auto& h : health) // restoring health
					h.setScale(0.035f, 0.035f);

				targets.clear(); // clearing targets vector
				fSpawnTimerMax = 500.0f; // setting start spawn timer value
				this->running = true;
			}
			break;
		default:
			break;
		}
	}

	// Setting cursor
	cursor->setPosition(sf::Vector2f(float(mouse.x), float(mouse.y)));

	if (!this->running) return;

	// Spawning new enemy in gaming zone if timer is up
	if (fSpawnTimer >= fSpawnTimerMax)
	{
		if (targets.size() <= nMaxTargets)
		{
			fSpawnTimer = 0.0f;
			sf::Vector2u winSize = this->window->getSize();
			Target* newTarget = new Target(sf::Vector2f(
				clamp(40.0f, winSize.x - 40.0f, float(rand() % winSize.x - 40.0f)),
				clamp(40.0f, winSize.y - 40.0f, float(rand() % winSize.y - 40.0f))
			));

			targets.push_back(newTarget);
		}
	}
	else fSpawnTimer += 0.1f;

	// if 
	auto i = std::remove_if(targets.begin(), targets.end(),
		[&](Target* t) { return t->scale < 0.0f; });

	if (i != targets.end())
	{
		targets.erase(i);
		for (int i = health.size() - 1; i >= 0; i--) // -health
		{
			if (health[i].getScale().x > 0.0f)
			{
				health[i].setScale(0.0f, 0.0f);
				break;
			}
		}

		if (std::count_if(health.begin(), health.end(), 
			[&](sf::Sprite s) { return s.getScale().x == 0.0f; }) == 3) // Checking if game is over
		{
			this->running = false;
		}
	}

	// Updating targets
	float delta = clock.restart().asSeconds();
	for (auto& t : targets)
		t->update(delta);
}

void Game::render() const
{
	window->clear(sf::Color(87, 89, 93, 255));

	// Draw sprites and other...
	for (const auto& t : targets)
		t->render(this->window);

	// Draw health
	for (const auto& h : health)
		window->draw(h);

	if (!this->running)
		window->draw(endGameText);

	// Render custom cursor
	window->draw(*cursor);

	window->display();
}
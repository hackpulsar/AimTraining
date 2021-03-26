#include "GameState.h"

GameState::GameState(GameDataRef data)
	:_data(data), cursor(new sf::Sprite), spawner(new Spawner(this->_data)),
	flash(new Flash(this->_data)), _state(GameStates::Playing), particleSystem(new ParticleSystem(this->_data))
{ }

GameState::~GameState()
{ }

void GameState::Init()
{
	this->cursor->setTexture(this->_data->assets.GetTexture("cursor"));
	this->cursor->setColor(std::get<0>(_colors[_data->settings.GetSetting("cursor color")]));

	this->_data->window.setMouseCursorVisible(false);
	cursor->setScale(0.035f, 0.035f);
	cursor->setOrigin(
		float(cursor->getTexture()->getSize().x / 2),
		float(cursor->getTexture()->getSize().y / 2));

	// Hearts
	for (int i = 0; i < hp; i++)
		health.push_back(sf::Sprite());
	for (int i = 0; i < health.size(); i++)
	{
		health[i].setTexture(this->_data->assets.GetTexture("heart"));
		health[i].setScale(0.035f, 0.035f);
		health[i].setPosition(sf::Vector2f(float(690 + i * 35), 0.0f));
	}

	// Starting spawning
	spawner->start();
}

void GameState::PollEvents()
{
	sf::Event ev;
	sf::Vector2i mouse = this->_data->input.GetMousePosition(this->_data->window); // Mouse position
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
				auto it = std::find_if(this->spawner->GetTargets().begin(), this->spawner->GetTargets().end(),
					[&](Target* t) { return t->GetSpr().getGlobalBounds().contains((float)mouse.x, (float)mouse.y); });
				if (it != this->spawner->GetTargets().end())
				{
					// Adding new particle (target death)
					this->particleSystem->AddParticle(
						{
							(*it)->GetSpr().getPosition(),				// position
							sf::Color(255, 255, 255, 255),				// color
							(*it)->GetSpr().getScale().x * 550.0f,		// radius
							1.5f,										// border thickness
							1.0f										// lifetime
						});

					auto i = std::remove_if(this->spawner->GetTargets().begin(), this->spawner->GetTargets().end(),
					[&](Target* t) { return t->GetSpr().getGlobalBounds().contains((float)mouse.x, (float)mouse.y); });

					if (i != this->spawner->GetTargets().end())
					{
						this->_data->assets.playSound("pop sound");
						this->_stats.AddClick(true);
						this->_stats.AddScore(10);

						this->spawner->DeleteTarget(i);
					}
				}
				else
				{
					this->_stats.AddClick(false);
				}
			}
			break;
		default:
			break;
		}
	}
}

void GameState::update(float delta)
{
	sf::Vector2i mouse = this->_data->input.GetMousePosition(this->_data->window);
	cursor->setPosition(sf::Vector2f(float(mouse.x), float(mouse.y))); // Setting cursor

	if (this->_state == GameStates::Playing)
	{
		// If target scale is less that 0.0f (that means that it is invisible) remove it and subtract one heart
		auto it = std::remove_if(this->spawner->GetTargets().begin(), this->spawner->GetTargets().end(),
			[&](Target* t) { return t->scale < 0.0f; });

		if (it != this->spawner->GetTargets().end())
		{
			this->spawner->DeleteTarget(it);
			--hp;
			this->_data->assets.playSound("hurt sound");
		}

		if (hp <= 0)
		{
			this->_state = GameStates::GameOver;
			this->_clock.restart();
		}

		// Updating Spawner
		this->spawner->update(delta);
		// Updating particles
		this->particleSystem->update(delta);
	}

	if (this->_state == GameStates::GameOver)
	{
		this->flash->show(delta);
		if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APEARS)
			this->_data->machine.AddState(StateRef(new GameOverScreen(this->_data, this->_stats)), true);
	}
}

void GameState::render() const
{
	this->_data->window.clear(sf::Color(87, 89, 93));
	this->spawner->render();

	// Draw health
	for (unsigned short int i = 0; i < hp; i++)
		this->_data->window.draw(health[i]);

	// Flash
	this->flash->render();

	// Particles
	this->particleSystem->render();

	this->_data->window.draw(*cursor); // Drawing cursor
	this->_data->window.display();
}

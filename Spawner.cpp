#include "Spawner.h"

int Spawner::clamp(int min, int max, int value) const
{
	if (value < min) value = min;
	else if (value > max) value = max;
	return value;
}

Spawner::Spawner(GameDataRef data)
	:_data(data), running(true)
{ }

Spawner::~Spawner()
{ }

std::vector<Target*>& Spawner::GetTargets()
{
	return this->targets;
}

void Spawner::DeleteTarget(std::vector<Target*>::iterator it)
{
	if (it != this->targets.end())
		this->targets.erase(it);
}

void Spawner::start()
{
	this->running = true;
	fSpawnTimerMax = 500.0f; // setting start spawn timer value
}

void Spawner::stop()
{
	this->running = false;
}

void Spawner::update(float delta)
{
	if (!this->running) return; // if spawner is not running don't update anything

	// Spawning new enemy in gaming zone if timer is up
	if (this->_clock.getElapsedTime().asMilliseconds() >= fSpawnTimerMax)
	{
		if (this->targets.size() <= nMaxTargets)
		{
			this->_clock.restart();
			sf::Vector2u winSize = this->_data->window.getSize();
			Target* newTarget = new Target(sf::Vector2f(
				this->clamp(40.0f, float(winSize.x - 40), float(rand() % winSize.x - 40.0f)),
				this->clamp(40.0f, float(winSize.y - 40), float(rand() % winSize.y - 40.0f))
			), this->_data->assets);

			this->targets.push_back(newTarget);

			if (fSpawnTimerMax > fSpawnTimerMin)
				fSpawnTimerMax -= 8.0f;
		}
	}

	// Updating targets
	for (auto& t : targets)
		t->update(delta);
}

void Spawner::render() const
{
	// Draw sprites and other
	for (const auto& t : targets)
		this->_data->window.draw(t->GetSpr());
}

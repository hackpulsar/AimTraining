#pragma once
#include <vector>
#include "Game.h"
#include <SFML/Graphics.hpp>

struct ParticleProps
{
	sf::Vector2f pos;
	sf::Color color;
	float radius = 10.0f;
	float size = 2.0f;
	float lifeTime = 1.0f;
};

class ParticleSystem
{
private:
	class Particle
	{
	private:
		sf::CircleShape _shape;
		sf::Clock _clock;
		ParticleProps _props;

		bool active = true;

	public:
		// Init
		Particle(ParticleProps props)
			:_props(props), _shape(sf::CircleShape(10))
		{
			// Copying color
			this->_shape.setFillColor(sf::Color(props.color.r, props.color.g, props.color.b, 0));

			this->_shape.setOutlineThickness(props.size);
			this->_shape.setOutlineColor(props.color);
			this->_shape.setPosition(props.pos);
			this->_shape.setRadius(props.radius);
			this->_shape.setOrigin(
				float(this->_shape.getRadius()),
				float(this->_shape.getRadius()));

			_clock.restart();
		}

		~Particle() { }

		// Getters
		sf::CircleShape& GetShape()
		{
			return this->_shape;
		}

		bool IsActive() const { return this->active; }

		// Functions
		void update(float delta)
		{
			if (!this->active) return;

			if (_clock.getElapsedTime().asSeconds() >= _props.lifeTime)
			{
				this->active = false;
			}

			auto clr = this->_props.color;
			this->_props.color = sf::Color(clr.r, clr.g, clr.b, sf::Uint8(clr.a - (4 + _props.lifeTime)));
			this->_shape.setOutlineColor(_props.color);
		}
	};

	GameDataRef _data;
	std::vector<Particle*> _particles;

public:
	ParticleSystem(GameDataRef data);
	~ParticleSystem();

	void AddParticle(ParticleProps props);

	// Functions
	void update(float delta);
	void render() const;

};


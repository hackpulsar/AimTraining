#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(GameDataRef data)
	:_data(data)
{ }

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::AddParticle(ParticleProps props)
{
	_particles.push_back(new Particle(props));
}

void ParticleSystem::update(float delta)
{
	auto it = std::remove_if(_particles.begin(), _particles.end(), 
		[](Particle *p) { return p->GetShape().getOutlineColor().a == 0 || p->IsActive() == false; });

	if (it != _particles.end())
	{
		_particles.erase(it);
	}

	// Update particles
	for (auto& p : _particles)
		p->update(delta);
}

void ParticleSystem::render() const
{
	for (const auto& p : _particles)
		this->_data->window.draw(p->GetShape());
}

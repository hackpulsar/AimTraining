#include "Target.h"

Target::Target(sf::Vector2f pos, const AssetManager& manager)
{
	// Setting sprite
	this->spr.setTexture(manager.GetTexture("target"));
	this->spr.setScale(this->scale, this->scale);
	this->spr.setPosition(pos);
	this->spr.setOrigin(
		float(this->spr.getTexture()->getSize().x / 2),
		float(this->spr.getTexture()->getSize().y / 2));
}

Target::~Target()
{ }

sf::Sprite& Target::GetSpr()
{
	return this->spr;
}

// Functions
void Target::update(float delta)
{
	this->scale += this->step * delta;
	if (this->scale >= 0.045f)
		this->step *= -1;
	this->spr.setScale(this->scale, this->scale);
}

void Target::render(sf::RenderTarget* target) const
{
	target->draw(this->spr);
}
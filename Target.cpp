#include "Target.h"

Target::Target(sf::Vector2f pos)
{
	// loading texture
	if (!this->texture.loadFromFile("./Sprites/target.png"))
		std::cout << "[!] Failed to load texture." << std::endl;
	else
	{
		this->texture.setSmooth(true);
		this->spr.setTexture(this->texture);
	}
	
	// setting sprite
	this->spr.setScale(this->scale, this->scale);
	this->spr.setPosition(pos);
	this->spr.setOrigin(
		this->spr.getTexture()->getSize().x / 2,
		this->spr.getTexture()->getSize().y / 2);
}

Target::~Target()
{

}

sf::Sprite Target::GetSpr() const
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
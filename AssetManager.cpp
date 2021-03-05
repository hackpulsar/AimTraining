#include "AssetManager.h"

AssetManager::AssetManager() { }
AssetManager::~AssetManager()
{
	this->_buffers.clear();
}

void AssetManager::PlaySound(std::string name)
{
	this->_sounds.at(name).play();
}

void AssetManager::LoadTexture(std::string name, std::string filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
		std::cout << "[!] Failed to load texture " << filename << std::endl;
	else
	{
		texture.setSmooth(true);
		this->_textures[name] = texture;
	}
}

void AssetManager::LoadFont(std::string name, std::string filename)
{
	sf::Font font;
	if (!font.loadFromFile(filename))
		std::cout << "[!] Failed to load texture " << filename << std::endl;
	else
	{
		this->_fonts[name] = font;
	}
}

void AssetManager::LoadSound(std::string name, std::string filename)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	sf::Sound sound;
	if (!buffer->loadFromFile(filename))
		std::cout << "[!] Failed to load texture " << filename << std::endl;
	else
	{
		sound.setBuffer(*buffer);
		sound.setVolume(50.0f);
		this->_buffers[name] = std::move(buffer);
		this->_sounds[name] = sound;
	}
}

const sf::Texture& AssetManager::GetTexture(std::string name) const
{
	return this->_textures.at(name);
}

const sf::Font& AssetManager::GetFont(std::string name) const
{
	return this->_fonts.at(name);
}

const sf::Sound& AssetManager::GetSound(std::string name) const
{
	return this->_sounds.at(name);
}

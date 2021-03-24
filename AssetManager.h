#pragma once

#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class AssetManager
{
private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::SoundBuffer*> _buffers;
	std::map<std::string, sf::Sound> _sounds;
public:
	AssetManager();
	~AssetManager();

	void playSound(std::string name);

	// Loading
	void LoadTexture(std::string name, std::string filename);
	void LoadFont(std::string name, std::string filename);
	void LoadSound(std::string name, std::string filename);

	// Getters
	const sf::Texture& GetTexture(std::string name) const;
	const sf::Font& GetFont(std::string name) const;
	const sf::Sound& GetSound(std::string name) const;
};


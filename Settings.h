#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <Windows.h>
#include <iostream>

class Colors
{
private:
	const std::vector<sf::Color> clrs { sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::Blue };
	const std::vector<std::string> clrs_names { "Green", "Red", "Yellow", "Blue" };
	int active_i = 0;

public:
	Colors() { }
	~Colors() { }

	std::pair<sf::Color, std::string> operator[](unsigned short int index)
	{
		return std::make_pair(this->clrs[index], clrs_names[index]);
	}

	std::pair<sf::Color, std::string> GetActive() const
	{
		return  std::make_pair(this->clrs[active_i], clrs_names[active_i]);
	}

	std::pair<sf::Color, std::string> Next()
	{
		active_i++;
		if (active_i > clrs.size() - 1)
			active_i = 0;
		return this->GetActive();
	}

	std::pair<sf::Color, std::string> Previous()
	{
		active_i--;
		if (active_i < 0)
			active_i = clrs.size() - 1;
		return this->GetActive();
	}
};

class Settings
{
private:
	std::map<std::string, DWORD> _sets;
	LPCWSTR companySubKey = L"SOFTWARE\\Aim Training";

	// Registry manipulation functions
	HKEY OpenRegKey(HKEY hRootKey, LPCWSTR strSubKey);
	void SetRegVelue(HKEY hKey, LPCWSTR lpVal, DWORD data);
	DWORD GetRegValue(HKEY hKey, LPCWSTR lpValue);

public:
	// Init
	Settings();
	~Settings();

	std::pair<sf::Color, std::string> curs_color;

	void SetSetting(std::string name, DWORD new_content);
	void AddSetting(std::string name, DWORD content);
	void Load();
	void Save();
	DWORD GetSetting(std::string name);
};


#pragma once
#include <iostream>

struct Info 
{
	// Score
	unsigned int score = 0;

	// Accuracy data
	unsigned int clicked = 0;
	unsigned int correct_clicks = 0;
};

class Statistic
{
private:
	Info _info;

public:
	Statistic();
	~Statistic();

	// Setters (rather adders lol)
	void AddClick(bool correct);
	void AddScore(unsigned int value);

	// Getters
	Info GetInfo() const;
	double GetAccuracy() const;
	unsigned int GetScore() const;

};


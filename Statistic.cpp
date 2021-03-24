#include "Statistic.h"

Statistic::Statistic()
{ }

Statistic::~Statistic()
{ }

void Statistic::AddClick(bool correct)
{
	this->_info.clicked++;
	if (correct)
		this->_info.correct_clicks++;
}

void Statistic::AddScore(unsigned int value)
{
	this->_info.score += value;
}

Info Statistic::GetInfo() const
{
	return this->_info;
}

double Statistic::GetAccuracy() const
{
	if (this->_info.clicked == 0) return 0.0;
	double res = (double(this->_info.correct_clicks) / double(this->_info.clicked)) * 100.0;
	return res;
}

unsigned int Statistic::GetScore() const
{
	return this->_info.score;
}

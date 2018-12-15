#pragma once
#include"MultiOption.h"

PsyTest::MultiOption::MultiOption(std::string name, std::string text, std::string image)
{
	this->name = name;
	this->text = text;
	this->img = image;
}

int PsyTest::MultiOption::count_points()
{
	int points = 0;
	for (int i = 0; i < answers.size(); ++i)
	{
		if (answers[i].second)
			points += answers[i].first.points;
	}
	return points;
}

void PsyTest::MultiOption::add_answer(std::string text, int points)
{
	answer tmp;
	tmp.text = text;
	tmp.points = points;
	std::pair<answer, bool> p;
	p.first = tmp;
	p.second = false;
	this->answers.push_back(p);
}

void PsyTest::MultiOption::remove_answer(int i)
{
	if (i < 0 || i >= answers.size())
		return;
	answers.erase(answers.begin() + i);
}
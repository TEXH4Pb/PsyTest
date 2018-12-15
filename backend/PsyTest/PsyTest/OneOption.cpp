#pragma once
#include"OneOption.h"

PsyTest::OneOption::OneOption(std::string name, std::string text, std::string image)
{
	this->name = name;
	this->text = text;
	this->img = image;
}

int PsyTest::OneOption::count_points()
{
	return answers[selection].points;
}

void PsyTest::OneOption::add_answer(std::string text, int points)
{
	answer tmp;
	tmp.text = text;
	tmp.points = points;
	this->answers.push_back(tmp);
}

void PsyTest::OneOption::remove_answer(int i)
{
	if (i < 0 || i >= answers.size())
		return;
	answers.erase(answers.begin() + i);
}

bool PsyTest::OneOption::selection_set(int i)
{
	if (i < 0 || i >= answers.size())
	{
		return false;
	}
	selection = i;
	return true;
}
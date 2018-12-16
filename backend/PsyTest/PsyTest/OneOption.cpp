#pragma once
#include"OneOption.h"

PsyTest::OneOption::OneOption(std::string name, std::string text, std::string image)
{
	this->name = name;
	this->text = text;
	this->selection = -1;

	if (image != "")
	{
		std::ifstream in(image, std::ios::binary | std::ios::ate);
		if (!in.is_open())
		{
			this->img = nullptr;
			this->img_size = 0;
		}
		else
		{
			this->img_size = in.tellg();
			in.seekg(std::ios::beg);
			this->img = (char*)malloc(this->img_size);
			in.read(this->img, this->img_size);
			in.close();
		}
	}
	else
	{
		this->img = nullptr;
		this->img_size = 0;
	}
}

PsyTest::OneOption::OneOption(const OneOption & obj)
{
	this->name = obj.name;
	this->text = obj.text;
	this->selection = obj.selection;
	this->img_size = obj.img_size;
	if (this->img_size > 0)
	{
		this->img = new char[this->img_size];
		for (int i = 0; i < this->img_size; ++i)
		{
			this->img[i] = obj.img[i];
		}
	}
	else
		this->img = nullptr;
	this->answers = obj.answers;
}

PsyTest::OneOption::~OneOption()
{
	delete[] this->img;
}

PsyTest::Question* PsyTest::OneOption::clone()
{
	return new OneOption(*this);
}

int PsyTest::OneOption::count_points()
{
	if (this->selection < 0)
		throw std::logic_error("Question has no selected answer.");
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

void PsyTest::OneOption::write(std::ofstream& file)
{
	if (!file.is_open())
		return;

	//запись типа вопроса
	QuestionType a = QuestionType::OneOpt;
	file.write((char*)&a, sizeof(a));

	size_t t;
	t = this->name.size();
	//запись длины строки
	file.write((char*)&t, sizeof(t));
	//запись символов строки
	file.write(this->name.c_str(), t);

	t = this->text.size();
	file.write((char*)&t, sizeof(t));
	file.write(this->text.c_str(), t);

	//запись размеров изображения
	file.write((char*)&this->img_size, sizeof(this->img_size));
	//запись байтов изображения
	if (this->img_size)
		file.write(this->img, this->img_size);

	//запись кол-ва ответов с последующей записью всех ответов
	t = this->answers.size();
	file.write((char*)&t, sizeof(t));
	for (int i = 0; i < this->answers.size(); ++i)
	{
		//запись текста ответа
		t = this->answers[i].text.size();
		file.write((char*)&t, sizeof(t));
		file.write(this->answers[i].text.c_str(), t);
		//запись баллов за ответ
		t = this->answers[i].points;
		file.write((char*)&t, sizeof(t));
	}
}

bool PsyTest::OneOption::read(std::ifstream& file)
{
	if(!file.is_open())
		return false;

	size_t t = 0;
	char* buf;

	file.read((char*)&t, sizeof(t));
	buf = new char[t + 1];
	file.read(buf, t);
	buf[t] = '\0';
	this->name = buf;

	file.read((char*)&t, sizeof(t));
	buf = new char[t + 1];
	file.read(buf, t);
	buf[t] = '\0';
	this->text = buf;

	file.read((char*)&this->img_size, sizeof(this->img_size));
	if (this->img_size)
	{
		this->img = new char[this->img_size];
		file.read(this->img, this->img_size);
	}
	else
		this->img = nullptr;

	this->answers.empty();
	file.read((char*)&t, sizeof(t));
	for (size_t i = 0, l; i < t; ++i)
	{
		file.read((char*)&l, sizeof(l));
		buf = new char[l + 1];;
		file.read(buf, l);
		buf[l] = '\0';
		file.read((char*)&l, sizeof(l));
		this->add_answer(buf, l);
	}
	return true;
}
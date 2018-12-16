#pragma once
#include"MultiOption.h"

PsyTest::MultiOption::MultiOption(std::string name, std::string text, std::string image)
{
	this->name = name;
	this->text = text;
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

PsyTest::MultiOption::MultiOption(const MultiOption & obj)
{
	this->name = obj.name;
	this->text = obj.text;
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

PsyTest::MultiOption::~MultiOption()
{
	delete[] this->img;
}

PsyTest::Question* PsyTest::MultiOption::clone()
{
	return new MultiOption(*this);
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

void PsyTest::MultiOption::write(std::ofstream& file)
{
	if (!file.is_open())
		return;

	//запись типа вопроса
	QuestionType a = QuestionType::MultiOpt;
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
		t = this->answers[i].first.text.size();
		file.write((char*)&t, sizeof(t));
		file.write(this->answers[i].first.text.c_str(), t);
		//запись баллов за ответ
		t = this->answers[i].first.points;
		file.write((char*)&t, sizeof(t));
	}
}

bool PsyTest::MultiOption::read(std::ifstream& file)
{
	if (!file.is_open())
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
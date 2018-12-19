#pragma once
#include"Result.h"

PsyTest::Result::Result(std::string title, std::string text, int to, int from, std::string image)
{
	this->title = title;
	this->text = text;
	this->to = to;
	this->from = from;
	this->occurrence = 0;

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
			this->img = new char[this->img_size];
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

PsyTest::Result::Result(const Result& obj)
{
	this->from = obj.from;
	this->to = obj.to;
	this->occurrence = obj.occurrence;
	this->title = obj.title;
	this->text = obj.text;
	this->img_size = obj.img_size;
	if (this->img_size > 0)
	{
		this->img = new char[this->img_size];
		for (unsigned long i = 0; i < this->img_size; ++i)
		{
			this->img[i] = obj.img[i];
		}
	}
	else
		this->img = nullptr;
}

PsyTest::Result::~Result()
{
	delete[] this->img;
}

void PsyTest::Result::write(std::ofstream & file)
{
	if (!file.is_open())
		return;

	size_t t;
	t = this->title.size();
	file.write((char*)&t, sizeof(t));
	file.write(this->title.c_str(), t);

	t = this->text.size();
	file.write((char*)&t, sizeof(t));
	file.write(this->text.c_str(), t);

	file.write((char*)&this->img_size, sizeof(this->img_size));
	if (this->img_size)
		file.write(this->img, this->img_size);

	file.write((char*)&this->from, sizeof(this->from));
	file.write((char*)&this->to, sizeof(this->to));
	file.write((char*)&this->occurrence, sizeof(this->occurrence));
}

bool PsyTest::Result::read(std::ifstream & file)
{
	if (!file.is_open())
		return false;

	size_t t = 0;
	char* buf;

	file.read((char*)&t, sizeof(t));
	buf = new char[t + 1];
	file.read(buf, t);
	buf[t] = '\0';
	this->title = buf;

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

	file.read((char*)&this->from, sizeof(this->from));
	file.read((char*)&this->to, sizeof(this->to));
	file.read((char*)&this->occurrence, sizeof(this->occurrence));
}

void PsyTest::Result::to_text(std::string filename)
{
	std::ofstream o(filename);
	if (!o.is_open())
		return;
	o << this->title << "\n\n";
	o << this->text;
	o.close();
}

void PsyTest::Result::occurrence_set(int i)
{
	if (i >= 0)
		occurrence = i;
}

bool PsyTest::Result::check(int points)
{
	if (points >= this->from && points <= this->to)
		return true;
	return false;
}

bool PsyTest::Result::set_image(std::string filename)
{
	std::ifstream in(filename, std::ios::binary | std::ios::ate);
	if (!in.is_open())
		return false;
	this->img_size = in.tellg();
	in.seekg(std::ios::beg);
	in.read(this->img, this->img_size);
	in.close();
}

bool PsyTest::Result::put_image(std::string filename)
{
	std::ofstream out(filename, std::ios::binary | std::ios::trunc);
	if (!out.is_open())
		return false;
	out.write(this->img, this->img_size);
	out.close();
	return true;
}
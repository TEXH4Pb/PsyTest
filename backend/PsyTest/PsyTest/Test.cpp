#pragma once
#include"Test.h"

PsyTest::Test::Test(std::string title, std::string description, std::string image)
{
	this->title = title;
	this->description = description;
	this->passedTimes = 0;

    if (!image.empty())
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

PsyTest::Test::Test(const Test & obj)
{
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

	this->title = obj.title;
	this->description = obj.description;
	this->passedTimes = obj.passedTimes;
	this->results = obj.results;

	for (int i = 0; i < this->questions.size(); ++i)
	{
		delete this->questions[i];
	}
	this->questions.clear();
	for (int i = 0; i < obj.questions.size(); ++i)
	{
		this->questions.push_back(obj.questions[i]->clone());
	}
}

PsyTest::Test::~Test()
{
	delete[] this->img;
	for (int i = 0; i < this->questions.size(); ++i)
	{
		delete this->questions[i];
	}
}

void PsyTest::Test::save(std::string filename)
{
	std::ofstream out(filename, std::ios::binary);
	if (!out.is_open())
		throw std::invalid_argument("Unable to open file");

	size_t t;

	t = this->title.size();
	out.write((char*)&t, sizeof(t));
	out.write(this->title.c_str(), t);

	t = this->description.size();
	out.write((char*)&t, sizeof(t));
	out.write(this->description.c_str(), t);

	out.write((char*)&this->passedTimes, sizeof(this->passedTimes));

	out.write((char*)&this->img_size, sizeof(this->img_size));
	if (this->img_size)
		out.write(this->img, this->img_size);

	t = this->questions.size();
	out.write((char*)&t, sizeof(t));
	for (int i = 0; i < t; ++i)
	{
		this->questions[i]->write(out);
	}

	t = this->results.size();
	out.write((char*)&t, sizeof(t));
	for (int i = 0; i < t; ++i)
	{
		this->results[i].write(out);
	}
}

void PsyTest::Test::load(std::string filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.is_open())
		throw std::invalid_argument("Unable to open file");

	size_t t = 0;
	char* buf;
	QuestionType qt;
	MultiOption mtmp;
	OneOption otmp;
	Result rtmp;

	in.read((char*)&t, sizeof(t));
	buf = new char[t + 1];
	in.read(buf, t);
	buf[t] = '\0';
	this->title = buf;

	in.read((char*)&t, sizeof(t));
	buf = new char[t + 1];
	in.read(buf, t);
	buf[t] = '\0';
	this->description = buf;

	in.read((char*)&this->passedTimes, sizeof(this->passedTimes));

	in.read((char*)&this->img_size, sizeof(this->img_size));
	if (this->img_size)
	{
		this->img = new char[this->img_size];
		in.read(this->img, this->img_size);
	}
	else
		this->img = nullptr;

	in.read((char*)&t, sizeof(t));
	this->questions.clear();
	for (int i = 0; i < t; ++i)
	{
		in.read((char*)&qt, sizeof(qt));
		switch (qt)
		{
		case QuestionType::OneOpt:
			otmp.read(in);
			this->questions.push_back(otmp.clone());
			break;
		case QuestionType::MultiOpt:
			mtmp.read(in);
			this->questions.push_back(mtmp.clone());
			break;
		default:
			break;
		}
	}

	in.read((char*)&t, sizeof(t));
	this->results.clear();
	for (int i = 0; i < t; ++i)
	{
		rtmp.read(in);
		this->results.push_back(rtmp);
	}
}

int PsyTest::Test::get_result()
{
	int tmp = 0;
	for (int i = 0; i < this->questions.size(); ++i)
	{
        try
        {
            tmp += this->questions[i]->count_points();
        }
        catch(std::logic_error e)
        {
            throw std::logic_error(std::to_string(i + 1));
        }
	}

	for (int i = 0; i < this->results.size(); ++i)
	{
		if (this->results[i].check(tmp))
        {
            this->results[i].occurrence_set(this->results[i].occurrence_get()+1);
			return i;
        }
	}
	return -1;
}

void PsyTest::Test::passedTimes_set(int i)
{
	if (i >= 0)
		this->passedTimes = i;
	return;
}

bool PsyTest::Test::set_image(std::string filename)
{
    if(filename.empty())
    {
        this->img_size = 0;
        if(this->img)
        {
            delete[] this->img;
            this->img = nullptr;
        }
    }
	std::ifstream in(filename, std::ios::binary | std::ios::ate);
	if (!in.is_open())
		return false;
	this->img_size = in.tellg();
	in.seekg(std::ios::beg);
    delete[] this->img;
    this->img = new char[this->img_size];
	in.read(this->img, this->img_size);
	in.close();
    return true;
}

bool PsyTest::Test::put_image(std::string filename)
{
    if(this->img_size == 0)
        return false;
	std::ofstream out(filename, std::ios::binary | std::ios::trunc);
	if (!out.is_open())
		return false;
	out.write(this->img, this->img_size);
	out.close();
	return true;
}

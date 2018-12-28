#pragma once
#include "Question.h"

bool PsyTest::Question::set_image(std::string filename)
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
	if(!in.is_open())
		return false;
	this->img_size = in.tellg();
	in.seekg(std::ios::beg);
    delete[] this->img;
    this->img = new char[this->img_size];
	in.read(this->img, this->img_size);
	in.close();
    return true;
}

bool PsyTest::Question::put_image(std::string filename)
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

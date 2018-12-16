#pragma once
#include "Question.h"

bool PsyTest::Question::set_image(std::string filename)
{
	std::ifstream in(filename, std::ios::binary | std::ios::ate);
	if(!in.is_open())
		return false;
	this->img_size = in.tellg();
	in.seekg(std::ios::beg);
	in.read(this->img, this->img_size);
	in.close();
}

bool PsyTest::Question::put_image(std::string filename)
{
	std::ofstream out(filename, std::ios::binary | std::ios::trunc);
	if (!out.is_open())
		return false;
	out.write(this->img, this->img_size);
	out.close();
	return true;
}

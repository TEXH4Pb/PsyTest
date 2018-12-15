#pragma once
#include"PsyTest.h"
#include<vector>

class PsyTest::Test
{
public:
	Test();
	~Test();
	void save(std::string filename);
	void load(std::string filename);
	Result get_result();
	int passedTimes_get() { return passedTimes; }
	bool passedTimes_set();

	std::string title;
	std::string description;
	std::vector<Question*> questions;
	std::vector<Result> results;
protected:
	int passedTimes;
};

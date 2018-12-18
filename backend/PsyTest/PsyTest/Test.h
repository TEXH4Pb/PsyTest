#pragma once
#include"PsyTest.h"
#include"Result.h"
#include"Question.h"
#include"MultiOption.h"
#include"OneOption.h"

class PsyTest::Test
{
public:
	Test(std::string title = "", std::string description = "", std::string image = "");
	Test(const Test& obj);
	~Test();
	void save(std::string filename);
	void load(std::string filename);
	int get_result();
	int passedTimes_get() { return passedTimes; }
	void passedTimes_set(int i);
	bool set_image(std::string filename);
	//сохраняет изображение на диск отдельным файлом
	bool put_image(std::string filename);

	std::string title;
	std::string description;
	std::vector<Question*> questions;
	std::vector<Result> results;
protected:
	//кол-во прохождений
	int passedTimes;
	//размер изображения
	unsigned long img_size;
	//байты изображения
	char* img;
};

#pragma once
#include"PsyTest.h"

class PsyTest::Question
{
public:
	virtual ~Question() = default;
	//ѕодсчЄт кол-ва баллов за все выбранные ответы
	virtual int count_points() = 0;
	virtual void add_answer(std::string text, int points) = 0;
	virtual void remove_answer(int i) = 0;
	virtual void write(std::ofstream& file) = 0;
	virtual bool read(std::ifstream& file) = 0;
	bool set_image(std::string filename);
	//сохран€ет изображение на диск отдельным файлом
	bool put_image(std::string filename);
	virtual Question* clone() = 0;

	//текст вопроса
	std::string text;
	//размер изображени€
	unsigned long img_size;
	//байты изображени€
	char* img;
};
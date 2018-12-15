#pragma once
#include"PsyTest.h"
#include<vector>

class PsyTest::Question
{
public:
	virtual ~Question() = default;
	//Подсчёт кол-ва баллов за все выбранные ответы
	virtual int count_points() = 0;
	virtual void add_answer(std::string text, int points) = 0;
	virtual void remove_answer(int i) = 0;
	virtual void write(std::ofstream file) = 0;
	virtual bool read(std::ifstream file) = 0;

	//имя вопроса для отображения в редакторе
	std::string name;
	//текст вопроса
	std::string text;
	//адрес изображения
	std::string img;
};
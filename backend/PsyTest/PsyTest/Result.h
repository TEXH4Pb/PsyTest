#pragma once
#include"PsyTest.h"
#include<string>
#include<vector>

class PsyTest::Result
{
	Result(std::string title = "", std::string text = "", int to = 0, int from = 0);
	~Result() = default;
	//Запись объекта в файл в бинарном режиме
	void write(std::ofstream file);
	//Чтение объекта из файла в бинарном режиме
	bool read(std::ifstream file);
	void to_text(std::string filename);
	inline int occurrence_get() { return occurrence; }
	void occurrence_set(int i);
	//Проверка на соответствие кол-ва баллов диапазону результата
	bool check(int points);

	std::string title;
	std::string text;
	//С какого числа начинается диапазон подходящих баллов (включительно)
	int from;
	//Каким числом заканчивается диапазон подходящих баллов (включительно)
	int to;
private:
	int occurrence;
};
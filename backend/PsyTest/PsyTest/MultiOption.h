#pragma once
#include"Question.h"

//Вопрос с возможностью выбрать несколько вариантов ответа
class PsyTest::MultiOption : PsyTest::Question
{
public:
	MultiOption(std::string name = "", std::string text = "", std::string image = "");
	~MultiOption() = default;
	//Подсчёт кол-ва баллов за все выбранные ответы
	int count_points();
	void add_answer(std::string text, int points);
	void remove_answer(int i);
	//Запись объекта в файл в бинарном режиме
	void write(std::ofstream file);
	//Чтение объекта из файла в бинарном режиме
	bool read(std::ifstream file);
	std::vector<std::pair<answer, bool>> answers;
};
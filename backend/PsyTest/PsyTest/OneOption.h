#pragma once
#include"Question.h"

//Вопрос с возможностью выбрать только один вариант ответа
class PsyTest::OneOption : public PsyTest::Question
{
public:
	explicit OneOption(std::string name = "", std::string text = "", std::string image = "");
	OneOption(const OneOption& obj);
	~OneOption();
	Question* clone();
	//Подсчёт кол-ва баллов за все выбранные ответы
	int count_points();
	void add_answer(std::string text, int points);
	void remove_answer(int i);
	inline int selection_get() { return selection; };
	bool selection_set(int i);
	//Запись объекта в файл в бинарном режиме
	void write(std::ofstream& file);
	//Чтение объекта из файла в бинарном режиме
	bool read(std::ifstream& file);
	std::vector<answer> answers;
protected:
	//Номер выбранного варианта ответа
	int selection;
};
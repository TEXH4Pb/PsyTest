#pragma once
#include"PsyTest.h"

class PsyTest::Result
{
public:
	explicit Result(std::string title = "", std::string text = "", int to = 0, int from = 0, std::string image = "");
	Result(const Result& obj);
	~Result();
	//Запись объекта в файл в бинарном режиме
	void write(std::ofstream& file);
	//Чтение объекта из файла в бинарном режиме
	bool read(std::ifstream& file);
	//запись результата в текстовый файл
	void to_text(std::string filename);
	inline int occurrence_get() { return occurrence; }
	void occurrence_set(int i);
	//Проверка на соответствие кол-ва баллов диапазону результата
	bool check(int points);
	bool set_image(std::string filename);
	//сохраняет изображение на диск отдельным файлом
	bool put_image(std::string filename);

	std::string title;
	std::string text;
	//С какого числа начинается диапазон подходящих баллов (включительно)
	int from;
	//Каким числом заканчивается диапазон подходящих баллов (включительно)
	int to;
protected:
	//размер изображения
	unsigned long img_size;
	//байты изображения
	char* img;
	//сколько раз встречался этот результат
	int occurrence;
};
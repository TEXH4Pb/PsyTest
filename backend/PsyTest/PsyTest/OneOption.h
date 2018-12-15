#pragma once
#include"Question.h"

//������ � ������������ ������� ������ ���� ������� ������
class PsyTest::OneOption : PsyTest::Question
{
public:
	OneOption(std::string name = "", std::string text = "", std::string image = "");
	~OneOption() = default;
	//������� ���-�� ������ �� ��� ��������� ������
	int count_points();
	void add_answer(std::string text, int points);
	void remove_answer(int i);
	inline int selection_get() { return selection; };
	bool selection_set(int i);
	//������ ������� � ���� � �������� ������
	void write(std::ofstream file);
	//������ ������� �� ����� � �������� ������
	bool read(std::ifstream file);
protected:
	std::vector<answer> answers;
	//����� ���������� �������� ������
	int selection;
};
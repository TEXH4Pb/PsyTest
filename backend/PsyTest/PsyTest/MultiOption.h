#pragma once
#include"Question.h"

//������ � ������������ ������� ��������� ��������� ������
class PsyTest::MultiOption : PsyTest::Question
{
public:
	MultiOption(std::string name = "", std::string text = "", std::string image = "");
	~MultiOption() = default;
	//������� ���-�� ������ �� ��� ��������� ������
	int count_points();
	void add_answer(std::string text, int points);
	void remove_answer(int i);
	//������ ������� � ���� � �������� ������
	void write(std::ofstream file);
	//������ ������� �� ����� � �������� ������
	bool read(std::ifstream file);
	std::vector<std::pair<answer, bool>> answers;
};
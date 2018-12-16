#pragma once
#include"Question.h"

//������ � ������������ ������� ������ ���� ������� ������
class PsyTest::OneOption : public PsyTest::Question
{
public:
	explicit OneOption(std::string name = "", std::string text = "", std::string image = "");
	OneOption(const OneOption& obj);
	~OneOption();
	Question* clone();
	//������� ���-�� ������ �� ��� ��������� ������
	int count_points();
	void add_answer(std::string text, int points);
	void remove_answer(int i);
	inline int selection_get() { return selection; };
	bool selection_set(int i);
	//������ ������� � ���� � �������� ������
	void write(std::ofstream& file);
	//������ ������� �� ����� � �������� ������
	bool read(std::ifstream& file);
	std::vector<answer> answers;
protected:
	//����� ���������� �������� ������
	int selection;
};
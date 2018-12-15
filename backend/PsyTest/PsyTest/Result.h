#pragma once
#include"PsyTest.h"
#include<string>
#include<vector>

class PsyTest::Result
{
	Result(std::string title = "", std::string text = "", int to = 0, int from = 0);
	~Result() = default;
	//������ ������� � ���� � �������� ������
	void write(std::ofstream file);
	//������ ������� �� ����� � �������� ������
	bool read(std::ifstream file);
	void to_text(std::string filename);
	inline int occurrence_get() { return occurrence; }
	void occurrence_set(int i);
	//�������� �� ������������ ���-�� ������ ��������� ����������
	bool check(int points);

	std::string title;
	std::string text;
	//� ������ ����� ���������� �������� ���������� ������ (������������)
	int from;
	//����� ������ ������������� �������� ���������� ������ (������������)
	int to;
private:
	int occurrence;
};
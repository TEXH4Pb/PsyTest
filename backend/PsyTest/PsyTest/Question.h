#pragma once
#include"PsyTest.h"

class PsyTest::Question
{
public:
	virtual ~Question() = default;
	//������� ���-�� ������ �� ��� ��������� ������
	virtual int count_points() = 0;
	virtual void add_answer(std::string text, int points) = 0;
	virtual void remove_answer(int i) = 0;
	virtual void write(std::ofstream& file) = 0;
	virtual bool read(std::ifstream& file) = 0;
	bool set_image(std::string filename);
	//��������� ����������� �� ���� ��������� ������
	bool put_image(std::string filename);
	virtual Question* clone() = 0;

	//����� �������
	std::string text;
	//������ �����������
	unsigned long img_size;
	//����� �����������
	char* img;
};
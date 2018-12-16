#pragma once
#include"PsyTest.h"

class PsyTest::Result
{
public:
	explicit Result(std::string title = "", std::string text = "", int to = 0, int from = 0, std::string image = "");
	Result(const Result& obj);
	~Result();
	//������ ������� � ���� � �������� ������
	void write(std::ofstream& file);
	//������ ������� �� ����� � �������� ������
	bool read(std::ifstream& file);
	//������ ���������� � ��������� ����
	void to_text(std::string filename);
	inline int occurrence_get() { return occurrence; }
	void occurrence_set(int i);
	//�������� �� ������������ ���-�� ������ ��������� ����������
	bool check(int points);
	bool set_image(std::string filename);
	//��������� ����������� �� ���� ��������� ������
	bool put_image(std::string filename);

	std::string title;
	std::string text;
	//� ������ ����� ���������� �������� ���������� ������ (������������)
	int from;
	//����� ������ ������������� �������� ���������� ������ (������������)
	int to;
protected:
	//������ �����������
	unsigned long img_size;
	//����� �����������
	char* img;
	//������� ��� ���������� ���� ���������
	int occurrence;
};
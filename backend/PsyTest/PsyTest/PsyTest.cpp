#include "PsyTest.h"
#include"MultiOption.h"
#include"OneOption.h"
using namespace PsyTest;

OneOption* PsyTest::convertToOneOption(MultiOption obj)
{
	OneOption* r = new OneOption();
	answer tmp;

	r->text = obj.text;
	r->img_size = obj.img_size;
	for (int i = 0; i < obj.answers.size(); ++i)
	{
		r->add_answer(obj.answers[i].first);
	}
	if (r->img_size > 0)
	{
		r->img = new char[r->img_size];
		for (int i = 0; i < r->img_size; ++i)
			r->img[i] = obj.img[i];
	}
	else
		r->img = nullptr;

	return r;
}

MultiOption* PsyTest::convertToMultiOption(OneOption obj)
{
	MultiOption* r = new MultiOption();
	answer tmp;

	r->text = obj.text;
	r->img_size = obj.img_size;
	for (int i = 0; i < obj.answers.size(); ++i)
	{
		r->add_answer(obj.answers[i]);
	}
	if (r->img_size > 0)
	{
		r->img = new char[r->img_size];
		for (int i = 0; i < r->img_size; ++i)
			r->img[i] = obj.img[i];
	}
	else
		r->img = nullptr;

	return r;
}

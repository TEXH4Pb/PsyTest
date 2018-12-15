#pragma once
#include<string>
namespace PsyTest
{
	enum QuestionType
	{
		MultiOption,
		OneOption
	};
	struct answer
	{
		std::string text;
		int points;
	};
	class Test;
	class Question;
	class MultiOption;
	class OneOption;
	class Result;
}
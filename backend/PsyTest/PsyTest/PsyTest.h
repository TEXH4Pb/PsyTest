#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<exception>

namespace PsyTest
{
	enum QuestionType
	{
		MultiOpt,
		OneOpt
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

	OneOption* convertToOneOption(MultiOption obj);
	MultiOption* convertToMultiOption(OneOption obj);
}
#include "std_lib_facilities.h"
#pragma once

class Token {
public:
	char kind;
	double value;
	std::string char_value;
	Token(char ch);
	Token(char ch, double val);
	Token(char ch, double val, std::string string_val);
	Token* get();
};
#include "Token.h"
#pragma once

class TokenStream {
private:
	bool full;
	Token buffer;
public:
	TokenStream();
	Token get();
	void putback(Token t);
	std::string equasion;
};
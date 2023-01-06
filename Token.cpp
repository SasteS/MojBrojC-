#include "Token.h"

Token::Token(char ch) : kind(ch), value(0), char_value("") {}

Token::Token(char ch, double val) : kind(ch), value(val), char_value("") {}

Token::Token(char ch, double val, std::string string_val) : kind(ch), value(val), char_value(string_val) {}

Token* Token::get() { return this; }
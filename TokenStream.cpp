#include "TokenStream.h"
#include "HelperFns.h"
#include <iostream>

TokenStream::TokenStream() : full(0), buffer(0), equasion("") {}

void TokenStream::putback(Token t) {
	if (full) error_txt("Trying to put token back into a full buffer!");
	buffer = t;
	full = true;
}

//geter za Token
Token TokenStream::get() {
	if (full) {
		full = false;
		return buffer;
	}

	char ch;
	std::cin >> ch; //cita karakter


	std::string str_val = "";
	//u zavisnosti od toga sta je karakter poziva odgovarajuci konstruktor za Token
	switch (ch)
	{
	case 'q':
	case ';':
	case '(': case ')': case '+': case '-': case '*': case '/':
		str_val = ch;
		return Token(ch, 0, str_val);
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		std::cin.putback(ch); //vraca karakter u cin da bi procitao kao double
		double val;
		std::cin >> val; //sada ne cita samo jedan karakter nego ceo broj koji je bio(ako je 123 nece samo 1 nego 123)
		str_val = std::to_string(val);
		return Token('8', val, str_val); //procitanu double vrednost prosledjuje konstruktoru; 8 ce oznacavati broj
	default:
		std::cout << "Bad token" << std::endl;
		return Token('9', -1); //u slucaju greske
	}
}
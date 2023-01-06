#pragma once
#include "TokenStream.h"

class Calculator {
public:
	Calculator ();
	//~Calculator ();
	void calculate();
	double get_val();
	void reset_equasion();
	std::string get_equasion();
	std::string get_best_solution(vector<std::string> str_arr, int solution_to_get);
private:
	TokenStream ts;
	double val;
	std::string equasion;
};
#include "TokenStream.h"
#include "std_lib_facilities.h"
#pragma once

void error_txt(std::string s);

double primary(TokenStream& ts);

double term(TokenStream& ts);

double expression(TokenStream& ts);

//-------------------------------------------------------------------------------------------------------------------

string concat(string& a, string& b, char op);

hash_map<long long, string> all_values(int L, int R);

bool read_input(vector<std::string> str_arr, int solution_to_get);

std::string solve();

int main();
#include "HelperFns.h"
#include <stdexcept>

void error_txt(std::string s) {
	std::cout << s << std::endl; //ispis greske
}

//najveceg prioriteta, regulise brojeve i zagrade, u kojima poziva expression kako bi regulisao izraz unutar zagrada
double primary(TokenStream& ts) {
	Token t = ts.get();
	ts.equasion += t.char_value;

	switch (t.kind)
	{
	case '8':
		return t.value;
	case '(':
		{
			double d = expression(ts);
			t = ts.get();
			if (t.kind != ')') {
				error_txt("')' expected!");
				return -1;
			}
			return d;
		}
	default:
		break;
	}
}

double term(TokenStream& ts) { //druga po prioritetu, regulise operatore * /
	double left = primary(ts);
	if (left == -1) return -1;
	Token t = ts.get();
	ts.equasion += t.char_value;

	while (true) {
		switch (t.kind)
		{
		case '*':
			{
				double d = primary(ts);
				if (d == -1) return -1;
				left *= d;
				t = ts.get();
				break; 
			}
		case '/':
			{
				double d = primary(ts);
				if (d == -1) return -1;
				if (d == 0) {
					error_txt("divide by zero");
					return -1;
				}
				left /= d;
				t = ts.get();
				break;
			}
		default:
			ts.putback(t);
			return left;
		}
	}
}

//regulise operatore najmanje vrednosti + -
double expression(TokenStream& ts) { //prva od tri funkcije koja se poziva iz kalkulatora
	double left = term(ts);
	if (left == -1) return -1; //prati pogresne unose
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '+':
			{
				double d = term(ts);
				if (d == -1) return -1;
				left += d;
				t = ts.get();
				break;
			}
		case '-':
			{
				double d = term(ts);
				if (d == -1) return -1;
				left -= d;
				t = ts.get();
				break;
			}
		default:
			ts.putback(t);
			return left;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------
//deo koji generise sve moguce kombinacije izraza i trazi najbolju

int n, target;
vector<int> arr;

string concat(string& a, string& b, char operat) { //sluzi pri pravljenju izraza
	return "(" + a + " " + string(1, operat) + " " + b + ")";
}

std::hash_map<long long, string> all_values(int L, int R) { //povratna vrednost je hesmapa koja cuva string izraz pod generisanim kljucem
	std::hash_map<long long, string> hmp;
	if (L == R) {
		hmp[arr[L]] = std::to_string(arr[L]);
		return hmp;
	}

	for (int mid = L; mid < R; mid++) {
		auto mpA = all_values(L, mid);
		auto mpB = all_values(mid + 1, R);
		for (auto& x : mpA) {
			for (auto& y : mpB) {
				hmp[x.first + y.first] = concat(x.second, y.second, '+'); //puni hesmapu sa novonapravljenim izrazima
				hmp[x.first - y.first] = concat(x.second, y.second, '-');
				hmp[x.first * y.first] = concat(x.second, y.second, '*');
				if (y.first && x.first % y.first == 0)
					hmp[x.first / y.first] = concat(x.second, y.second, '/');
			}
		}
	}
	return hmp;
}

bool read_input(vector<std::string> str_arr, int solution_to_get) { //proseldjuje mu se vektor sa brojevima na raspolganju
	n = str_arr.size();

	arr.resize(n);
	for (int i = 0; i < n; i++) {
		arr[i] = stoi(str_arr[i]);
	}

	target = solution_to_get;
	return true;
}

std::string solve() {
	stringstream ss;

	sort(arr.begin(), arr.end());
	do {
		auto hmp = all_values(0, n - 1);
		if (hmp.count(target)) {
			std::cout << target << " = ";
			std::cout << hmp[target] << endl;
			std::cout << "----------------------------------------------------" << std::endl;
			ss << target;
			string str = ss.str();
			return str + " = " + hmp[target]; //izraz koji daje tacno resenje
		}
	} while (next_permutation(arr.begin(), arr.end()));
	cout << "No solution" << std::endl;

	int target_manji = target;
	int target_veci = target;
	sort(arr.begin(), arr.end());
	do { //ukoliko ne moze naci tacno resenje
		target_manji -= 1;
		target_veci += 1;
		auto hmp = all_values(0, n - 1);
		if (hmp.count(target_manji)) {
			std::cout << target_manji << " = ";
			std::cout << hmp[target_manji] << std::endl;
			std::cout << "----------------------------------------------------" << std::endl;
			ss << target_manji;
			string str = ss.str();
			return str + " = " + hmp[target_manji]; //printuje izraz manji od solution_to_find
		}
		if (hmp.count(target_veci)) {
			std::cout << target_veci << " = ";
			std::cout << hmp[target_veci] << std::endl;
			std::cout << "----------------------------------------------------" << std::endl;
			ss << target_veci;
			string str = ss.str();
			return str + " = " + hmp[target_veci]; //printuje izraz veci od solution_to_find
		}
	} while (next_permutation(arr.begin(), arr.end()));
}

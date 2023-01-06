#include "Calculator.h"
#include "HelperFns.h"

Calculator::Calculator() : ts(), val(0), equasion("") {}

void Calculator::calculate() {
    try
    {
        while (cin) {
            //dobavlja karakter iz cina
            Token t = ts.get();

            //u zavisnosti od vrste Tokena odlucuje dalju radnju: ispis rezultata, greska, racunanje
            if (t.kind == ';') { 
                cout << "=" << val << '\n'; //ispis rezultata
                break;
            }
            if (t.kind == '9') {
                val = -1; //greska
                break;
            }
            else {
                ts.putback(t);
                val = expression(ts); //racunanje
                if (val == -1) break;
            }
        }
        equasion = ts.equasion; //izraz koji je igrac pisao
    }
    catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
        keep_window_open();
    }
    catch (...) {
        cerr << "Oops: unknown exception!\n";
        keep_window_open();
    };
}

//geter za vrednost izraza
double Calculator::get_val() {
    return val;
}

//vraca string za pamcenje izraza na prazan string
void Calculator::reset_equasion() {
    ts.equasion = "";
}

//vraca izraz
std::string Calculator::get_equasion() {
    return equasion;
}

//poziva pomocne funkcije koje sluze za racunanje najboljeg resenja
std::string Calculator::get_best_solution(vector<std::string> str_arr, int solution_to_get) {
    bool check = read_input(str_arr, solution_to_get);
    if (check == false)
        error_txt("Can't read input!");

    return solve();
}
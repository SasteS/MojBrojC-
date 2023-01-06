#include "Calculator.h"

int main() {
	std::cout << "--------- MOJ BROJ ---------" << std::endl;

	//prima ime fajla
	std::cout << "Name of file: ";
	std::string file_name;
	std::cin >> file_name;

	//fstream file("rezultati.txt", ios::out); //prazni file pred pocetak igre
	//if (!file.is_open()) {
	//	std::cout << "unable to open the file!" << std::endl;
	//}
	//else {
	//	file << "";
	//}
	//file.close();

	std::string approx_res_equasion; //varijavla pomocu koje ce se ispisati resenje koje program nadje
	std::string player1_equasion; //izrazi prvog i drugog igraca
	std::string player2_equasion;
	double player1_deviation; //odstupanja od racnog resenja
	double player2_deviation;

	int num_of_round = 1;
	std::string winner;
	int player1_win_count = 0; //broj pobedjenih rundi
	int player2_win_count = 0;
	
	int solution_to_get; //resenje koje se trazi
	vector<std::string> line_split; //brojevi na raspolaganju

	//ucitavanje brojeva iz fajla runda po runda
	std::string line;
	ifstream file(file_name);
	if (!file.is_open()) {
		std::cout << "Unable to open the file!" << std::endl;
	}
	else {
		std::string line;

		while (getline(file, line)) {
			line_split.clear();

			std::stringstream ss(line);
			std::string temp_holder;
			int brojac = 0;
			while (ss >> temp_holder) //koristi brojac da bi mogao da razdvoji broj koji se trazi od brojeva na raspolaganju
			{
				if (brojac == 0)
					solution_to_get = stoi(temp_holder);
				else
					line_split.push_back(temp_holder);
				brojac++;
			}

			Calculator c; //koristi se za racunanje izraza igraca

			double player1_res = -1; //rezultati igraca
			double player2_res = -1;
			bool no_second_player = false; //vrednost koja u slucaju cistog pogotka igraca koji je prvi na redu onesposobljava drugog igraca

			std::cout << "Get: " << solution_to_get << std::endl;
			vector<string>::iterator it;
			std::cout << "Use numbers: ";
			for(it = line_split.begin(); it != line_split.end(); it++)
				std::cout << *it << ", ";
			std::cout << std::endl << std::endl;

			if (num_of_round % 2 != 0) //ako je parni broj runde drugi igrac igra prvi
			{
				std::cout << "Player1 enter your expression:" << std::endl;
				while (player1_res == -1) {
					std::cout << "rezultat = ";
					c.reset_equasion(); //po pocetku nove runde vraca izraz na ""
					c.calculate(); //unutar ove funkcije obavlja se kompleksno racunanje izraza
					player1_equasion = c.get_equasion(); //nakon izracunavanja vrednosti cuva izraz u ovoj promenljivoj
					player1_res = c.get_val(); //nakon izracunavanja vrednosti cuva vrednost izraza u ovoj promenljivoj
					player1_deviation = std::abs(player1_res - solution_to_get);
					if (player1_deviation == 0) //ako je pogodio drugi igrac ne igra
						no_second_player = true;
					std::cout << "Player1s result: " << player1_res << std::endl << std::endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (no_second_player == false) {
					std::cout << "Player2 enter your expression:" << std::endl;
					while (player2_res == -1) {
						std::cout << "rezultat = ";
						c.reset_equasion();
						c.calculate();
						player2_equasion = c.get_equasion();
						player2_res = c.get_val();
						player2_deviation = std::abs(player2_res - solution_to_get);
						std::cout << "Player2s result: " << player2_res << std::endl << std::endl;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
				else //u slucaju da drugi igrac nema pravo da igra desava se sledece
				{
					player2_res = -100000;
					player2_deviation = std::abs(player2_res - solution_to_get);
				}
			}
			else { //isto kao gore deo samo kad drugi igrac igra prvi
				std::cout << "Player2 enter your expression:" << std::endl;
				while (player2_res == -1) {
					std::cout << "rezultat = ";
					c.reset_equasion();
					c.calculate();
					player2_equasion = c.get_equasion();
					player2_res = c.get_val();
					player2_deviation = std::abs(player2_res - solution_to_get);
					if (player2_deviation == 0)
						no_second_player = true;
					std::cout << "Player2s result: " << player2_res << std::endl << std::endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (no_second_player == false) {
					std::cout << "Player1 enter your expression:" << std::endl;
					while (player1_res == -1) {
						std::cout << "rezultat = ";
						c.reset_equasion();
						c.calculate();
						player1_equasion = c.get_equasion();
						player1_res = c.get_val();
						player1_deviation = std::abs(player1_res - solution_to_get);
						std::cout << "Player1s result: " << player1_res << std::endl << std::endl;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
				else
				{
					player1_res = -100000;
					player1_deviation = std::abs(player1_res - solution_to_get);
				}
			}			

			//deo koda koji sracunava najbolje resenje
			approx_res_equasion = c.get_best_solution(line_split, solution_to_get);
			if (player1_deviation < player2_deviation) { //odredjivanje pobednika
				winner = "player1";
				player1_win_count++;
			}
			else {
				winner = "player2";
				player2_win_count++;
			}

			//ispis rezultata u izlazni fajl
			fstream file("Rezultati.txt", ios::out | ios::app);
			if (!file.is_open()) {
				std::cout << "Unable to open the file!" << std::endl;
			}
			else {
				file << "Round: " << num_of_round << std::endl << "\tnumbers given: ";
				for (it = line_split.begin(); it != line_split.end(); it++)
					file << *it << " ";
				file << std::endl << "\tsolution to get: " << solution_to_get << std::endl
					<< "\tplayer2:" << std::endl << "\t\tgot: " << player1_res << std::endl << "\t\tdeviation: " << player1_deviation << std::endl << "\t\tplayer1s solution: " << player1_equasion << std::endl
					<< "\tplayer2:" << std::endl << "\t\tgot: " << player2_res << std::endl << "\t\tdeviation: " << player2_deviation << std::endl << "\t\tplayer2s solution: " << player2_equasion << std::endl
					<< "\twon the round:" << winner << std::endl << "\tProgram solution: " << approx_res_equasion << std::endl << std::endl;
			}
			file.close();
			num_of_round++; //povecava broj runde
		}
		//na samom kraju igre zapisuje ko je pobednik i ukupne brojeve pobedjenih rundi oba igraca
		fstream file("Rezultati.txt", ios::out | ios::app);
		if (!file.is_open()) {
			std::cout << "Unable to open the file!" << std::endl;
		}
		else {
			file << "total plyer1 wins: " << player1_win_count << std::endl << "total plyer2 wins: " << player2_win_count << std::endl;
			if (player1_win_count > player2_win_count)
				file << "winner: player1";
			else
				file << "winner: player2";
		}
	}
	file.close();

	return 0;
}
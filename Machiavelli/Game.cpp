#include "Game.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "CardFactory.h"


Game::Game()
{
	loadResources();
}

Game::~Game()
{
}

void Game::loadResources() {	
	buildCards = readCSV("../Resources/Bouwkaarten.csv", CardType::bouw);
	classCards = readCSV("../Resources/Karakterkaarten.csv", CardType::karakter);
}

vector<BaseCard*> Game::readCSV(const std::string& path, CardType type) {
	CardFactory m_CF = CardFactory();

	ifstream infile(path);

	vector<BaseCard*> cards;

	while (infile)
	{
		string s;
		if (!getline(infile, s)) break;

		istringstream ss(s);

		while (ss)
		{
			string s;
			if (!getline(ss, s, ',')) break;


			vector <string> record;
			stringstream ss(s);
			string item;
			while (std::getline(ss, item, ';')) {
				record.push_back(item);
			}
			
			if (type == CardType::bouw) {
				cards.push_back(m_CF.CreateInstance(record.at(0), atoi(record.at(1).c_str()), record.at(2)));
			}
			else {
				cards.push_back(m_CF.CreateInstance(record.at(1)));
			}
		}
	}
	if (!infile.eof())
	{
		cerr << "Fooey!\n";
	}

	return cards;
}

#include "Game.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "CardFactory.h"


Game::Game() : gameStarted{ false }
{
	loadResources();
}

Game::~Game()
{
}

void Game::loadResources() {	
	buildCards = readCSV("../Resources/Bouwkaarten.csv", CardType::bouw);
	classCards = readCSV("../Resources/Karakterkaarten.csv", CardType::karakter);
	
	currentPlayers = std::vector<std::shared_ptr<Player>>();
	cerr << "Resources initialized." << '\n';
}

std::vector<std::shared_ptr<BaseCard>> Game::readCSV(const std::string& path, CardType type) {
	CardFactory m_CF = CardFactory();

	ifstream infile(path);

	std::vector<std::shared_ptr<BaseCard>> cards;

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

void Game::AddPlayer(std::shared_ptr<Player> p) {
	currentPlayers.push_back(p);

	cerr << "Player "<< p->get_name() <<" connected." << '\n';
}

void Game::RemovePlayer(std::shared_ptr<Player> p) {
	for (size_t i = 0; i< currentPlayers.size(); i++){
		if (p->get_name() == currentPlayers[i]->get_name()) {
			currentPlayers.erase(currentPlayers.begin() + i);
		}
	}
}

std::shared_ptr<Player> Game::getCurrentPlayer() {
	return m_currentPlayer;
}

void Game::handleCommand(shared_ptr<Player> player, string command) {
	string message;

	std::transform(command.begin(), command.end(), command.begin(), ::tolower);

	if (command == "join") {
		message = "Player " + player->get_name() + " has joined, welcome him.\r\n";		
	}
	else if (command == "quit") {
		message = "Player " + player->get_name() + " has quit.\r\n";
	}
	else if (command == "ready") {
		player->isReady(true);
		message = "Player " + player->get_name() + " is ready.\r\n";
		if (currentPlayers.size() > 1 && allPlayersReady()) {
			gameStarted = true;
			message += "All players are ready. Let the best one win!";
		}
	}
	else if (command == "not ready") {
		player->isReady(false);
		message = "Player " + player->get_name() + " is not ready.\r\n";
	}
	else {
		message = command + "\r\n";
	}

	for (const auto &p : currentPlayers) {
		if (p->get_name() != player->get_name()) {
			p->getClient()->write(message);
		}
	}
}

bool Game::allPlayersReady() {
	for (const auto &p : currentPlayers) {
		if (p->isReady() != true) {
			return false;
		}
	}

	return true;
}
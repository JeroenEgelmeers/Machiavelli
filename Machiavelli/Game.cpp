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

void Game::StartGame()
{
	gameStarted = true;
	currentPlayers.at(0)->SetKing(true); // First player will be the King!
	m_currentPlayer = currentPlayers.at(0);
	//message += currentPlayers.at(0)->get_name() + " is the king and may now pick a character card!";
}

void Game::NewRound()
{
	// TODO Reset deck (Characters).
	SetupRound();
}

void Game::SetupRound()
{
	// TODO SetupRound implementation.

	// Reset King status (will be re-earned by the CharacterCard: King)
	for (const auto &p : currentPlayers) {
		p->SetKing(false);
	}
	PlayRound();
}

void Game::PlayRound()
{
	// TODO playRound implementation.
	VictoryCheck();
}

void Game::VictoryCheck()
{
	bool victory = false;
	for (const auto &p : currentPlayers) {
		if (p->FirstEightPoints()) {
			victory = true;
			p->getClient()->write("Game finished!" + p->get_name() + " played 8 or more buildling cards!");
		}
	}

	if (victory) {
		string	winnerName		=	"";
		int		winnerPoints	=	0;

		// Check best player
		for (const auto &p : currentPlayers) {
			p->CalculatePoints();
			if (winnerPoints < p->GetWinningPoints()) {
				winnerPoints = p->GetWinningPoints();
				winnerName = p->get_name();
				p->getClient()->write("You've got:" + std::to_string(p->GetWinningPoints()) + " points!");
			}
		}

		// Send message to all players who won the game.
		for (const auto &p : currentPlayers) {
			p->getClient()->write(winnerName + " won the game with " + std::to_string(winnerPoints) + " points!");
		}
	}
	else {
		NewRound();
	}
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

	if (gameStarted == false) {
		if (command == "join") {
			message = "Player " + player->get_name() + " has joined, welcome him.\r\n" + "machiavelli> ";

			for (const auto &p : currentPlayers) {
				if (p->getId() != player->getId()) {
					p->getClient()->write(message);
				}
				else {
					p->getClient()->write("machiavelli> ");
				}
			}
		}
		else if (command == "quit") {
			message = "Player " + player->get_name() + " has quit.\r\n" + "machiavelli> ";

			for (const auto &p : currentPlayers) {
				if (p->getId() != player->getId()) {
					p->getClient()->write(message);
				}
				else {
					p->getClient()->write("machiavelli> ");
				}
			}
		}
		else if (command == "ready") {
			player->isReady(true);
			message = "Player " + player->get_name() + " is ready.\r\n" + "machiavelli> ";
			for (const auto &p : currentPlayers) {
				if (p->getId() != player->getId()) {
					p->getClient()->write(message);
				}
				else {
					p->getClient()->write("machiavelli> ");
				}
			}
			if (currentPlayers.size() > 1 && allPlayersReady()) {
				message = "All players are ready. Let the best one win!\r\nmachiavelli> ";
				gameStarted = true;

				for (const auto &p : currentPlayers) {
					p->getClient()->write(message);
				}
			}
		}
		else if (command == "not ready") {
			player->isReady(false);
			message = "Player " + player->get_name() + " is not ready.\r\n" + "machiavelli> ";
			for (const auto &p : currentPlayers) {
				if (p->getId() != player->getId()) {
					p->getClient()->write(message);
				}
				else {
					p->getClient()->write("machiavelli> ");
				}
			}
		}
		else {
			message = "machiavelli> Did not understand command " + command + " please repeat. \r\n"+"machiavelli> ";
			player->getClient()->write(message);
		}
	}
	else if (gameStarted == true) {
		if (command == "quit") {
			message = "Player " + player->get_name() + " has left the game.\r\n" + "machiavelli> ";

			for (const auto &p : currentPlayers) {
				if (p->getId() != player->getId()) {
					p->getClient()->write(message);
				}
				else {
					p->getClient()->write("machiavelli> ");
				}
			}

			if (currentPlayers.size() <= 1) {
				gameStarted = false; 
				for (const auto &p : currentPlayers) {		
					message = "Insufficient players remaining, game stopped. \r\nmachiavelli> ";
					p->getClient()->write(message);
					p->isReady(false);
				}
				
			}
		}
		else {
			message = "machiavelli> Did not understand command " + command + " please repeat. \r\n" + "machiavelli> ";
			player->getClient()->write(message);
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
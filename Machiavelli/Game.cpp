#include "Game.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <thread>

#include "CardFactory.h"


Game::Game() : gameStarted{ false }
{
	loadResources();
}

Game::~Game()
{
}

void Game::loadResources() {	
	buildCards		= readCSV("../Resources/Bouwkaarten.csv", CardType::bouw);
	characterCards	= readCSV("../Resources/Karakterkaarten.csv", CardType::karakter);
	
	currentPlayers = std::vector<std::shared_ptr<Player>>();
	cerr << "Resources initialized." << '\n';
}

void Game::StartGame()
{
	gameStarted = true;
	while (gameStarted) {};
	currentPlayers.at(0)->SetKing(true); // First player will be the King!
	m_currentPlayer = currentPlayers.at(0);
	//message += currentPlayers.at(0)->get_name() + " is the king and may now pick a character card!";
}

void Game::NewRound()
{
	// Clear current deckCharacters
	if (deckCharacters.GetDeckSize() > 0) {
		deckCharacters.ClearDeck();
	}

	// Set up new deck
	for (const auto &c : characterCards) {
		deckCharacters.AddCard(c);
	}

	// Shuffle deck so the first will be always random.
	deckCharacters.ShuffleDeck();
	
	SetupRound();
}

void Game::SetupRound()
{
	// TODO SetupRound implementation.
	if (m_currentPlayer->IsKing()) {
		int cardIndex = 0;
		if (deckCharacters.GetDeck().at(0)->GetCharacterType() == CharacterType::Koning) {
			cardIndex++;
		}
		m_currentPlayer->getClient()->write("The first card: " + deckCharacters.GetDeck().at(0)->GetName() + " is removed from the deck.");
		deckCharacters.RemoveCardIndex(cardIndex);
		// Pick a card!
		PickCharacterCard();
		// Reset King status (will be re-earned by the CharacterCard: King)
		m_currentPlayer->SetKing(false);
		// TODO Change current player to second.
		SetupRound();
	}else {
		if (deckCharacters.GetDeckSize() > 0) {
			PickCharacterCard();
			// TODO change current player to second.
			if (deckCharacters.GetDeckSize() > 0) {
				m_currentPlayer->getClient()->write("It's now your turn. Pick a new Character card.");
				SetupRound();
			}
			else {
				PlayRound();
			}
		}
	}
}

void Game::PickCharacterCard()
{
	m_currentPlayer->getClient()->write("There are "+ std::to_string(deckCharacters.GetDeckSize()) + " characters left. Which do you want?");
	int pICardIndex = 0; // TODO Player gives index through console.
	deckCharacters.RemoveCardIndex(pICardIndex);
	m_currentPlayer->getClient()->write("There are " + std::to_string(deckCharacters.GetDeckSize()) + " characters left. Which do you want to remove?");
	pICardIndex = 0; // TODO Player gives index through console.
	bool inputTrue = false;
	while(!inputTrue) {
		pICardIndex = 0; // TODO Player gives index through console.
		if (deckCharacters.GetDeck().at(0)->GetCharacterType() == CharacterType::Koning) {
			m_currentPlayer->getClient()->write("You can't remove the king!");
		}
		else { inputTrue = true; }
	}
	deckCharacters.RemoveCardIndex(pICardIndex);
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

				for (const auto &p : currentPlayers) {
					p->getClient()->write(message);
				}

				thread g{ &Game::StartGame, this };
				g.detach();
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
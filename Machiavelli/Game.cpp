#include "Game.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <thread>
#include "CardFactory.h"
#include "CharacterCard.h"


Game::Game() : gameStarted{ false }
{
	loadResources();
}

Game::~Game()
{
}

void Game::loadResources() {	
	readCSV("../Resources/Bouwkaarten.csv", CardType::bouw);
	readCSV("../Resources/Karakterkaarten.csv", CardType::karakter);
	
	currentPlayers = std::vector<std::shared_ptr<Player>>();
	cerr << "Resources initialized." << '\n';
}

void Game::StartGame()
{
	gameStarted = true;
	m_currentPlayer = currentPlayers.at(0);
	m_currentPlayer->SetKing(true); // First player will be the King!

	// Get the building cards and store them in the buildlingcard deck
	for (const auto &c : buildCards) {
		deckBuildingCards.AddCard(c);
	}

	deckBuildingCards.ShuffleDeck(); // Shuffle the deck
	
	// Start the first round!
	NewRound();
}

void Game::NewRound()
{
	string kingsName = "";
	for (const auto &p : currentPlayers) {
		if (p->IsKing()) {
			kingsName = p->get_name();
			m_currentPlayer = p;
		}
		// Set this as we need this later.
		if (p->WasKing()) {
			p->SetWasKing(false);
		}
	}

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

	// Give players start gear
	for (const auto &p : currentPlayers) {
		p->AddGold(2);
		int i = 0;
		while (i <= 3) {
			p->AddHandCard(dynamic_pointer_cast<BuildingCard>(deckBuildingCards.GetDeck().at(0)));
			deckBuildingCards.RemoveCard(deckBuildingCards.GetDeck().at(0));

			i++;
		}
		p->getClient()->write("You gained 2 gold and 4 building cards.\r\nmachiavelli> ");
	}

	for (const auto &p : currentPlayers) {
		p->getClient()->write("A new round has started! \r\nmachiavelli> All characters are going back in the deck and they're getting shuffled! \r\nmachiavelli> ");
		p->getClient()->write("It's up to you king " + kingsName + "!\r\nmachiavelli> ");
	}
	
	SetupRound();
}

void Game::SetupRound()
{
	int cardIndex = 0;
	if (deckCharacters.GetDeck().at(0)->GetCharacterType() == CharacterType::Koning) {
		cardIndex++;
	}
	m_currentPlayer->getClient()->write("The first card: " + deckCharacters.GetDeck().at(cardIndex)->GetName() + " is removed from the deck.\r\nmachiavelli> ");
	deckCharacters.RemoveCardIndex(cardIndex);
	// Pick a card!
	PickCharacterCard(true);
	// Reset King status (will be re-earned by the CharacterCard: King)
	m_currentPlayer->SetKing(false);
	ChangeCurrentPlayer();

	// Then all other players (looping)
	while (deckCharacters.GetDeckSize() > 0) {
		m_currentPlayer->getClient()->write("It's now your turn. Pick a new Character card.\r\nmachiavelli> ");
		PickCharacterCard(false);
		ChangeCurrentPlayer();
	}

	for (const auto &p : currentPlayers) {
		p->getClient()->write("The character deck is cleared! Let's start!\r\nmachiavelli> ");
	}
	
	PlayRound(); // TODO
}

void Game::ShowCharacterCardsLeft() {
	string message = "";
	int i = 1;
	for (const auto &c : deckCharacters.GetDeck()) {
		message += "[" + std::to_string(i) + "]" + c->GetName() + "\r\nmachiavelli> ";
		i++;
	}

	m_currentPlayer->getClient()->write(message);
}

void Game::PickCharacterCard(bool skipRemove)
{
	// Pick a card
	m_currentPlayer->getClient()->write("There are " + std::to_string(deckCharacters.GetDeckSize()) + " characters left.\r\nmachiavelli> Which do you want?\r\nmachiavelli> ");
	ShowCharacterCardsLeft();
	bool inputTrue = false;
	while (!inputTrue) {
		string response = m_currentPlayer->getResponse();
		int cardnr = atoi(response.c_str());
		if (cardnr >= 1 && cardnr <= deckCharacters.GetDeck().size()) {
			m_currentPlayer->AddCharacterCard(deckCharacters.GetDeck().at(cardnr - 1));

			m_currentPlayer->getClient()->write("machiavelli> You picked "+ deckCharacters.GetDeck().at(cardnr - 1)->GetName() +".\r\nmachiavelli> ");
			deckCharacters.RemoveCardIndex(cardnr-1);
			inputTrue = true;
		}
		else {
			m_currentPlayer->getClient()->write("machiavelli> Invalid input. Please try again.\r\nmachiavelli> ");
		}
	}

	if (!skipRemove) {
		// Remove a card
		m_currentPlayer->getClient()->write("There are " + std::to_string(deckCharacters.GetDeckSize()) + " characters left.\r\nmachiavelli> Which do you want to remove?\r\nmachiavelli> ");
		ShowCharacterCardsLeft();
		inputTrue = false;
		while (!inputTrue) {
			string response = m_currentPlayer->getResponse();
			int cardnr = atoi(response.c_str());
			if (cardnr >= 1 && cardnr <= deckCharacters.GetDeck().size()) {
				if (deckCharacters.GetDeck().at(cardnr - 1)->GetCharacterType() == CharacterType::Koning) {
					m_currentPlayer->getClient()->write("You can't remove the king!\r\nmachiavelli> ");
				}
				else {
					deckCharacters.RemoveCardIndex(cardnr - 1);
					m_currentPlayer->getClient()->write("machiavelli> Card removed.\r\nmachiavelli> ");
					inputTrue = true;
				}
			}
			else {
				m_currentPlayer->getClient()->write("machiavelli> Invalid input. Please try again.\r\nmachiavelli> ");
			}
		}
	}
}

void Game::ChangeCurrentPlayer()
{
	bool playerFound = false;
	bool playerChanged = false;
	int i = 0;
	for (const auto &p : currentPlayers) {
		if (p->getId() == m_currentPlayer->getId()) {
			playerFound = true;
		}
		else if (playerFound) {
			m_currentPlayer->getClient()->write("End of your turn, please wait...\r\nmachiavelli> ");
			m_currentPlayer = p;
			playerChanged = true;
		}
	}
	if (!playerChanged) {
		m_currentPlayer->getClient()->write("End of your turn, please wait...\r\nmachiavelli> ");
		m_currentPlayer = currentPlayers.at(0); 
	}
}

void Game::PlayRound()
{
	int currentCharacter = 1;

	// Get the kingsname for some nice information on screen.
	string kingName = "";
	for (const auto &p : currentPlayers) {
		if (p->WasKing()) {
			kingName = p->get_name();
		}
	}

	// Step 1: Loop through characters
	while (currentCharacter < 9) {
		int  playerBuild = 0;
		for (const auto &p : currentPlayers) {
			p->getClient()->write("King " + kingName + " asks for the " + CharacterTypeToString(CharacterType(currentCharacter)) + "\r\n");
		}
		bool charFound = false;
		for (const auto &p : currentPlayers) {
			if (p->HasAndCanPlayCharacter(CharacterType(currentCharacter))) {
				p->getClient()->write("You've got this card! It's now your turn!");
				m_currentPlayer = p;
				charFound = true;
			}
		}
		if (charFound) {
			// Inform other players
			for (const auto &p : currentPlayers) {
				if (p->getId() != m_currentPlayer->getId()) {
					p->getClient()->write(m_currentPlayer->get_name() + " has the " + CharacterTypeToString(CharacterType(currentCharacter)));
				}
			}
			// Give player possiblity
			bool validInput = false;
			string message = "";
			while (!validInput) {
				message += "What would you like to do? \r\nmachiavelli> ";
				message += "[1] Get 2 gold coins. \r\nmachiavelli> ";
				message += "[2] Get 2 building cards. \r\nmachiavelli> ";
				m_currentPlayer->getClient()->write(message);

				string response = m_currentPlayer->getResponse();
				int playerInput = atoi(response.c_str());
				switch (playerInput) {
					case 1:
						m_currentPlayer->AddGold(2);
						m_currentPlayer->getClient()->write("You took 2 gold coins.");
						validInput = true;
						for (const auto &p : currentPlayers) {
							if (p->getId() != m_currentPlayer->getId()) {
								p->getClient()->write(m_currentPlayer->get_name() + " took 2 gold coins!");
							}
						}
						break;
					case 2:
						deckBuildingCards.RemoveCardIndex(0);
						m_currentPlayer->getClient()->write("You took a: " + deckBuildingCards.GetDeck().at(0)->GetName() + "from the building card deck.");
						m_currentPlayer->AddHandCard(dynamic_pointer_cast<BuildingCard>(deckBuildingCards.GetDeck().at(0)));
						deckBuildingCards.RemoveCardIndex(0);
						validInput = true;
						for (const auto &p : currentPlayers) {
							if (p->getId() != m_currentPlayer->getId()) {
								p->getClient()->write(m_currentPlayer->get_name() + " took 1 building card!");
							}
						}
						break;
					default:
						break;
				}
			}

			// This is because bouwmeester can build 3 buildings!
			int canBuild = 1;
			if (currentCharacter == 7) {
				canBuild = 3;
			}
			validInput = false;
			while (!validInput) {
				int playerInput;
				if (canBuild > 0) {
					message += "You can build " + std::to_string(canBuild) + " buildings. Would you like to build one? \r\nmachiavelli> ";
					message += "[1] Yes. \r\nmachiavelli> ";
					message += "[2] No. \r\nmachiavelli> ";
					m_currentPlayer->getClient()->write(message);

					string response = m_currentPlayer->getResponse();
					playerInput = atoi(response.c_str());
				}
				else {
					validInput = true;
					break;
				}

				bool validInputInner = false;
				switch (playerInput) {

					case 1:
						while (!validInputInner && playerBuild <= canBuild) {
							message = "";
							message += "Which card would you like to build?\r\nmachiavelli>";
							message += "[0] I don't want to play a card.\r\nmachiavelli>";
							int i = 1;
							for (const auto &c : m_currentPlayer->GetHandCards()) {
								message += "["+std::to_string(i)+"] " + c->GetName() + " cost: " + std::to_string(c->GetGoldCoins()) + "\r\nmachiavelli>";
								i++;
							}
							m_currentPlayer->getClient()->write(message);

							int playerInputInner = -1; // TODO set player input
							if (playerInputInner == 0) {
								validInputInner = true;
								validInput		= true;
							}
							if (playerInputInner <= i) {
								if (m_currentPlayer->PlayCard(i)) {
									canBuild--;
									for (const auto &p : currentPlayers) {
										p->getClient()->write(m_currentPlayer->get_name() + " build one building! \r\nmachiavelli>");
									}
									if (!playerReachedEightPoints && m_currentPlayer->GetBuildingPoints() >= 8) {
										playerReachedEightPoints = true;
										m_currentPlayer->SetFirstEightPoints(true);
										for (const auto &p : currentPlayers) {
											p->getClient()->write(m_currentPlayer->get_name() + " reached 8 points! \r\nmachiavelli>");
										}
									}
								}
								validInputInner = true;
							}										
						}
						validInput = true;
						break;
					case 2:
						validInput = true;
						break;
					default:
						break;
				}
			}

			// Execute card
			m_currentPlayer->GetCharacterCard(CharacterTypeToString(CharacterType(currentCharacter)))->Execute(*this); // Pointer before the this else it'll give an error!
		}
		// Go to next character
		currentCharacter++;
	}

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

void Game::readCSV(const std::string& path, CardType type) {
	CardFactory m_CF = CardFactory();

	ifstream infile(path);

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
				buildCards.push_back(m_CF.CreateInstance(record.at(0), atoi(record.at(1).c_str()), record.at(2)));
			}
			else {
				characterCards.push_back(m_CF.CreateInstance(record.at(1)));
			}
		}
	}
	if (!infile.eof())
	{
		cerr << "Fooey!\n";
	}
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
			if (player == m_currentPlayer) {
				player->setResponse(command);
			}
			else {
				message = "machiavelli> It is not your turn, please wait. \r\nmachiavelli> ";
				player->getClient()->write(message);
			}
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
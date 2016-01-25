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
	try {
		gameStarted = true;
		m_currentPlayer = currentPlayers.at(0);
		m_currentPlayer->SetKing(true); // First player will be the King!

		// Get the building cards and store them in the buildlingcard deck
		for (const auto &c : buildCards) {
			deckBuildingCards.AddCard(c);
		}

		deckBuildingCards.ShuffleDeck(); // Shuffle the deck

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
		// Start the first round!
		NewRound();
	}
	catch (int e) {
		gameStarted = false;
		if (currentPlayers.size() < 2) {
			for (const auto &p : currentPlayers) {
				p->SetKing(false);
				p->isReady(false);
				p->getClient()->write("Unable to continue! \r\nmachiavelli> ");
			}
		}
	}
}

void Game::NewRound()
{
	string kingsName = "";
	for (const auto &p : currentPlayers) {
		// Remove characters.
		p->ClearCharacterCards();

		// Set current king
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
				if (deckCharacters.GetDeck().at(cardnr - 1)->GetCharacterType() == CharacterType::Koning && deckCharacters.GetDeckSize() > 1) {
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
			p->getClient()->write("King " + kingName + " asks for the " + CharacterTypeToString(CharacterType(currentCharacter)) + "\r\nmachiavelli> ");
		}
		bool charFound = false;
		for (const auto &p : currentPlayers) {
			if (p->HasAndCanPlayCharacter(CharacterType(currentCharacter))) {
				p->getClient()->write("You've got this card! It's now your turn! \r\nmachiavelli> ");
				m_currentPlayer = p;
				charFound = true;
			}
		}
		if (charFound) {
			// Inform other players
			for (const auto &p : currentPlayers) {
				if (p->getId() != m_currentPlayer->getId()) {
					p->getClient()->write(m_currentPlayer->get_name() + " has the " + CharacterTypeToString(CharacterType(currentCharacter)) + "\r\nmachiavelli> ");
				}
			}
			// Give player possiblity
			bool validInput = false; 
			string message;
			while (!validInput) {
				message = "";
				message += "What would you like to do? \r\nmachiavelli> ";
				message += "[1] Get 2 gold coins. \r\nmachiavelli> ";
				message += "[2] Get 1 building card. \r\nmachiavelli> ";
				message += "[3] Check character cards. \r\nmachiavelli> ";
				message += "[4] Check building cards. \r\nmachiavelli> ";
				message += "[5] Check build buildings. \r\nmachiavelli> ";
				m_currentPlayer->getClient()->write(message);

				string response = m_currentPlayer->getResponse();
				int playerInput = atoi(response.c_str());
				switch (playerInput) {
					case 1:
						m_currentPlayer->AddGold(2);
						m_currentPlayer->getClient()->write("machiavelli> You took 2 gold coins. \r\nmachiavelli> ");
						validInput = true;
						for (const auto &p : currentPlayers) {
							if (p->getId() != m_currentPlayer->getId()) {
								p->getClient()->write(m_currentPlayer->get_name() + " took 2 gold coins! \r\nmachiavelli>");
							}
						}
						break;
					case 2:
						m_currentPlayer->getClient()->write("You took a: " + deckBuildingCards.GetDeck().at(0)->GetName() + " from the building card deck. \r\nmachiavelli>");
						m_currentPlayer->AddHandCard(dynamic_pointer_cast<BuildingCard>(deckBuildingCards.GetDeck().at(0)));
						deckBuildingCards.RemoveCardIndex(0);
						deckBuildingCards.RemoveCardIndex(0); // TODO instead of removing one more, the player should be able to choose which he/she wants to get.
						validInput = true;
						for (const auto &p : currentPlayers) {
							if (p->getId() != m_currentPlayer->getId()) {
								p->getClient()->write(m_currentPlayer->get_name() + " took 1 building card! \r\nmachiavelli>");
							}
						}
						break;
					case 3:
						m_currentPlayer->PrintCharacterCards();
						break;
					case 4:
						m_currentPlayer->PrintHandCards();
						break;
					case 5:
						m_currentPlayer->PrintTableCards();
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
			bool validInput1 = false;
			while (!validInput1) {
				int playerInput;
				if (canBuild > 0) {
					message = "";
					message += "You can build " + std::to_string(canBuild) + " buildings. Would you like to build one? \r\nmachiavelli> ";
					message += "[1] Yes. \r\nmachiavelli> ";
					message += "[2] No. \r\nmachiavelli> ";
					m_currentPlayer->getClient()->write(message);

					string response = m_currentPlayer->getResponse();
					playerInput = atoi(response.c_str());
				}
				else {
					validInput1 = true;
					break;
				}

				bool validInputInner = false;
				switch (playerInput) {

					case 1:
						while (!validInputInner && playerBuild <= canBuild) {
							message = "\r\nmachiavelli> ";
							message += "Which card would you like to build?\r\nmachiavelli> ";
							message += "[0] I don't want to play a card.\r\nmachiavelli> ";
							int i = 1;
							for (const auto &c : m_currentPlayer->GetHandCards()) {
								message += "["+std::to_string(i)+"] " + c->GetName() + " cost: " + std::to_string(c->GetGoldCoins()) + "\r\nmachiavelli> ";
								i++;
							}
							m_currentPlayer->getClient()->write(message);

							string response = m_currentPlayer->getResponse();
							int playerInputInner = atoi(response.c_str());

							if (playerInputInner == 0) {
								validInputInner = true;
								validInput1 = true;
							}
							else if (playerInputInner <= i) {
								if (m_currentPlayer->PlayCard(playerInputInner-1)) {
									canBuild--;
									for (const auto &p : currentPlayers) {
										if (p->getId() != m_currentPlayer->getId()) {
											p->getClient()->write(m_currentPlayer->get_name() + " build one building! \r\nmachiavelli>");
										}
									}
									if (!playerReachedEightPoints && m_currentPlayer->BuildingCardsOnTable() >= 8) {
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
						validInput1 = true;
						break;
					case 2:
						validInput1 = true;
						break;
					default:
						break;
				}
			}

			// Execute card
			m_currentPlayer->ExecuteCharacterCard(currentCharacter, *this); // Pointer before the this else it'll give an error!
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
			p->getClient()->write("Game finished!" + p->get_name() + " played 8 or more buildling cards!  \r\nmachiavelli>");
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
				p->getClient()->write("You've got:" + std::to_string(p->GetWinningPoints()) + " points!  \r\nmachiavelli>");
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
			message = "Player " + player->get_name() + " has joined. \r\n" + "machiavelli> ";

			for (const auto &p : currentPlayers) {
				if (p->getId() != player->getId()) {
					p->getClient()->write(message);
				}
				else {
					p->getClient()->write("machiavelli> ");
				}
			}

			if (currentPlayers.size() >= 2) {
				for (const auto &p : currentPlayers) {					
					p->getClient()->write("Enough players have joined.\r\nmachiavelli> Type ready to begin. \r\nmachiavelli> ");
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
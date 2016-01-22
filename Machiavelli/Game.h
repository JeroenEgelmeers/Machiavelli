#pragma once

#include <string>
#include <vector>
#include <memory>

#include "BaseCard.h"
#include "Player.h"
#include "CardDeck.h"

class Game
{
public:
	Game();
	~Game();

	void AddPlayer(std::shared_ptr<Player> p);
	void RemovePlayer(std::shared_ptr<Player> p);

	std::shared_ptr<Player> getCurrentPlayer();

	void handleCommand(shared_ptr<Player> player, std::string command);

	bool isGameStarted() { return gameStarted; };
private:
	bool gameStarted;

	std::vector<std::shared_ptr<Player>> currentPlayers;
	std::shared_ptr<Player> m_currentPlayer;

	std::vector<std::shared_ptr<BaseCard>> buildCards;
	std::vector<std::shared_ptr<BaseCard>> characterCards;

	void loadResources();

	void StartGame();
	void NewRound();
	void SetupRound();
		void PickCharacterCard();
	void PlayRound();
	void VictoryCheck();

	CardDeck deckCharacters;
	CardDeck deckBuildlingCharacters;

	std::vector<std::shared_ptr<BaseCard>> readCSV(const std::string& path, CardType type);

	bool allPlayersReady();
};

// No clue what the game class should have. First designing before implementation?

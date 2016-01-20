#pragma once

#include <string>
#include <vector>
#include <memory>

#include "BaseCard.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	void AddPlayer(std::shared_ptr<Player> p);
	void RemovePlayer(std::shared_ptr<Player> p);

	std::shared_ptr<Player> getCurrentPlayer();
private:
	std::vector<std::shared_ptr<Player>> currentPlayers;
	std::shared_ptr<Player> m_currentPlayer;

	std::vector<std::shared_ptr<BaseCard>> buildCards;
	std::vector<std::shared_ptr<BaseCard>> classCards;

	void loadResources();

	std::vector<std::shared_ptr<BaseCard>> readCSV(const std::string& path, CardType type);
};

// No clue what the game class should have. First designing before implementation?

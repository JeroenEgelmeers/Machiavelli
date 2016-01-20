#pragma once

#include <string>
#include <vector>
#include <memory>

#include "BaseCard.h"

class Game
{
public:
	Game();
	~Game();
private:
	std::vector<std::shared_ptr<BaseCard>> buildCards;
	std::vector<std::shared_ptr<BaseCard>> classCards;

	void loadResources();

	std::vector<std::shared_ptr<BaseCard>> readCSV(const std::string& path, CardType type);
};

// No clue what the game class should have. First designing before implementation?

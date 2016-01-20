#pragma once

#include <string>
#include <vector>

#include "BaseCard.h"

class Game
{
public:
	Game();
	~Game();
private:
	std::vector<BaseCard*> buildCards;
	std::vector<BaseCard*> classCards;

	void loadResources();

	std::vector<BaseCard*> readCSV(const std::string& path, CardType type);
};

// No clue what the game class should have. First designing before implementation?

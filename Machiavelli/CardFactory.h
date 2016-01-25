#pragma once

#include <string>
#include <map>
#include <memory>

#include "BuildingCard.h"
#include "CharacterCard.h"
#include "EnumCard.h"

class CardFactory
{
public:
	CardFactory();
	~CardFactory();

	std::shared_ptr<BuildingCard>  CreateInstance(std::string name, int goldCoins, std::string color);
	std::shared_ptr<CharacterCard>  CreateInstance(std::string type);
private:
	std::map<std::string, CardColor> colorResolver;
	std::map<std::string, CharacterType> cardTypeResolver;
};


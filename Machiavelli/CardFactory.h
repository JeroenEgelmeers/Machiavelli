#pragma once

#include <string>
#include <map>
#include "BaseCard.h"
#include "EnumCard.h"

class CardFactory
{
public:
	CardFactory();
	~CardFactory();

	BaseCard* CreateInstance(string name, int goldCoins, string color);
	BaseCard* CreateInstance(string type);
private:
	std::map<string, CardColor> colorResolver;
	std::map<string, CharacterType> cardTypeResolver;
};


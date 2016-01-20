#pragma once

#include <string>
#include <map>
#include <memory>

#include "BaseCard.h"
#include "EnumCard.h"

class CardFactory
{
public:
	CardFactory();
	~CardFactory();

	std::shared_ptr<BaseCard>  CreateInstance(string name, int goldCoins, string color);
	std::shared_ptr<BaseCard>  CreateInstance(string type);
private:
	std::map<string, CardColor> colorResolver;
	std::map<string, CharacterType> cardTypeResolver;
};


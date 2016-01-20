#include "BuildingCard.h"
#include "Game.h"

BuildingCard::BuildingCard(string name, CardColor color, int goldCoins, int silverCoins, CharacterType type) : BaseCard(name, color, type)
{
	mGoldCoins		= goldCoins;
	mSilverCoins	= silverCoins;
}

BuildingCard::~BuildingCard() {} // TODO

void BuildingCard::Execute(Game game) {} // TODO
void BuildingCard::Print() {} // TODO

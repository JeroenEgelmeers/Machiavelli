#include "BuildingCard.h"
#include "Game.h"

BuildingCard::BuildingCard(string name, CardColor color, int goldCoins, int silverCoins)
	: mGoldCoins(goldCoins), mSilverCoins(silverCoins), mColor(color), mName(name)
{}

BuildingCard::~BuildingCard() {} // TODO

void BuildingCard::Execute(Game game) {} // TODO
void BuildingCard::Print() {} // TODO
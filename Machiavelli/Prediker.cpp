#include "Prediker.h"
#include "Game.h"


Prediker::Prediker() : CharacterCard("Prediker", CardColor::blue, CharacterType::Prediker){}
Prediker::~Prediker(){}

void Prediker::Execute(Game game)
{
	// Protected to condotierre.
	// One gold coin for each blue buildling on table.
	int earnsGoldCoins = game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::blue);
	if (earnsGoldCoins > 0) {
		game.getCurrentPlayer()->AddGold(earnsGoldCoins);
		game.getCurrentPlayer()->getClient()->write("You earned " + std::to_string(earnsGoldCoins) + " gold for your red buildings. \r\nmachiavelli> ");
	}
}

void Prediker::Print()
{
}

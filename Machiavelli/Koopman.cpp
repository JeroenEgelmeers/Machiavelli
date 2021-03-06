#include "Koopman.h"
#include "Game.h"


Koopman::Koopman() : CharacterCard("Merchant", CardColor::green, CharacterType::Koopman){}
Koopman::~Koopman(){}

void Koopman::Execute(Game game)
{
	// Gets one gold coin
	game.getCurrentPlayer()->AddGold(1);
	game.getCurrentPlayer()->getClient()->write("You earned one gold because you played the Merchant  \r\nmachiavelli> ");

	int earnsGoldCoins = game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::green);
	if (earnsGoldCoins > 0) {
		game.getCurrentPlayer()->AddGold(earnsGoldCoins);
		game.getCurrentPlayer()->getClient()->write("You earned " + std::to_string(earnsGoldCoins) + " gold for your green buildlings. \r\nmachiavelli> ");
	}

	game.getCurrentPlayer()->getClient()->write("You're playing the Merchant. \r\nmachiavelli> ");
}

void Koopman::Print()
{
}


#include "Koning.h"
#include "Game.h"


Koning::Koning() : CharacterCard("Koning", CardColor::yellow, CharacterType::Koning) { }
Koning::~Koning() { }

void Koning::Execute(Game game)
{
	game.getCurrentPlayer()->getClient()->write("You're playing the King.  \r\nmachiavelli> ");
	// Is now KING for next round.
	game.getCurrentPlayer()->SetKing(true);
	game.getCurrentPlayer()->getClient()->write("You'll be the king next round.  \r\nmachiavelli> ");
	// Gets one gold coin for each gold building on table.
	int earnsGoldCoins = game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::yellow);
	if (earnsGoldCoins > 0) {
		game.getCurrentPlayer()->AddGold(earnsGoldCoins);
		game.getCurrentPlayer()->getClient()->write("You earned " + std::to_string(earnsGoldCoins) + " gold for your red buildlings. \r\nmachiavelli> ");
	}
}

void Koning::Print()
{
}

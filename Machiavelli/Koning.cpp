#include "Koning.h"
#include "Game.h"


Koning::Koning() : CharacterCard("Koning", CardColor::yellow, CharacterType::Koning) { }
Koning::~Koning() { }

void Koning::Execute(Game game)
{
	// Is now KING for next round.
	game.getCurrentPlayer()->SetKing(true);	
	// Gets one gold coin for each gold building on table.
	game.getCurrentPlayer()->AddGold(game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::yellow));
}

void Koning::Print()
{
}

#include "Prediker.h"
#include "Game.h"


Prediker::Prediker() : CharacterCard("Prediker", CardColor::blue, CharacterType::Prediker){}
Prediker::~Prediker(){}

void Prediker::Execute(Game game)
{
	// Protected to condotierre.
	// One gold coin for each blue buildling on table.
	game.getCurrentPlayer()->AddGold(game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::blue));
}

void Prediker::Print()
{
}

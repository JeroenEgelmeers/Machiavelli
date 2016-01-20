#include "Koopman.h"
#include "Game.h"


Koopman::Koopman() : CharacterCard("Koopman", CardColor::green, CharacterType::Koopman){}
Koopman::~Koopman(){}

void Koopman::Execute(Game game)
{
	// Gets one gold coin
	game.getCurrentPlayer()->AddGold(1);

	// Gets one gold coin for each green buildling on table.
	game.getCurrentPlayer()->AddGold(game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::green));
}

void Koopman::Print()
{
}


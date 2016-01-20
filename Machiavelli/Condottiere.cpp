#include "Condottiere.h"
#include "Game.h"


Condottiere::Condottiere() : CharacterCard("Condottiere", CardColor::red, CharacterType::Condottiere){}
Condottiere::~Condottiere(){}

void Condottiere::Execute(Game game)
{
	// Gets one gold coin for each red buildling on table
	game.getCurrentPlayer()->AddGold(game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::red));
	// TODO: Can destroy one buildling from another player. Needs to pay for this the cost of the buildling - 1.
	// Warning: Can NOT destroy from Prediker.

}

void Condottiere::Print()
{
}

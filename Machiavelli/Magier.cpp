#include "Magier.h"
#include "Game.h"


Magier::Magier() : CharacterCard("Tovenaar", CardColor::white, CharacterType::Magiër){}
Magier::~Magier(){}

void Magier::Execute(Game game)
{
	// TODO If player wants, trade cards with other player.
	// TODO OR remove x-amount of cards from hand and get for the same amount of cards new cards from the carddeck.
}

void Magier::Print()
{
}

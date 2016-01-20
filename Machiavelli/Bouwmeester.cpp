#include "Bouwmeester.h"
#include "Game.h"

Bouwmeester::Bouwmeester() : CharacterCard("Bouwmeester", CardColor::white, CharacterType::Bouwmeester){}
Bouwmeester::~Bouwmeester(){}

void Bouwmeester::Execute(Game game)
{
	// TODO: Get two buildling cards in hand.
	// TODO: Can build 3 buildlings in each round!
}

void Bouwmeester::Print() {}

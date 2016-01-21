#include "Moordenaar.h"
#include "Game.h"


Moordenaar::Moordenaar() : CharacterCard("Moordenaar", CardColor::white, CharacterType::Moordenaar){}
Moordenaar::~Moordenaar(){}

void Moordenaar::Execute(Game game)
{
	// TODO Choose which Character he wants to kill.
	// Kill character (isAlive = false);
}

void Moordenaar::Print()
{
}

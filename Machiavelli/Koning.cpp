#include "Koning.h"



Koning::Koning() : CharacterCard("Koning", CardColor::yellow, CharacterType::Koning) { }
Koning::~Koning() { }

void Koning::Execute()
{
	// Is now KING for next round.
	// Gets one gold coin for each gold building on table.
}

void Koning::Print()
{
}

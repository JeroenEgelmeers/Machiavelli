#include "Condottiere.h"



Condottiere::Condottiere() : CharacterCard("Condottiere", CardColor::red, CharacterType::Condottiere){}
Condottiere::~Condottiere(){}

void Condottiere::Execute()
{
	// Gets one gold coin for each red buildling on table
	// Can destroy one buildling from another player. Needs to pay for this the cost of the buildling - 1.

}

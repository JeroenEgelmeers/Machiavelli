#include "Dief.h"
#include "Game.h"


Dief::Dief() : CharacterCard("Dief", CardColor::white, CharacterType::Dief){}
Dief::~Dief(){}

void Dief::Execute(Game game)
{
	game.getCurrentPlayer()->getClient()->write("You're playing the Thief.");
	// TODO:: Say a character to steal gold from. [ Excl: murderer or killed character ]
	
}

void Dief::Print()
{
}

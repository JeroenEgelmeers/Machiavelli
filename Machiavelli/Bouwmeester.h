#pragma once
#include "CharacterCard.h"

class Game;

class Bouwmeester : public CharacterCard
{
public:
	Bouwmeester();
	~Bouwmeester();

	void		Execute(Game game)override; // Should handle everything that the player gets when playing this card.
	void		Print()override; // Should handle the print events of card.

};


#pragma once
#include "CharacterCard.h"

class Game;

class Koopman : public CharacterCard
{
public:
	Koopman();
	~Koopman();

	void		Execute(Game game)override; // Should handle everything that the player gets when playing this card.
	void		Print(); // Should handle the print events of card.
};


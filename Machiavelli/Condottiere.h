#pragma once
#include "CharacterCard.h"

class Game;

class Condottiere : public CharacterCard
{
public:
	Condottiere();
	~Condottiere();

	void		Execute(Game game)override; // Should handle everything that the player gets when playing this card.
	void		Print(); // Should handle the print events of card.

};


#pragma once
#include "CharacterCard.h"

class Game;

class Prediker : public CharacterCard
{
public:
	Prediker();
	~Prediker();

	void	Execute(Game game); // Should handle everything that the player gets when playing this card.
	void	Print(); // Should handle the print events of card.

};


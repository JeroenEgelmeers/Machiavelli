#pragma once
#include "CharacterCard.h"

class Game;

class Moordenaar : public CharacterCard
{
public:
	Moordenaar();
	~Moordenaar();
	
	void		Execute(Game game); // Should handle everything that the player gets when playing this card.
	void		Print(); // Should handle the print events of card.
};


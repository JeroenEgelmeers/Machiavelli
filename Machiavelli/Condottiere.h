#pragma once
#include "CharacterCard.h"
class Condottiere : public CharacterCard
{
public:
	Condottiere();
	~Condottiere();

	void		Execute()override; // Should handle everything that the player gets when playing this card.
	void		Print()override; // Should handle the print events of card.

};


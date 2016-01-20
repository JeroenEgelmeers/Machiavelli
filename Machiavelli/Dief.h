#pragma once
#include "CharacterCard.h"
class Dief : public CharacterCard
{
public:
	Dief();
	~Dief();

	void		Execute()override; // Should handle everything that the player gets when playing this card.
	void		Print()override; // Should handle the print events of card.
};


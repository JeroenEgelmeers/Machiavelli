#pragma once
#include <string>
#include "BaseCard.h"
#include "EnumCard.h"

using namespace std;

class CharacterCard : public BaseCard
{
private:
	
	bool				mSpecialtyPlayed	= false;
	bool				alive				= true;
	bool				beenStolen			= false;

public:
	CharacterCard(string name, CardColor color, CharacterType type = CharacterType::NONE);
	~CharacterCard();

	bool				GetSpecialtyPlayed()	{ return mSpecialtyPlayed; }
	bool				GetIsAlive()			{ return alive; }
	bool				GetBeenStolen()			{ return beenStolen; }

	void		Execute()override; // Should handle everything that the player gets when playing this card.
	void		Print()override; // Should handle the print events of card.
};


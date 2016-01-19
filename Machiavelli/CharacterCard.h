#pragma once
#include <string>
#include "BaseCard.h"
#include "EnumCard.h"

using namespace std;

class CharacterCard : public BaseCard
{
private:
	
	bool		mSpecialtyPlayed	= false;
	bool		mAlive				= true;
	bool		mBeenStolen			= false;

public:
	CharacterCard(string name, CardColor color, CharacterType type = CharacterType::NONE);
	~CharacterCard();

	bool		GetSpecialtyPlayed()	{ return mSpecialtyPlayed; }
	bool		GetIsAlive()			{ return mAlive; }
	bool		GetBeenStolen()			{ return mBeenStolen; }

	void		Execute()override; // Should handle everything that the player gets when playing this card.
	void		Print()override; // Should handle the print events of card.
};


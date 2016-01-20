#pragma once
#include <string>
#include "BaseCard.h"
#include "EnumCard.h"

using namespace std;

class CharacterCard : public BaseCard
{
private:
	
	bool		mSpecialtyPlayed	= false;
	bool		mAlive				= true; // Can be killed by murderer
	bool		mBeenStolen			= false;

public:
	CharacterCard(string name, CardColor color, CharacterType type = CharacterType::NONE);
	~CharacterCard();

	bool		GetSpecialtyPlayed()	{ return mSpecialtyPlayed; }
	bool		GetIsAlive()			{ return mAlive; }
	bool		GetBeenStolen()			{ return mBeenStolen; }
};


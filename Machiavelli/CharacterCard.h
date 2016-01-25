#pragma once
#include <string>
#include "EnumCard.h"

class Game;

class CharacterCard
{
private:
	
	bool		mSpecialtyPlayed	= false;
	bool		mAlive				= true; // Can be killed by murderer
	bool		mBeenStolen			= false;

	bool		mVisible;
	int			mGoldCoins;
	int			mSilverCoins; // Where are those for?
	std::string	mName;
	std::string	mDescription;
	CardColor	mColor;
	CharacterType	mCharacterType;

public:
	CharacterCard(std::string name, CardColor color, CharacterType type = CharacterType::NONE);
	~CharacterCard();

	bool	GetSpecialtyPlayed()	{ return mSpecialtyPlayed; }
	bool	GetIsAlive()			{ return mAlive; }
	bool	GetBeenStolen()			{ return mBeenStolen; }
	void	SetBeenStolen(bool input) { mBeenStolen = input; }

	bool	GetVisible() { return mVisible; }
	void	SetVisible(bool visible) { mVisible = visible; }

	int		GetGoldCoins() { return mGoldCoins; } // Returns only Gold coins
	int		GetSilverCoins() { return mSilverCoins; } // Returns only Silver coins
	int		GetCoins() { return (mGoldCoins + mSilverCoins); } // Returns total coins

	std::string		GetName() { return mName; }
	std::string		GetDescription() { return mDescription; } // Returns for character cards it's specialty

	CardColor		GetColor() { return mColor; }
	CharacterType   GetCharacterType() { return mCharacterType;  }

	virtual void	Execute(Game game) = 0; // Should handle everything that the player gets when playing this card.
	void	Print(); // Should handle the print events of card.
};
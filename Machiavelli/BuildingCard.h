#pragma once
#include "BaseCard.h"

class BuildingCard : public BaseCard
{
private:
	int		mGoldCoins;
	int		mSilverCoins; // Where are those for?

public:
	BuildingCard(string name, CardColor color, int goldCoins, int silverCoins, CharacterType type = CharacterType::NONE);
	~BuildingCard();

	int		GetGoldCoins()		{ return mGoldCoins;	} // Returns only Gold coins
	int		GetSilverCoins()	{ return mSilverCoins;	} // Returns only Silver coins
	int		GetCoins()			{ return (mGoldCoins + mSilverCoins); } // Returns total coins

	void	Execute(Game game)override; // Should handle everything that the player gets when playing this card.
	void	Print()override; // Should handle the print events of card.
};


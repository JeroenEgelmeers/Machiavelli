#pragma once
#include <string>
#include "EnumCard.h"

class Game;

class BuildingCard
{
private:
	bool		mVisible;
	int			mGoldCoins;
	int			mSilverCoins; // Where are those for?
	std::string	mName;
	std::string	mDescription;
	CardColor	mColor;

public:
	BuildingCard(std::string name, CardColor color, int goldCoins, int silverCoins);
	~BuildingCard();
	
	bool	GetVisible() { return mVisible; }
	void	SetVisible(bool visible) { mVisible = visible; }

	int		GetGoldCoins() { return mGoldCoins; } // Returns only Gold coins
	int		GetSilverCoins() { return mSilverCoins; } // Returns only Silver coins
	int		GetCoins() { return (mGoldCoins + mSilverCoins); } // Returns total coins

	std::string		GetName() { return mName; }
	std::string		GetDescription() { return mDescription; } // Returns for character cards it's specialty

	CardColor		GetColor() { return mColor; }

	void	Execute(Game game); // Should handle everything that the player gets when playing this card.
	void	Print(); // Should handle the print events of card.
};


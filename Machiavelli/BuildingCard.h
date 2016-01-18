#pragma once
#include <string>
#include "EnumCardColor.h"

class BuildingCard
{
private:
	std::string			mName;
	BuildingCardColor	mColor; // Enum?
	std::string			mDescription;
	int					mGoldCoins;
	int					mSilverCoins; // Where are those for?

public:
	BuildingCard();
	~BuildingCard();

	std::string			GetName()			{ return mName;			}
	BuildingCardColor	GetCardColor()		{ return mColor;		}
	std::string			GetDescription()	{ return mDescription;	}
	int					GetGoldCoins()		{ return mGoldCoins;	} // Returns only Gold coins
	int					GetSilverCoins()	{ return mSilverCoins;	} // Returns only Silver coins
	int					GetCoins()			{ return (mGoldCoins + mSilverCoins); } // Returns total coins
};


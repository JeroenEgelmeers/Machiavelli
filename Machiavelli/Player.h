//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "CharacterCard.h"
#include "BuildingCard.h"
#include "BaseCard.h"
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Player {
public:
	Player() {}
	Player(const std::string& name) : name {name} {}
	
	// Player information
	std::string get_name() const			{ return name; }
	void set_name(const std::string& new_name) { name = new_name; }

	// Game information
	void AddGold(int amount)				{ mGold += amount; }
	void RemoveGold(int amount)				{ mGold -= amount; }

	void AddHandCard(shared_ptr<BuildingCard> card)			{ buildingCardsInHand.push_back(card); }
	void AddTableCard(shared_ptr<BuildingCard> card)		{ buildingCardsOnTable.push_back(card); }
	void RemoveHandCard(shared_ptr<BuildingCard> card);
	void RemoveTableCard(shared_ptr<BuildingCard> card);

	void PlayCard(shared_ptr<BaseCard> card);

	void PrintHandCards();
	void PrintTableCards();
	void PrintCharacterCards();

	void AddCharacterCard(shared_ptr<CharacterCard> card)	{ characterCards.push_back(card); }
	void RemoveCharacterCard(shared_ptr<CharacterCard> card) { characterCards.erase(find(characterCards.begin(), characterCards.end(), card)); }

	bool IsKing()							{ return mIsKing; }
	void SetKing(bool king)					{ mIsKing = king; }

	bool FirstEightPoints()					{ return mFirstEightPoints; }
	void SetFirstEightPoints(bool first)	{ mFirstEightPoints = first; }

	int  GetBuildingPoints();
	bool DifferentBuildingBonus();
	int	 AmountBuildlingColorOnTable(CardColor color);
	void CalculatePoints();		// set player points on end of match.
	int	 GetWinningPoints()					{ return mPoints; }	// return player points on end of match.

	shared_ptr<CharacterCard> operator [](CharacterType type) {
		for (size_t i = 0; i < characterCards.size(); i++)
		{
			if (characterCards[i]->GetCharacterType() == type) {
				return characterCards[i];
			}
		}
		return nullptr;
	}

private:
	// Player information
	std::string name;
	int		mPlayerID;			// Give the player an ID to identify
	bool	mFirstEightPoints;	// If player reaches as first 8 cards, set to true.

	// Round information
	bool	mIsKing;			// Is the player the king?

	// Game information
	int		mGold		= 0;	// Players gold: start on 0.
	int		mPoints		= 0;	// Players final score.
	vector<shared_ptr<CharacterCard>>	characterCards;
	vector<shared_ptr<BuildingCard>>	buildingCardsOnTable;
	vector<shared_ptr<BuildingCard>>	buildingCardsInHand;
};

#endif /* Player_hpp */

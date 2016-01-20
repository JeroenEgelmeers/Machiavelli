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

	void AddHandCard(BuildingCard card)			{ buildingCardsInHand.push_back(card); }
	void RemoveHandCard(BuildingCard card)		{ buildingCardsInHand.erase(find(buildingCardsInHand.begin(), buildingCardsInHand.end(), card)); }
	void AddTableCard(BuildingCard card)		{ buildingCardsOnTable.push_back(card); }
	void RemoveTableCard(BuildingCard card)		{ buildingCardsOnTable.erase(find(buildingCardsOnTable.begin(), buildingCardsOnTable.end(), card)); }

	void PlayCard(BaseCard card);

	void PrintHandCards();
	void PrintTableCards();
	void PrintCharacterCards();

	void AddCharacterCard(CharacterCard card)	{ characterCards.push_back(card); }
	void RemoveCharacterCard(CharacterCard card) { characterCards.erase(find(characterCards.begin(), characterCards.end(), card)); }

	bool IsKing()							{ return mIsKing; }
	void SetKing(bool king)					{ mIsKing = king; }

	bool FirstEightPoints()					{ return mFirstEightPoints; }
	void SetFirstEightPoints(bool first)	{ mFirstEightPoints = first; }

	void CalculatePoints();	// set player points on end of match.
	int	 GetWinningPoints()					{ return mPoints; }	// return player points on end of match.

private:
	// Player information
	std::string name;
	int		mPlayerID;			// Give the player an ID to identify
	bool	mIsKing;			// Is the player the king?
	bool	mFirstEightPoints;	// If player reaches as first 8 cards, set to true.

	// Game information
	int		mGold		= 0;	// Players gold: start on 0.
	int		mPoints		= 0;	// Players final score.
	std::vector<CharacterCard>	characterCards;
	std::vector<BuildingCard>	buildingCardsOnTable;
	std::vector<BuildingCard>	buildingCardsInHand;
};

#endif /* Player_hpp */

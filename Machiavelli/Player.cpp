//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
#include <memory>
#include <map>
using namespace std;

void Player::PlayCard(BaseCard card) { 
	card.Execute();
}

void Player::PrintHandCards() {
	for (size_t i = 0; i < buildingCardsInHand.size(); i++)
	{
		// Write this line to client.
		// buildingCardsInHand[i].GetDescription();	
	}
}

void Player::PrintTableCards() { 
	for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	{
		// Write this line to client.
		// buildingCardsOnTable[i].GetDescription();	
	}
}

void Player::PrintCharacterCards() { 
	for (size_t i = 0; i < characterCards.size(); i++)
	{
		// Write this line to client.
		// characterCards[i].GetDescription();
	}
}

int Player::GetBuildingPoints()
{
	int points = 0;
	for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	{
		points += buildingCardsOnTable[i].GetCoins();
	}
	return points;
}

bool Player::DifferentBuildingBonus()
{
	map<CardColor, bool> hasDifferentCards;
	hasDifferentCards.insert<CardColor::yellow, false>;
	hasDifferentCards.insert<CardColor::green, false>;
	hasDifferentCards.insert<CardColor::blue, false>;
	hasDifferentCards.insert<CardColor::red, false>;
	hasDifferentCards.insert<CardColor::lila, false>;

	for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	{
		std::map<CardColor, bool>::iterator it = hasDifferentCards.find(buildingCardsOnTable[i].GetColor());
		if (it != hasDifferentCards.end() && !it->second) { it->second = true; }
	}

	map<CardColor, bool>::iterator it;
	bool falseValueFound = false;
	for (it = hasDifferentCards.begin(); it != hasDifferentCards.end(); it++)
	{
		if (!it->second) {
			return false;
		}
	}

	// Player has all different colors card that are described up here.
	return true;
}

void Player::CalculatePoints() {
	// Get buildling points.
	mPoints += GetBuildingPoints();
	// BONUS: First to eight points.
	if (FirstEightPoints)			{ mPoints += 4; }
	// BONUS: All different buildings build.
	if (DifferentBuildingBonus())	{ mPoints += 3; }
	
}
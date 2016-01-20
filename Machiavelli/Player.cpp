//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
#include "Game.h"
#include <memory>
#include <map>
#include <vector>
using namespace std;

void Player::RemoveHandCard(shared_ptr<BuildingCard> card)
{
	for (size_t i = 0; i < buildingCardsInHand.size(); i++)
	{
		if (buildingCardsInHand[i]->GetName() == card->GetName()) {
			buildingCardsInHand.erase(buildingCardsInHand.begin() + i);
			break;
		}
	}
}

void Player::RemoveTableCard(shared_ptr<BuildingCard> card)
{
	for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	{
		if (buildingCardsOnTable[i]->GetName() == card->GetName()) {
			buildingCardsOnTable.erase(buildingCardsOnTable.begin() + i);
			break;
		}
	}
}

void Player::PlayCard(shared_ptr<BaseCard> card)
{
	//card->Execute(game); // TODO :: Should be a game var in Player
}

void Player::PrintHandCards() {
	//for (size_t i = 0; i < buildingCardsInHand.size(); i++)
	//{
	//	// Write this line to client.
	//	// buildingCardsInHand[i].GetDescription();	
	//}
}

void Player::PrintTableCards() { 
	//for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	//{
	//	// Write this line to client.
	//	// buildingCardsOnTable[i].GetDescription();	
	//}
}

void Player::PrintCharacterCards() { 
	//for (size_t i = 0; i < characterCards.size(); i++)
	//{
	//	// Write this line to client.
	//	// characterCards[i].GetDescription();
	//}
}

void Player::SetKing(bool king)
{
	mIsKing = true;
	// TODO Remove the king value from other players!
}

int Player::GetBuildingPoints()
{
	int points = 0;
	for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	{
		points += buildingCardsOnTable[i]->GetCoins();
	}
	return points;
}

bool Player::DifferentBuildingBonus()
{
	map<CardColor, bool> hasDifferentCards;
	hasDifferentCards.insert(std::pair<CardColor, bool>(CardColor::yellow, false));
	hasDifferentCards.insert(std::pair<CardColor, bool>(CardColor::green, false));
	hasDifferentCards.insert(std::pair<CardColor, bool>(CardColor::blue, false));
	hasDifferentCards.insert(std::pair<CardColor, bool>(CardColor::red, false));
	hasDifferentCards.insert(std::pair<CardColor, bool>(CardColor::lila, false));

	for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	{
		std::map<CardColor, bool>::iterator it = hasDifferentCards.find(buildingCardsOnTable[i]->GetColor());
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

int Player::AmountBuildlingColorOnTable(CardColor color)
{
	int amount = 0;
	for (size_t i = 0; i < buildingCardsOnTable.size(); i++)
	{
		if (buildingCardsOnTable[i]->GetColor() == color) {
			amount++;
		}
	}
	return amount;
}

void Player::CalculatePoints() {
	// Get buildling points.
	mPoints += GetBuildingPoints();
	// BONUS: First to eight points.
	if (FirstEightPoints())			{ mPoints += 4; }
	// BONUS: All different buildings build.
	if (DifferentBuildingBonus())	{ mPoints += 3; }
	// BONUS: Player has 8 or more cards build but was not the first player to reach.
	if (buildingCardsOnTable.size() >= 8 && !FirstEightPoints()) { mPoints += 2; }
	
}
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

bool Player::HasAndCanPlayCharacter(CharacterType c)
{
	for (const auto &ch : characterCards) {
		if (ch->GetCharacterType() == c) {
			if (ch->GetIsAlive()) {
				if (ch->GetBeenStolen()) {
					client->write("Arrghh! You've been stolen by the thief! \r\nmachiavelli>");
					for (const auto &p : game->getCurrentPlayers()) {
						for (const auto &thief : p->GetCharacterCards()) {
							if (thief->GetCharacterType() == CharacterType::Dief) {
								p->AddGold(game->getCurrentPlayer()->mGold);
								game->getCurrentPlayer()->RemoveGold(game->getCurrentPlayer()->mGold);
								p->getClient()->write("Muhaha! You stolen " + std::to_string(game->getCurrentPlayer()->mGold) + " gold from "+ game->getCurrentPlayer()->get_name() +" \r\nmachiavelli>");
							}
						}
					}
				}
				return true;
			}
			else {
				client->write("You've got this card but you won't tell them as it's killed by the murderer! \r\nmachiavelli>");
				return false;
			}
		}
	}
	return false;
}

bool Player::PlayCard(int handCardId)
{
	if (buildingCardsInHand.size() >= handCardId) {
		int cost = buildingCardsInHand.at(handCardId)->GetGoldCoins();
		if (cost <= mGold) {
			RemoveGold(cost);
			AddTableCard(buildingCardsInHand.at(handCardId));
			RemoveHandCard(buildingCardsInHand.at(handCardId));
			getClient()->write("Congratulations! You build the card!  \r\nmachiavelli>");
			getClient()->write("You've got " + std::to_string(mGold) + " gold left!  \r\nmachiavelli>");
			return true;
		}
		else {
			getClient()->write("You don't have so much gold!  \r\nmachiavelli>");
			return false;
		}
	}
	else {
		getClient()->write("You don't have this card!  \r\nmachiavelli>");
		return false;
	}
	return false;
}

void Player::PrintHandCards() {	
	// Write this line to client.
	string message = "machiavelli> ";
	message += "You have the following building cards in your hand: \r\nmachiavelli> ";
	for (const auto &c : buildingCardsInHand) {
		message += c->GetName() + ", " + c->GetBuildingColorString() + ", Cost: " + std::to_string(c->GetCoins()) + " \r\nmachiavelli> ";
	}

	client->write(message);
}

void Player::PrintTableCards() { 
	// Write this line to client.
	string message = "machiavelli> ";
	message += "You have build the following buildings: \r\nmachiavelli> ";
	message += "You have build " + std::to_string(buildingCardsOnTable.size()) + " \r\nmachiavelli> ";
	for (const auto &c : buildingCardsOnTable) {
		message += c->GetName() + ", " + c->GetBuildingColorString() + ", Points: " + std::to_string(c->GetCoins()) + " \r\nmachiavelli> ";
	}

	client->write(message);
}

void Player::PrintCharacterCards() {
	// Write this line to client.
	string message = "machiavelli> ";
	message += "You have the following character cards this round: \r\nmachiavelli> ";
	for (const auto &c : characterCards) {
		message += c->GetName() + ", " + c->GetCharacterColorString() + " \r\nmachiavelli> ";
	}

	client->write(message);
}

void Player::ExecuteCharacterCard(int cardID, Game game)
{
	for (const auto &c : characterCards) {
		if (c->GetCharacterType() == CharacterType(cardID)) {
			c->Execute(game);
		}
	}
}

void Player::SetKing(bool king)
{
	mIsKing = king;
	if (!king) {
		SetWasKing(true);
	}
}

void Player::SetWasKing(bool king)
{
	mWasKing = king;
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

std::string Player::getResponse() {
	while (m_response == ""){

	}
	std::string output = m_response;
	setResponse("");

	return output;
}
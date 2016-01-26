//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp


#include "Socket.h"
#include <string>
#include <vector>
#include <memory>
#include "CharacterCard.h"
#include "BuildingCard.h"

using namespace std;

class Game;

static int playerCount;

class Player {
public:
	Player() {}
	Player(const std::string& name, const shared_ptr<Game> game, const shared_ptr<Socket> socket) : client{ socket }, game{ game }, name{ name }, m_isReady{ false }, mPlayerID{ playerCount } { playerCount++; }
	
	// Player information
	std::string get_name() const			{ return name; }
	void set_name(const std::string& new_name) { name = new_name; }

	// Game information
	void AddGold(int amount)				{ mGold += amount; }
	void RemoveGold(int amount)				{ mGold -= amount; }
	int  GetGold() { return mGold; }

	void AddHandCard(shared_ptr<BuildingCard> card)			{ buildingCardsInHand.push_back(card); }
	void AddTableCard(shared_ptr<BuildingCard> card)		{ buildingCardsOnTable.push_back(card); }
	
	void RemoveHandCard(shared_ptr<BuildingCard> card);
	void RemoveTableCard(shared_ptr<BuildingCard> card);
	vector<shared_ptr<BuildingCard>> GetBuildlingCardsOnTable() { return buildingCardsOnTable; }
	vector<shared_ptr<BuildingCard>> GetBuildingCardsInHand() { return buildingCardsInHand; }
	bool HasAndCanPlayCharacter(CharacterType c);
	vector<shared_ptr<BuildingCard>> GetHandCards() { return buildingCardsInHand; }
	void ClearHandCards() { buildingCardsInHand.clear(); }
	size_t BuildingCardsOnTable() { return buildingCardsOnTable.size(); }
	size_t BuildlingCardsInHand() { return buildingCardsInHand.size(); }



	bool PlayCard(int handCardId);

	void PrintHandCards();
	void PrintTableCards();
	void PrintCharacterCards();

	void AddCharacterCard(shared_ptr<CharacterCard> card)	{ characterCards.push_back(card); }
	void RemoveCharacterCard(shared_ptr<CharacterCard> card) { characterCards.erase(find(characterCards.begin(), characterCards.end(), card)); }
	vector<shared_ptr<CharacterCard>> GetCharacterCards() { return characterCards; }
	void ClearCharacterCards() { characterCards.clear(); }
	void ExecuteCharacterCard(int cardID, Game game);

	bool IsKing()							{ return mIsKing; }
	void SetKing(bool king);
	void SetWasKing(bool king);
	bool WasKing() { return mWasKing;  }

	bool FirstEightPoints()					{ return mFirstEightPoints; }
	void SetFirstEightPoints(bool first)	{ mFirstEightPoints = first; }

	int  GetBuildingPoints();
	bool DifferentBuildingBonus();
	int	 AmountBuildlingColorOnTable(CardColor color);
	void CalculatePoints();		// set player points on end of match.
	int	 GetWinningPoints()					{ return mPoints; }	// return player points on end of match.

	bool isReady() { return m_isReady; };
	void isReady(bool r) { m_isReady = r; };

	int getId() { return mPlayerID;  }

	std::string getResponse();
	void setResponse(std::string response) { m_response = response; }

	shared_ptr<CharacterCard> operator [](CharacterType type) {
		for (size_t i = 0; i < characterCards.size(); i++)
		{
			if (characterCards[i]->GetCharacterType() == type) {
				return characterCards[i];
			}
		}
		return nullptr;
	}

	int getCoins() { return mGold; };

	const shared_ptr<Socket> getClient() { return client; }

private:
	// Player information
	std::string m_response;
	std::string name;
	const shared_ptr<Game> game;
	const shared_ptr<Socket> client;

	bool m_isReady;

	int		mPlayerID;			// Give the player an ID to identify
	bool	mFirstEightPoints = false;	// If player reaches as first 8 cards, set to true.

	// Round information
	bool	mIsKing;			// Is the player the king?
	bool	mWasKing;

	// Game information
	int		mGold		= 0;	// Players gold: start on 0.
	int		mPoints		= 0;	// Players final score.
	vector<shared_ptr<CharacterCard>>	characterCards;
	vector<shared_ptr<BuildingCard>>	buildingCardsOnTable;
	vector<shared_ptr<BuildingCard>>	buildingCardsInHand;
};

#endif /* Player_hpp */

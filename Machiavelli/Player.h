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
#include <string>
#include <vector>
using namespace std;

class Player {
public:
	Player() {}
	Player(const std::string& name) : name {name} {}
	
	// Player information
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }

	// Game information
	void AddGold(int amount) { gold += amount; }
	void RemoveGold(int amount) { gold -= amount; }

	void AddHandCard();			// TODO: Implementation; hand cards of player
	void RemoveHandCard();
	void AddTableCard();		// TODO: Implementation; table cards of player
	void RemoveTableCard();

	void AddCharacterCard();	// TODO: Implement character card class
	void RemoveCharacterCard();
	void AddBuildCard();		// TODO: Implement Build card class
	void RemoveBuildCard();


private:
	// Player information
	std::string name;
	int  mPlayerID; // Give the player an ID to identify

	// Game information
	int gold = 0; // Player's gold: start on 0.
	std::vector<CharacterCard> characterCards;
	std::vector<BuildingCard> buildingCards;
};

#endif /* Player_hpp */

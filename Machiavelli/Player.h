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
	void addGold(int amount) { gold += amount; }
	void removeGold(int amount) { gold -= amount; }

	void addHandCard();			// TODO: Implementation; hand cards of player
	void addTableCard();		// TODO: Implementation; table cards of player

	void addCharacterCard();	// TODO: Implement character card class
	void addBuildCard();		// TODO: Implement Build card class

private:
	// Player information
	std::string name;
	int  mPlayerID; // Give the player an ID to identify

	// Game information
	std::vector<CharacterCard> characterCards;
	std::vector<BuildingCard> buildingCards;
	int gold = 0; // Player's gold: start on 0.
};

#endif /* Player_hpp */

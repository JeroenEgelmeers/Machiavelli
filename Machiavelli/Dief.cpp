#include "Dief.h"
#include "Game.h"
#include "EnumCard.h"


Dief::Dief() : CharacterCard("Dief", CardColor::white, CharacterType::Dief){}
Dief::~Dief(){}

void Dief::Execute(Game game)
{
	// Steal from other player
	game.getCurrentPlayer()->getClient()->write("You're playing the Thief.\r\nmachiavelli> ");
	game.getCurrentPlayer()->getClient()->write("From which character would you like to steal gold? \r\nmachiavelli> ");

	game.getCurrentPlayer()->getClient()->write("[1] Magier \r\nmachiavelli> [2] Koning\r\nmachiavelli> [3] Prediker\r\nmachiavelli> [4] Koopman\r\nmachiavelli> [5] Bouwmeester\r\nmachiavelli> [6] Condottiere \r\nmachiavelli> ");
	bool inputTrue = false;
	while (!inputTrue) {
		string response = game.getCurrentPlayer()->getResponse();
		int responseInt = atoi(response.c_str());

		if (responseInt > 0 && responseInt < 7) {
			for (auto const &p : game.getCurrentPlayers()) {
				for (auto const &c : p->GetCharacterCards()) {
					if (c->GetCharacterType() == CharacterType(responseInt+2)) {
						c->SetBeenStolen(true);				
					}
				}
			}
			for (auto const &pl : game.getCurrentPlayers()) {
				pl->getClient()->write("The thief called the " + std::string(CharacterTypeIDToString(responseInt + 2)) + " to steal from.\r\nmachiavelli> ");
			}
			inputTrue = true;
		}
		else {
			game.getCurrentPlayer()->getClient()->write("Invalid input. Try again.\r\nmachiavelli> ");
			inputTrue = false;
		}
	}	
}

void Dief::Print()
{
}

#include "Moordenaar.h"
#include "Game.h"


Moordenaar::Moordenaar() : CharacterCard("Moordenaar", CardColor::white, CharacterType::Moordenaar){}
Moordenaar::~Moordenaar(){}

void Moordenaar::Execute(Game game)
{
	game.getCurrentPlayer()->getClient()->write("You're playing the Murder.\r\nmachiavelli> ");
	game.getCurrentPlayer()->getClient()->write("Which character do you want to kill?\r\nmachiavelli> ");
	game.getCurrentPlayer()->getClient()->write("[1] Dief \r\nmachiavelli> [2] Tovenaar \r\nmachiavelli> [3] Koning \r\nmachiavelli> [4] Prediker \r\nmachiavelli> [5] Koopman \r\nmachiavelli> [6] Bouwmeester \r\nmachiavelli> [7] Condottiere \r\nmachiavelli> ");
	bool inputTrue = false;
	while (!inputTrue) {
		string response = game.getCurrentPlayer()->getResponse();
		int responseInt = atoi(response.c_str());
		if (responseInt > 0 && responseInt < 8) {
			for (auto const &p : game.getCurrentPlayers()) {
				for (auto const &c : p->GetCharacterCards()) {
					if (c->GetCharacterType() == CharacterType(responseInt + 1)) {
						c->SetIsAlive(false);						
					}
				}
			}
			for (auto const &pl : game.getCurrentPlayers()) {
				pl->getClient()->write("The murderer killed the " + std::string(CharacterTypeIDToString(responseInt + 2)) + ".\r\nmachiavelli> ");
			}
			inputTrue = true;
		}
		else {
			game.getCurrentPlayer()->getClient()->write("Invalid input. Try again.\r\nmachiavelli> ");
			inputTrue = false;
		}
	}
	
	
	// TODO Choose which Character he wants to kill.
	// Kill character (isAlive = false);
}

void Moordenaar::Print()
{
}

#include "Magier.h"
#include "Game.h"

using namespace std;

Magier::Magier() : CharacterCard("Tovenaar", CardColor::white, CharacterType::Magier){}
Magier::~Magier(){}

void Magier::Execute(Game game)
{
	// TODO If player wants, trade cards with other player.
	// TODO OR remove x-amount of cards from hand and get for the same amount of cards new cards from the carddeck.

	game.getCurrentPlayer()->getClient()->write("You're playing the Magier.");
	game.getCurrentPlayer()->getClient()->write("You've got some options. Which do you want to do? \r\nmachiavelli> [1] Trade your cards with another player. \r\nmachiavelli> [2] Trade x-amount of your hand cards with new cards. \r\nmachiavelli> [3] Do nothing.");

	bool inputTrue = false;
	while (!inputTrue) {
		string response = game.getCurrentPlayer()->getResponse();
		int responseInt = atoi(response.c_str());
		if (responseInt >= 1 && responseInt <= 3) {
			if (responseInt == 1) {
				// Trade cards with other player
				game.getCurrentPlayer()->getClient()->write("With who do you want to trade cards?");
				int playerSize = 1;
				for (auto const &p : game.getCurrentPlayers()) {
					if (game.getCurrentPlayer()->getId() != p->getId()) {
						game.getCurrentPlayer()->getClient()->write("[ " + std::to_string(playerSize) + " ]" + p->get_name() + " has " + std::to_string(p->GetHandCards().size()) + " cards.");
						playerSize++;
					}
				}
				string response1 = game.getCurrentPlayer()->getResponse();
				int responseInt1 = atoi(response1.c_str());
				if (responseInt1 <= 1 && responseInt1 >= playerSize) {
					int i = 1;
					for (auto const &p : game.getCurrentPlayers()) {
						if (game.getCurrentPlayer()->getId() != p->getId()) {
							if (i == responseInt1) {
								// TODO Switch card hands

								game.getCurrentPlayer()->getClient()->write("Well done! You're trading your cards with: " + p->get_name());
							}
							i++;
						}
					}
				}

			}
			else if (responseInt == 2) {
				// TODO Remove cards from hand and get new cards.
			}
			else if (responseInt == 3) {
				// Do nothing..
			}
			inputTrue = true;
		}
		else {
			inputTrue = false;
		}
	}
}

void Magier::Print()
{
}

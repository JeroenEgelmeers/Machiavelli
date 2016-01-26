#include "Condottiere.h"
#include "Game.h"


Condottiere::Condottiere() : CharacterCard("Condottiere", CardColor::red, CharacterType::Condottiere){}
Condottiere::~Condottiere(){}

void Condottiere::Execute(Game game)
{
	// Gets one gold coin for each red buildling on table
	game.getCurrentPlayer()->getClient()->write("You're playing the Condottiere.\r\nmachiavelli> ");
	int earnsGoldCoins = game.getCurrentPlayer()->AmountBuildlingColorOnTable(CardColor::red);
	if (earnsGoldCoins > 0) {
		game.getCurrentPlayer()->AddGold(earnsGoldCoins);
		game.getCurrentPlayer()->getClient()->write("You earned " + std::to_string(earnsGoldCoins) + " gold for your red buildlings.");
	}

	game.getCurrentPlayer()->getClient()->write("You're playing the Condottiere.\r\nmachiavelli> ");
	string message = "[0] Don't destroy any buildings!\r\nmachiavelli> ";
	int i = 0;
	for (auto const &p : game.getCurrentPlayers()) {
		if (p->getId() != game.getCurrentPlayer()->getId()) {
			if (p->BuildingCardsOnTable() > 0) {
				i++;
				message += "[" + std::to_string(i) + "] " + p->get_name() + " has " + std::to_string(p->BuildingCardsOnTable()) + " buildings on table.\r\nmachiavelli> ";
			}
		}
	}
	game.getCurrentPlayer()->getClient()->write(message);
	bool inputTrue = false;
	while (!inputTrue) {
		string response = game.getCurrentPlayer()->getResponse();
		int responseInt = atoi(response.c_str());
		if (responseInt >= 0 && responseInt <= i) {
			if (responseInt != 0) {
				int innerI = 1;
				for (auto const &p : game.getCurrentPlayers()) {
					if (p->getId() != game.getCurrentPlayer()->getId()) {
						if (p->BuildingCardsOnTable() > 0) {
							if (responseInt == innerI) {
								message = "";
								message = "Which building do you like to destroy?\r\nmachiavelli> ";
								message = "You've got: " + std::to_string(game.getCurrentPlayer()->GetGold()) + " gold.\r\nmachiavelli> ";
								message += "[0] Don't destroy any building. \r\nmachiavelli> ";
								int c = 0;
								for (auto const &ch : p->GetBuildlingCardsOnTable()) {
									c++;
									message += "[" + std::to_string(c) + "] " + ch->GetName() + " - cost: " + std::to_string((ch->GetGoldCoins() - 1)) + "  \r\nmachiavelli> ";
								}
								game.getCurrentPlayer()->getClient()->write(message);
								bool inputTrueInner = false;
								while (!inputTrueInner) {
									string response1 = game.getCurrentPlayer()->getResponse();
									int responseInt1 = atoi(response1.c_str());

									if (responseInt1 >= 0 && responseInt1 <= c) {
										if (responseInt1 != 0) {
											int c1 = 1;
											for (auto const &ch : p->GetBuildlingCardsOnTable()) {
												if (c1 == responseInt1) {
													if ((ch->GetGoldCoins()-1) <= game.getCurrentPlayer()->GetGold()) {
														bool isPrediker = false;
														for (auto const &pred : p->GetCharacterCards()) {
															if (pred->GetCharacterType() == CharacterType::Prediker) {
																isPrediker = true;
															}
														}
														if (isPrediker) {
															for (auto const &p1 : game.getCurrentPlayers()) {
																p1->getClient()->write("The Condottiere tried to destroy " + p->get_name() + "'s building: " + ch->GetName() + ". But the player has the Prediker card! \r\nmachiavelli> ");
															}
														}
														else {
															game.getCurrentPlayer()->RemoveGold((ch->GetGoldCoins() - 1));
															for (auto const &p1 : game.getCurrentPlayers()) {
																p1->getClient()->write("The Condottiere destroyed " + p->get_name() + "'s building: " + ch->GetName() + "\r\nmachiavelli> ");
															}
															p->RemoveTableCard(ch);
														}
													}
													else {
														game.getCurrentPlayer()->getClient()->write("You don't have so much gold.\r\nmachiavelli> ");
													}
													inputTrueInner = true;
												}
												c1++;
											}
										}
										else { inputTrueInner = true; }
									}
									else {
										game.getCurrentPlayer()->getClient()->write("Invalid input. Try again.\r\nmachiavelli> ");
										inputTrueInner = false;
									}
								}

								inputTrue = true;
							}
							innerI++;
						}
					}
				}
			}
			else {
				inputTrue = true;
			}
		}
		else {
			game.getCurrentPlayer()->getClient()->write("Invalid input. Try again.\r\nmachiavelli> ");
		}
	}
}

void Condottiere::Print()
{
}

#include "Bouwmeester.h"
#include "Game.h"

Bouwmeester::Bouwmeester() : CharacterCard("Building master", CardColor::white, CharacterType::Bouwmeester){}
Bouwmeester::~Bouwmeester() {}

void Bouwmeester::Execute(Game game)
{
	game.getCurrentPlayer()->getClient()->write("You're playing the Building master.  \r\nmachiavelli> ");
	// Get two buildling cards in hand.
	game.getCurrentPlayer()->AddHandCard(game.GetBuildlingCardDeck().GetDeck().at(0));
	game.GetBuildlingCardDeck().RemoveCardIndex(0);
	game.getCurrentPlayer()->AddHandCard(game.GetBuildlingCardDeck().GetDeck().at(0));
	game.GetBuildlingCardDeck().RemoveCardIndex(0);
	game.getCurrentPlayer()->getClient()->write("You received two extra building cards.  \r\nmachiavelli> ");

	// Inform other players
	for (auto const &p : game.getCurrentPlayers()) {
		if (p->getId() != game.getCurrentPlayer()->getId()) {
			p->getClient()->write(game.getCurrentPlayer()->get_name() + " received two extra building cards for playing the building master.  \r\nmachiavelli> ");
		}
	}
	// [V] IN GAME: Can build 3 buildings in each round!
}

void Bouwmeester::Print() {}

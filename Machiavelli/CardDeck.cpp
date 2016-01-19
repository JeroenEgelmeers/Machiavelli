#include "CardDeck.h"
#include <algorithm>

CardDeck::CardDeck() {}
CardDeck::~CardDeck() {}

// Shuffle using <algorithm> library.
void CardDeck::ShuffleDeck()							{ random_shuffle(deck.begin(), deck.end()); }
void CardDeck::AddCard(shared_ptr<BaseCard> card)		{ deck.push_back(card); }
void CardDeck::RemoveCard(shared_ptr<BaseCard> card)	{ deck.erase(find(deck.begin(), deck.end(), card)); }

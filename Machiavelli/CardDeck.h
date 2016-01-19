#pragma once
#include "BaseCard.h"
#include <vector>
#include <memory>
#include <algorithm>

class CardDeck
{
public:
	CardDeck();
	~CardDeck();

	void	ShuffleDeck()							{ random_shuffle(deck.begin(), deck.end()); }
	void	AddCard(shared_ptr<BaseCard> card)		{ deck.push_back(card); }
	void	RemoveCard(shared_ptr<BaseCard> card)	{ deck.erase(find(deck.begin(), deck.end(), card)); }
	int		GetDeckSize()							{ return deck.size(); }
	void	ClearDeck()								{ deck.clear(); }
	vector<shared_ptr<BaseCard>> GetDeck()			{ return deck; }

private:
	vector<shared_ptr<BaseCard>> deck;
};


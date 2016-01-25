#pragma once
#include <vector>
#include <memory>
#include <algorithm>

template <class T>
class CardDeck
{
public:
	CardDeck() {};
	~CardDeck() {};

	void	ShuffleDeck()					{ random_shuffle(deck.begin(), deck.end()); }
	void	AddCard(shared_ptr<T> card)		{ deck.push_back(card); }
	void	RemoveCard(shared_ptr<T> card)	{ deck.erase(find(deck.begin(), deck.end(), card)); }
	void	RemoveCardIndex(int index)		{ deck.erase(deck.begin() + index); }
	size_t	GetDeckSize()					{ return deck.size(); }
	void	ClearDeck()						{ deck.clear(); }
	vector<shared_ptr<T>> GetDeck()			{ return deck; }

private:
	vector<shared_ptr<T>> deck;
};


#include "BaseCard.h"



BaseCard::BaseCard(string name, CardColor color, CharacterType cType)
{
	SetName(name);
	SetColor(color);
	SetCharacterType(cType);
}

BaseCard::~BaseCard(){}
void Execute() { }

void Print() { return 0; }

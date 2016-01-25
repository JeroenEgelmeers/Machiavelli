#include "CharacterCard.h"
#include "Game.h"

CharacterCard::CharacterCard(std::string name, CardColor color, CharacterType type) 
	: mCharacterType(type), mName(name), mColor(color)
{
}

CharacterCard::~CharacterCard() {}

void CharacterCard::Print() {} // TODO

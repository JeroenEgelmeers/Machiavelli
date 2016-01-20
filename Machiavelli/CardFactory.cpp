#include "CardFactory.h"
#include "BuildingCard.h"
#include "Moordenaar.h"
#include "Dief.h"
#include "Magier.h"
#include "Koning.h"
#include "Prediker.h"
#include "Koopman.h"
#include "Bouwmeester.h"
#include "Condottiere.h"

CardFactory::CardFactory()
{
	colorResolver = map<string, CardColor>();
	colorResolver.insert(make_pair("wit", CardColor::white));
	colorResolver.insert(make_pair("geel", CardColor::yellow));
	colorResolver.insert(make_pair("groen", CardColor::green));
	colorResolver.insert(make_pair("blauw", CardColor::blue));
	colorResolver.insert(make_pair("rood", CardColor::red));
	colorResolver.insert(make_pair("lila", CardColor::lila));

	cardTypeResolver = map<string, CharacterType>();
	cardTypeResolver.insert(make_pair("NONE", CharacterType::NONE));
	cardTypeResolver.insert(make_pair("Moordenaar", CharacterType::Moordenaar));
	cardTypeResolver.insert(make_pair("Dief", CharacterType::Dief));
	cardTypeResolver.insert(make_pair("Magiër", CharacterType::Magiër));
	cardTypeResolver.insert(make_pair("Koning", CharacterType::Koning));
	cardTypeResolver.insert(make_pair("Prediker", CharacterType::Prediker));
	cardTypeResolver.insert(make_pair("Koopman", CharacterType::Koopman));
	cardTypeResolver.insert(make_pair("Bouwmeester", CharacterType::Bouwmeester));
	cardTypeResolver.insert(make_pair("Condottiere", CharacterType::Condottiere));
}

CardFactory::~CardFactory()
{
}

BaseCard* CardFactory::CreateInstance(string name, int goldCoins, string color) {
	return new BuildingCard(name, colorResolver.find(color)->second, goldCoins, 0);
}

BaseCard* CardFactory::CreateInstance(string type) {
	switch (cardTypeResolver.find(type)->second) {
	case CharacterType::Moordenaar:
		return new Moordenaar();
	case CharacterType::Dief:
		return new Dief();
	case CharacterType::Magiër:
		return new Magier();
	case CharacterType::Koning:
		return new Koning();
	case CharacterType::Prediker:
		return new Prediker();
	case CharacterType::Koopman:
		return new Koopman();
	case CharacterType::Bouwmeester:
		return new Bouwmeester();
	case CharacterType::Condottiere:
		return new Condottiere();
	}
	
	return nullptr;
}
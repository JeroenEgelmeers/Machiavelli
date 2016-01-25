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

using std::make_pair;
using std::string;
using std::map;
using std::make_shared;
using std::shared_ptr;

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
	cardTypeResolver.insert(make_pair("Magier", CharacterType::Magier));
	cardTypeResolver.insert(make_pair("Koning", CharacterType::Koning));
	cardTypeResolver.insert(make_pair("Prediker", CharacterType::Prediker));
	cardTypeResolver.insert(make_pair("Koopman", CharacterType::Koopman));
	cardTypeResolver.insert(make_pair("Bouwmeester", CharacterType::Bouwmeester));
	cardTypeResolver.insert(make_pair("Condottiere", CharacterType::Condottiere));
}

CardFactory::~CardFactory()
{
}

shared_ptr<BuildingCard> CardFactory::CreateInstance(string name, int goldCoins, string color) {
	return make_shared<BuildingCard>(BuildingCard(name, colorResolver.find(color)->second, goldCoins, 0));
}

shared_ptr<CharacterCard> CardFactory::CreateInstance(string type) {
	switch (cardTypeResolver.find(type)->second) {
	case CharacterType::Moordenaar:
		return make_shared<Moordenaar>(Moordenaar());
	case CharacterType::Dief:
		return make_shared<Dief>(Dief());
	case CharacterType::Magier:
		return make_shared<Magier>(Magier());
	case CharacterType::Koning:
		return make_shared<Koning>(Koning());
	case CharacterType::Prediker:
		return make_shared<Prediker>(Prediker());
	case CharacterType::Koopman:
		return make_shared<Koopman>(Koopman());
	case CharacterType::Bouwmeester:
		return make_shared<Bouwmeester>(Bouwmeester());
	case CharacterType::Condottiere:
		return make_shared<Condottiere>(Condottiere());
	}
	
	return nullptr;
}
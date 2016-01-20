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

std::shared_ptr<BaseCard> CardFactory::CreateInstance(string name, int goldCoins, string color) {
	return make_shared<BaseCard>(BuildingCard(name, colorResolver.find(color)->second, goldCoins, 0));
}

std::shared_ptr<BaseCard> CardFactory::CreateInstance(string type) {
	switch (cardTypeResolver.find(type)->second) {
	case CharacterType::Moordenaar:
		return make_shared<BaseCard>(Moordenaar());
	case CharacterType::Dief:
		return make_shared<BaseCard>(Dief());
	case CharacterType::Magiër:
		return make_shared<BaseCard>(Magier());
	case CharacterType::Koning:
		return make_shared<BaseCard>(Koning());
	case CharacterType::Prediker:
		return make_shared<BaseCard>(Prediker());
	case CharacterType::Koopman:
		return make_shared<BaseCard>(Koopman());
	case CharacterType::Bouwmeester:
		return make_shared<BaseCard>(Bouwmeester());
	case CharacterType::Condottiere:
		return make_shared<BaseCard>(Condottiere());
	}
	
	return nullptr;
}
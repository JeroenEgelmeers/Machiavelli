#pragma once
#include <string>
// Warning; should have namespaces when not using C++ 11!  But as we use C++11+ we use the clean version. :)
enum class CardType			{ bouw, karakter};
enum class CardColor		{ white, yellow, green, blue, red, lila };
enum class CharacterType	{ NONE, Moordenaar, Dief, Magiër, Koning, Prediker, Koopman, Bouwmeester, Condottiere };

inline const char* CharacterTypeToString(CharacterType c)
{
	switch (c)
	{
		case CharacterType::Moordenaar:		return "Moordenaar";
		case CharacterType::Dief:			return "Dief";
		case CharacterType::Magiër:			return "Magiër";
		case CharacterType::Koning:			return "Koning";
		case CharacterType::Prediker:		return "Prediker";
		case CharacterType::Koopman:		return "Koopman";
		case CharacterType::Bouwmeester:	return "Bouwmeester";
		case CharacterType::Condottiere:	return "Condottiere";
		default: return "NONE";
	}
}
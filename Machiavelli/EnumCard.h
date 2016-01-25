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
		case CharacterType::Magiër:			return "Tovenaar";
		case CharacterType::Koning:			return "Koning";
		case CharacterType::Prediker:		return "Prediker";
		case CharacterType::Koopman:		return "Koopman";
		case CharacterType::Bouwmeester:	return "Bouwmeester";
		case CharacterType::Condottiere:	return "Condottiere";
		default: return "NONE";
	}
}

inline const char* ColorToString(CardColor c)
{
	switch (c)
	{
	case CardColor::white:		return "White";
	case CardColor::yellow:		return "Yellow";
	case CardColor::green:		return "Green";
	case CardColor::blue:		return "Blue";
	case CardColor::red:		return "Red";
	case CardColor::lila:		return "Lila";
	default:					return "White";
	}
}

inline const char* CharacterTypeIDToString(int c)
{
	switch (c)
	{
		case 1:		return "Moordenaar";
		case 2:		return "Dief";
		case 3:		return "Tovenaar";
		case 4:		return "Koning";
		case 5:		return "Prediker";
		case 6:		return "Koopman";
		case 7:		return "Bouwmeester";
		case 8:		return "Condottiere";
		default:	return "NONE";
	}
}
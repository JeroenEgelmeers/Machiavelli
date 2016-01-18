#pragma once
#include <string>
#include "EnumCardColor.h"

class CharacterCard
{
private:
	std::string			mName;
	CharacterCardColor	mColor;
	std::string			mSpecialty;
	int					mPlayId;

public:
	CharacterCard();
	~CharacterCard();

	std::string			GetName()		{ return mName; }
	CharacterCardColor	GetColor()		{ return mColor; }
	std::string			GetSpecialty()	{ return mSpecialty; }
	int					GetPlayID()		{ return mPlayId; }
};


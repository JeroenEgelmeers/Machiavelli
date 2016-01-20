#pragma once
#include <string>
#include "EnumCard.h"
using namespace std;

class BaseCard
{
private:
	string			mName;
	string			mDescription;
	bool			mVisible;
	CardColor		mColor;
	CharacterType	mCharacterType;

public:
	BaseCard(string name, CardColor color, CharacterType cType = CharacterType::NONE);
	~BaseCard();

	string			GetName()					{ return mName; }
	string			GetDescription()			{ return mDescription;  } // Returns for character cards it's specialty
	bool			GetVisible()				{ return mVisible; }
	void			SetVisible(bool visible)	{ mVisible = visible; }
	CharacterType	GetCharacterType()			{ return mCharacterType; }
	CardColor		GetColor()					{ return mColor; }

	// For setup
	void			SetName(string name)		{ mName = name; }
	void			SetDescription(string desc) { mDescription = desc; }
	void			SetColor(CardColor color)	{ mColor = color; }
	void			SetCharacterType(CharacterType type) { mCharacterType = type; }

	virtual void	Execute();
	virtual void	Print();
};


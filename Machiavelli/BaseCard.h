#pragma once
#include <string>
#include "Game.h"
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

	virtual void	Execute();
	virtual void	Print();

	string			GetName()					{ return mName; }
	string			GetDescription()			{ return mDescription;  }
	bool			GetVisible()				{ return mVisible; }
	void			SetVisible(bool visible)	{ mVisible = visible; }
	CharacterType	GetCharacterType()			{ return mCharacterType; }

	// For setup
	void			SetName(string name)		{ mName = name; }
	void			SetDescription(string desc) { mDescription = desc; }
	void			SetColor(CardColor color)	{ mColor = color; }
	void			SetCharacterType(CharacterType type) { mCharacterType = type; }

};


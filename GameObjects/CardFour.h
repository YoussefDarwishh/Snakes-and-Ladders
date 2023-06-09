#pragma once
#include "Card.h"
#include "Player.h"

class CardFour : public Card
{
public:
	CardFour();
	CardFour(const CellPosition& Position); // A Constructor takes Card Position
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFour on the passed Player
	~CardFour();
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
};
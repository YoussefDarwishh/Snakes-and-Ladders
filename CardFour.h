#pragma once
#include "Card.h"
#include "Player.h"

class CardFour : public Card
{
public:
	CardFour();
	CardFour(const CellPosition& pos); // A Constructor takes card position
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFour on the passed Player
	~CardFour();
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
};
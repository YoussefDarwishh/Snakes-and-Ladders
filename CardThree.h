#pragma once
#include "Card.h"
#include "Player.h"

class CardThree : public Card
{
public:
	CardThree();
	CardThree(const CellPosition& pos); // A Constructor takes card position
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThree on the passed Player
	~CardThree();
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
};
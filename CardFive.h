#pragma once
#include "Card.h"
#include "Player.h"

class CardFive : public Card
{
public:
	CardFive(const CellPosition& pos); // A Constructor takes card position
	CardFive();
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFive on the passed Player
	virtual ~CardFive();
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
};
#pragma once
#include "Card.h"
#include "Player.h"

class CardTwo :	public Card
{
private:

public:
	CardTwo(const CellPosition & Position); // A Constructor takes Card Position
	CardTwo();

//No Read Parameters in this Card

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by decrementing the Player's Wallet by the WalletAmount data member

	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
	virtual ~CardTwo(); // A Virtual Destructor
};


#pragma once
#include "Card.h"
#include "Player.h"

class CardTwelve : public Card
{
private:

public:
	CardTwelve(const CellPosition & Position); // A Constructor takes Card Position
	CardTwelve();

//No Read Parameters in this Card

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwelve on the passed Player
	                                                  // by decrementing the Player's Wallet by the WalletAmount data member
		virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
	virtual ~CardTwelve(); // A Virtual Destructor
};
#pragma once
#include "Card.h"
#include "Player.h"

class CardTwelve : public Card
{
private:

public:
	CardTwelve(const CellPosition & pos); // A Constructor takes card position
	CardTwelve();

//No Read Parameters in this card

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwelve on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
		virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
	virtual ~CardTwelve(); // A Virtual Destructor
};
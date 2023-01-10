#pragma once
#include "Card.h"
#include "Player.h"

class CardSeven : public Card
{
private:
public:
	CardSeven(const CellPosition & pos); // A Constructor takes card position
	CardSeven();

	//there are no read parameters

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member

	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding

	virtual ~CardSeven(); // A Virtual Destructor
};
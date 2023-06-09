#pragma once

#include "Card.h"

// [ CardOne ] Summary:
// Its Apply() Function: Decrements the value of the passing Player’s Wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardOne :	public Card
{
	// CardOne Parameters:
	int WalletAmount; // the Wallet value to decrease from the Player

public:
	CardOne(const CellPosition & Position); // A Constructor takes Card Position
	CardOne();
	void setWallet(int n);
	int getWallet();
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardOne which is: WalletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by decrementing the Player's Wallet by the WalletAmount data member

	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding

	virtual ~CardOne(); // A Virtual Destructor
};
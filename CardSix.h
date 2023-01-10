#pragma once
#include "Card.h"
#include "Player.h"

class CardSix : public Card
{
private:
	CellPosition instructedCell;
public:
	CardSix();
	CardSix(const CellPosition &);
	void setInstructed(CellPosition a);
	CellPosition getInstructed();
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                                                  // by decrementing the player's wallet by the walletAmount data member
	~CardSix();   // A Virtual Destructor
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
};
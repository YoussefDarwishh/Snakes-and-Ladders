#pragma once
#include "Card.h"
#include "Player.h"

class CardEleven : public Card
{
private:
	static Player* Owner;
	static int CardPrice, fee; //it has to be static since all Cards with the number will be same
	static int count; //only once to ask user if he wants to buy
public:
	CardEleven(const CellPosition & Position);
	CardEleven();
	//for 12
	static int getC11P();
	static Player* getC11Owner();
	static void setC11Owner(Player*);
	//for 12
	virtual void ReadCardParameters(Grid * pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
	virtual ~CardEleven(); // A Virtual Destructor
};
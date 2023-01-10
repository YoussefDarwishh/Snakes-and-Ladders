#pragma once
#include "Card.h"
#include "Player.h"

class CardEight : public Card
{
private:
	int fee;
	int check;
public:
	CardEight(const CellPosition & pos);
	CardEight();
	void setfee(int a);
	int getfee();
	virtual void ReadCardParameters(Grid * pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual ~CardEight(); // A Virtual Destructor
	
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
};
#pragma once
#include "Card.h"
#include "Player.h"

class CardNine : public Card
{
private:
	static Player*Owner;
	static int CardPrice, fee; //it has to be static since all Cards with the number will be same
	static int count; //only once to ask user if he wants to buy
public:
	CardNine(const CellPosition & Position);
	CardNine();
	static int getC9P(); // need this for Card 12
	static Player* getC9Owner(); //need this for Card 12
	static void setC9Owner(Player*); // need this for Card 12
	virtual void ReadCardParameters(Grid * pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer); 
	virtual ~CardNine(); // A Virtual Destructor
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding
};
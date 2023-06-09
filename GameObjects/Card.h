#pragma once

#include "GameObject.h"
#include "Player.h"

// Base Class of All Types of Cards (CardOne, CardTwo, CardThree, ...etc.)
// Note: We will make each type of Card in a separate class because:
// it may have additional data members and functions like: Apply(), ...etc. which have different implementation depending on Card Number
class Card : public GameObject
{
private:

protected:
	int CardNumber; // an integer representing the Card number

public:
	Card(const CellPosition & Position); // A Constructor for Card that takes the Cell Position of it
	Card();

	void SetCardNumber(int cnum);   // The setter of Card number
	int GetCardNumber();            // The getter of Card number

	void Draw(Output* pOut) const;  // Draws the Card number in the Cell Position of the Card
	                                // It has the same implementation for all Card Types (Non-Virtual)

	virtual void ReadCardParameters(Grid * pGrid); // It reads the parameters specific for each Card Type
	                                               // It is a virtual function (implementation depends on Card Type)

	virtual void Apply(Grid* pGrid, Player* pPlayer);  // It applies the effect of the Card Type on the passed Player
	                                                   // It is a virtual function (implementation depends on Card Type)
	virtual void Save(ofstream &OutFile, int a); //overriding 
	virtual void Load (ifstream &Ifile, Grid*pGrid, GameObject*type); //overriding



	virtual ~Card(); // A Virtual Destructor
};
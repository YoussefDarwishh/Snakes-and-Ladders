#include "Card.h"

Card::Card(const CellPosition & Position) : GameObject(Position) // sets the Cell Position of the GameObject
{
}

Card::Card()
{
}

void Card::SetCardNumber(int cnum)
{
	if (cnum>0 && cnum<13)
	CardNumber = cnum; // needs Validation
	else
		CardNumber = -1;
}

int Card::GetCardNumber()
{
	return CardNumber;
}

void Card::Draw(Output* pOut) const
{
	pOut->DrawCell(Position,CardNumber);
}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer) 
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a Player reaches a Card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached Card " + to_string(CardNumber) + ". Click to continue ...");
}

void Card :: Save(ofstream &OutFile, int a)
{
}

void Card :: Load (ifstream &Ifile, Grid*pGrid, GameObject*type)
{
}

Card::~Card()
{
}

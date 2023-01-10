#include "CardSeven.h"
#include <fstream>

void CardSeven::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 9)
	{
		OutFile << cardNumber << "\t" << position.GetCellNum() << endl;
	}
}

void CardSeven::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	cardNumber = 7;
	Ifile>>CellPos;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}

CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card

{
	cardNumber = 7;   // set the inherited cardNumber data member with the card number (7 here)
}

CardSeven::CardSeven()
{}
void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("this card restarts the game for the first player whose cell is after the current player click to continue ");
	pIn->GetCellClicked();
	Player* pNextPlayer = pGrid->GetNextPlayer(pPlayer);
	if (pNextPlayer)
	{
		CellPosition start(1);
		pGrid->UpdatePlayerCell(pNextPlayer, start);
		pGrid->UpdateInterface();
	}
	else 
	{
		pGrid->PrintErrorMessage("There are no players after you! Click To continue");
	}

	pOut->ClearStatusBar();
}
CardSeven::~CardSeven(void)
{

}
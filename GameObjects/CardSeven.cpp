#include "CardSeven.h"
#include <fstream>

void CardSeven::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 9)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() << endl;
	}
}

void CardSeven::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	CardNumber = 7;
	Ifile>>CellPos;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}

CardSeven::CardSeven(const CellPosition& Position) : Card(Position) // set the Cell Position of the Card

{
	CardNumber = 7;   // set the inherited CardNumber data member with the Card number (7 here)
}

CardSeven::CardSeven()
{}
void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("this Card restarts the game for the first Player whose Cell is after the Current Player click to continue ");
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
		pGrid->PrintErrorMessage("There are no Players after you! Click To continue");
	}

	pOut->ClearStatusBar();
}
CardSeven::~CardSeven(void)
{

}
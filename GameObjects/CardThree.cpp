#include "CardThree.h"
#include <fstream>

CardThree::CardThree(const CellPosition& Position) : Card(Position) // set the Cell Position of the Card
{
	CardNumber = 3; // set the inherited CardNumber data member with the Card number (3 here)
}

CardThree::CardThree()
{
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)      // Applies the effect of CardThree on the passed Player
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("this Card gives the Player an extra Dice roll click to continue ");
	pIn->GetCellClicked();
	int Playernumber = pGrid->GetCurrentPlayer()->GetPlayerNum();
	if (Playernumber == 0) 
	{
		Playernumber = 3;
	}
	else Playernumber = Playernumber - 1;
	pGrid->SetCurrPlayerNumber(Playernumber);

	pOut->ClearStatusBar();
}


CardThree::~CardThree()
{
}

void CardThree::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 5)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() << endl;
	}
}

void CardThree::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	CardNumber = 3;
	Ifile>>CellPos;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
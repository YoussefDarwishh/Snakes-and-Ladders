#include "CardThree.h"
#include <fstream>

CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

CardThree::CardThree()
{
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)      // Applies the effect of CardThree on the passed Player
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("this card gives the player an extra dice roll click to continue ");
	pIn->GetCellClicked();
	int playernumber = pGrid->GetCurrentPlayer()->GetPlayerNum();
	if (playernumber == 0) 
	{
		playernumber = 3;
	}
	else playernumber = playernumber - 1;
	pGrid->SetCurrPlayerNumber(playernumber);

	pOut->ClearStatusBar();
}


CardThree::~CardThree()
{
}

void CardThree::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 5)
	{
		OutFile << cardNumber << "\t" << position.GetCellNum() << endl;
	}
}

void CardThree::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	cardNumber = 3;
	Ifile>>CellPos;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
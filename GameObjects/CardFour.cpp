#include "CardFour.h"
#include <fstream>

CardFour::CardFour(const CellPosition& Position) : Card(Position) // set the Cell Position of the Card
{
	CardNumber = 4;   // set the inherited CardNumber data member with the Card number (4 here)
}
CardFour::CardFour()
{
}
void CardFour::Apply(Grid* pGrid, Player* pPlayer)  //this Card prevents Player form rolling the next Turn 
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("this Card prevents you from rolling the Dice the next Turn click to continue");
	pIn->GetCellClicked();
	bool f=false;
	pPlayer->setCheckCardFour(f);
	pOut->ClearStatusBar();
}


CardFour::~CardFour()
{
}
void CardFour::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 6)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() << endl;
	}
}

void CardFour::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	CardNumber = 4;
	Ifile>>CellPos;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
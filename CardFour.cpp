#include "CardFour.h"
#include <fstream>

CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4;   // set the inherited cardNumber data member with the card number (4 here)
}
CardFour::CardFour()
{
}
void CardFour::Apply(Grid* pGrid, Player* pPlayer)  //this card prevents player form rolling the next turn 
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("this card prevents you from rolling the dice the next turn click to continue");
	pIn->GetCellClicked();
	bool f=false;
	pPlayer->setcheckCardFour(f);
	pOut->ClearStatusBar();
}


CardFour::~CardFour()
{
}
void CardFour::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 6)
	{
		OutFile << cardNumber << "\t" << position.GetCellNum() << endl;
	}
}

void CardFour::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	cardNumber = 4;
	Ifile>>CellPos;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
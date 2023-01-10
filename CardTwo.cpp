#include "CardTwo.h"
#include "Ladder.h"
#include <fstream>

CardTwo::CardTwo(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (2 here)
}

CardTwo::CardTwo()
{
}

CardTwo :: ~CardTwo(void)
{
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid,pPlayer);
	Output *pOut = pGrid->GetOutput();      
	Input * pIn = pGrid->GetInput();
	pOut->PrintMessage("Card Two Moves player forward to start of next ladder if available, click to continue");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();
	CellPosition CurrentP = pPlayer -> GetCurrentPosition(); //im adding this function to player to get current position
	Ladder*nextL = pGrid->GetNextLadder(CurrentP); //see if theres any next ladder
	if (nextL) //not null
	{
		CellPosition LadderP = nextL->GetPosition(); //INHERITED IN LADDER DONT MAKE A NEW FUNCTION FOR IT YA YOUSSEF
		pGrid->UpdatePlayerCell(pPlayer,LadderP);
		nextL->Apply(pGrid,pPlayer);
	}
	pOut->ClearStatusBar();
}

void CardTwo::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 4)
	{
		OutFile << cardNumber << "\t" << position.GetCellNum() << endl;
	}
}

void CardTwo::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	cardNumber = 2;
	Ifile>>CellPos;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
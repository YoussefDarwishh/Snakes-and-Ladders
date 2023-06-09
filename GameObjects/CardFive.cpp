#include <fstream>
#include "CardFive.h"

CardFive::CardFive(const CellPosition& Position) : Card(Position) // set the Cell Position of the Card
{
	CardNumber = 5;    // set the inherited CardNumber data member with the Card number (5 here)
}

CardFive::CardFive()
{

}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)         // Applies the effect of Cardfive on the passed Player
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("this Card moves you backwards the same steps you moved which is :" + to_string(pPlayer->GetjustRolledDiceNum()) + "  click to continue");
	Input* pIn = pGrid->GetInput();
	pIn->GetCellClicked();
	int Turn = pPlayer->GetTurnCount();   // modifying the trun count before entering the move function 
	Turn--;
	pPlayer->setTurnCount(Turn);
	int movement = -(pPlayer->GetjustRolledDiceNum());                //moves the Player backwards the same steps he has just moved 
	pPlayer->Move(pGrid, movement);
	
	if (pPlayer->GetCell()->HasLadder())
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);    //Checks if there is ladder in the Cell to take it 
	}
	else if (pPlayer->GetCell()->HasSnake()) 
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);     //chekcs if there is snake  in the Cell to take it 
	}
	                                                                    // logically ladder and snake mustnt be implemented but i wrote it as it was asked in the pdf
	
	else if (pPlayer->GetCell()->HasCard())                             
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);     //chekcs if there is Card  in the Cell to take it 
	}
	pOut->ClearStatusBar();
}

CardFive::~CardFive()
{

}

void CardFive::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 7)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() << endl;
	}
}

void CardFive::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	CardNumber = 5;
	Ifile>>CellPos;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
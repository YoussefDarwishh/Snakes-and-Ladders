#include <fstream>
#include "CardFive.h"

CardFive::CardFive(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5;    // set the inherited cardNumber data member with the card number (5 here)
}

CardFive::CardFive()
{

}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)         // Applies the effect of Cardfive on the passed Player
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("this card moves you backwards the same steps you moved which is :" + to_string(pPlayer->GetjustRolledDiceNum()) + "  click to continue");
	Input* pIn = pGrid->GetInput();
	pIn->GetCellClicked();
	int turn = pPlayer->GetTurnCount();   // modifying the trun count before entering the move function 
	turn--;
	pPlayer->setTurnCount(turn);
	int movement = -(pPlayer->GetjustRolledDiceNum());                //moves the player backwards the same steps he has just moved 
	pPlayer->Move(pGrid, movement);
	
	if (pPlayer->GetCell()->HasLadder())
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);    //checks if there is ladder in the cell to take it 
	}
	else if (pPlayer->GetCell()->HasSnake()) 
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);     //chekcs if there is snake  in the cell to take it 
	}
	                                                                    // logically ladder and snake mustnt be implemented but i wrote it as it was asked in the pdf
	
	else if (pPlayer->GetCell()->HasCard())                             
	{
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);     //chekcs if there is card  in the cell to take it 
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
		OutFile << cardNumber << "\t" << position.GetCellNum() << endl;
	}
}

void CardFive::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	cardNumber = 5;
	Ifile>>CellPos;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
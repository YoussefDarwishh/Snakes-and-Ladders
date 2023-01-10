#include <fstream>
#include "Player.h"
#include "CardSix.h"

CardSix::CardSix(const CellPosition &CellPos):Card(CellPos)
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (1 here)
}

CardSix::CardSix()
{

}
 void CardSix:: ReadCardParameters(Grid * pGrid)
 {
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("select the cell to move for");
	CellPosition instructedCel( (CellPosition::GetCellNumFromPosition(pIn->GetCellClicked()) ));
	if (CellPosition :: GetCellNumFromPosition(instructedCel) == 99)
	{
		pOut->PrintMessage("Cannot be cell 99!, select the cell to move for");
		CellPosition a = pIn->GetCellClicked();
		instructedCel.SetHCell(a.HCell());
		instructedCel.SetVCell(a.VCell());
	}
	pOut->ClearStatusBar();
	instructedCell=instructedCel;
	int H=instructedCell.HCell();
	int V=instructedCell.VCell();

 }

 void CardSix:: Apply(Grid* pGrid, Player* pPlayer)
 {
	 Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
// ReadCardParameters( pGrid);
 pGrid->UpdatePlayerCell(pPlayer,instructedCell);
 GameObject*pObj=pPlayer->GetCell()->GetGameObject();
	if (pObj!=NULL)
	{
		pObj->Apply(pGrid,pPlayer);
	}
	pGrid->UpdateInterface();
	pOut->ClearStatusBar();

}

CardSix::~CardSix()  
{

}

void CardSix :: setInstructed(CellPosition a)
{
	instructedCell = a;
}

CellPosition CardSix :: getInstructed()
{
	return instructedCell;
}

void CardSix::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 8)
	{
		OutFile << cardNumber << "\t" << position.GetCellNum() << " " << CellPosition::GetCellNumFromPosition(instructedCell) << endl;
	}
}

void CardSix::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	int Instructed;
	cardNumber = 6;
	Ifile>>CellPos;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	Ifile>>Instructed;
	instructedCell = CellPosition::GetCellPositionFromNum(Instructed);
	pGrid->AddObjectToCell(type);
}
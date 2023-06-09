#include "Snake.h"
#include <fstream>
#include<iostream>
#include "Player.h"
#include"Ladder.h"

using namespace std;
Snake::Snake(const CellPosition & startCellPos, const CellPosition & endCellPos)  :GameObject(startCellPos)
{
	//if (.GetCellNum() >startCellPos.GetCellNum())
	this->endCellPos = endCellPos ;
}

Snake::Snake()  : GameObject(endCellPos)
{
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(Position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Output* pOut= pGrid->GetOutput();
	Input* pIn= pGrid->GetInput();

	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a snake. Click to continue ...");
	// 2- Apply the ladder's effect by moving the Player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	
	pGrid->UpdatePlayerCell( pPlayer,endCellPos);
	pOut->ClearStatusBar();
		GameObject*pObj=pPlayer->GetCell()->GetGameObject();
	if (pObj!=NULL)
	{
		pObj->Apply(pGrid,pPlayer);
	}
	pGrid->UpdateInterface();
	pOut->ClearStatusBar();
	
}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

bool Snake:: isoverlapping(GameObject*a) const
{
	//avoid Checking on the same snake
	if(this==a)
		return false;

	//End and start of Snake
	int StartCell1=Position.VCell();
	int EndCell1=endCellPos.VCell();

	if(dynamic_cast<Snake*>(a))
	{
		Snake* pladder=(Snake*)a;

		int StartCell2=a->GetPosition().VCell();
		int EndCell2=pladder->GetEndPosition().VCell();

		//End of ladder and snake will make this Validation
		if (StartCell2 == StartCell1)
			{
				return false;
			}

			//Validation of overlapping of snakes
		if( !(EndCell2<StartCell1 || StartCell2>EndCell1) )
		{
			return true;
		}
		else
			return false;
	}

	//adding ladder on snake
	else if(dynamic_cast<Ladder*>(a))
	{
		Ladder * psnake=(Ladder*)a;

		int StartCell2=psnake->GetPosition().VCell();
		int EndCell2=psnake->GetEndPosition().VCell();

		//Validation of overlapping snake and a ladder
		if( EndCell2==StartCell1 || EndCell1==StartCell2 )
		{
			return true;
		}
		else 
			return false;

	}
}

void Snake :: Save (ofstream&Outfile, int a)
{
	if (a == 2)
	{
		Outfile<< Position.GetCellNum() <<" "<<endCellPos.GetCellNum() << endl;
	}
}


void Snake :: Load(ifstream &Infile,Grid*pGrid,GameObject*type)
{
	int startCell, endCell;
	Infile>>startCell>>endCell;
	endCellPos = CellPosition :: GetCellPositionFromNum(endCell);
	Position = CellPosition :: GetCellPositionFromNum(startCell);
	pGrid->AddObjectToCell(type);
}

Snake::~Snake(void)
{
}
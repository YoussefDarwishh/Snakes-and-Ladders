#include "Ladder.h"
#include "Card.h"
#include "Snake.h"
#include <fstream>

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	///TODO: Do the needed validation
	if (endCellPos.GetCellNum() >startCellPos.GetCellNum())
		this->endCellPos = endCellPos;
	notDeleted = 1;
}

Ladder:: Ladder() : GameObject(endCellPos)
{
	notDeleted = 1;
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}


void Ladder::remove(Output* pOut) 
{
	notDeleted=0;
	pOut->removeLadder(position,endCellPos);
}


void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Output* pOut= pGrid->GetOutput();
	Input* pIn= pGrid->GetInput();

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a ladder. Click to continue ...");
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	if (notDeleted==1)
	{
		pGrid->UpdatePlayerCell( pPlayer,endCellPos);
	}

	GameObject*pObj=pPlayer->GetCell()->GetGameObject();
	if (pObj!=NULL)
	{
		pObj->Apply(pGrid,pPlayer);
	}
	pGrid->UpdateInterface();
	pOut->ClearStatusBar();
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

bool Ladder::isoverlapping(GameObject*a) const
{
	//avoid checking on the same ladder
		if(this==a)
			return false;

		//End and start potions of Ladder
		int StartCell1=position.VCell();
		int EndCell1=endCellPos.VCell();

		//adding ladder on ladder
		if(dynamic_cast<Ladder*>(a))
		{
			Ladder* pladder=(Ladder*)a;

			int StartCell2=pladder->GetPosition().VCell();
			int EndCell2=pladder->GetEndPosition().VCell();

			//End of ladder and snake will make this validation
			if (StartCell2 == StartCell1)
			{
				return false;
			}

			//validation of overlapping of two ladders
			if( !(EndCell2>StartCell1 || StartCell2<EndCell1) )
				return true;
			else
				return false;
		}

		//adding ladder on snake
		else if(dynamic_cast<Snake*>(a))
		{
			Snake * psnake=(Snake*)a;

			int StartCell2=psnake->GetPosition().VCell();
			int EndCell2=psnake->GetEndPosition().VCell();

			//validation of overlapping snake and a ladder
			if( EndCell2==StartCell1 || EndCell1==StartCell2 )
			{
				return true;
			}
			else
				return false;

		}
}

void Ladder:: Save(ofstream &OutFile, int a)
{
	if (a == 1)
	{
		OutFile<< position.GetCellNum() <<" "<<endCellPos.GetCellNum() << endl;
	}
}

void Ladder :: Load(ifstream &Infile,Grid*pGrid,GameObject*type)
{
	int startcell, endcell;
	Infile>>startcell>>endcell;
	endCellPos = CellPosition :: GetCellPositionFromNum(endcell);
	position = CellPosition :: GetCellPositionFromNum(startcell);
	pGrid->AddObjectToCell(type);
}

Ladder::~Ladder()
{
}
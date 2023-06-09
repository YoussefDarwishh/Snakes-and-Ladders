#include <fstream>
#include "CardEight.h"
#include"CardOne.h"
#include<iostream>
using namespace std;

CardEight::CardEight(const CellPosition & Position): Card(Position),Check(0)
{
	CardNumber=8;
	fee = 0;
}

CardEight::CardEight()
	{
	}

void CardEight::ReadCardParameters(Grid * pGrid)
{
	Input*pIn=pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Enter the value to be paid to get out of prison the Player with: ");
	int a = pIn ->GetInteger(pGrid->GetOutput());
	if ( a>0)
	{
		fee=a;
	}
	else 
		pOut->PrintMessage("sorry you enter either negative or zero: ");
	// [ Note ]:
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();
	

}
void CardEight:: Apply(Grid* pGrid, Player* pPlayer)
{
	Input*pIn=pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("do you want to go to prison? if yes enter 1 else enter 0 to pay ");
	int choice=pIn ->GetInteger(pGrid->GetOutput());
	Check=choice;
	if (Check==0)
	{
	int w=pPlayer->GetWallet();
	w=w-fee;
	pPlayer->SetWallet(w);
	}
	else 
	{
	pPlayer->setCheckCardEight(1);
	}
}

void CardEight :: setfee(int a)
	{
		fee = a;
	}
int CardEight :: getfee()
	{
		return fee;
	}

CardEight:: ~CardEight() // A Virtual Destructor
{}

void CardEight::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 10)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() <<" " << fee << endl;
	}
}

void CardEight::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	int amount;
	CardNumber = 8;
	Ifile>>CellPos;
	Ifile>>amount;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	fee = amount;
	pGrid->AddObjectToCell(type);
}
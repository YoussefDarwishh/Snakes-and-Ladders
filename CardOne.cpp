#include "CardOne.h"
#include <fstream>

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	int walletAmount=0; // the amount to  be decreased from the user
}

CardOne::CardOne()
{
	int walletAmount=0; // the amount to  be decreased from the user
}

CardOne::~CardOne(void)
{
}

void CardOne :: setwallet(int n)
{
	walletAmount = n;
}
int CardOne :: getwallet()
{
	return walletAmount;
}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Input * pIn=pGrid -> GetInput();
	Output * pOut=pGrid -> GetOutput();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	pOut->PrintMessage("Enter the value to decrement the player with: ");
	int a = pIn ->GetInteger(pGrid->GetOutput());
	if ( a>0)
	{
	walletAmount=a;
	}
	else 
		pOut->PrintMessage("sorry you enter either negative or zero: ");
	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply( pGrid,  pPlayer) ;
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	int w=pPlayer->GetWallet();
	w=w-walletAmount;
	pPlayer->SetWallet(w);
}

void CardOne::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 3)
	{
		OutFile << cardNumber << "\t" << position.GetCellNum() << " " << walletAmount << endl;
	}
}

void CardOne::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	int walletam;
	cardNumber = 1;
	Ifile>>CellPos;
	Ifile>>walletam;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	walletAmount = walletam;
	pGrid->AddObjectToCell(type);
}
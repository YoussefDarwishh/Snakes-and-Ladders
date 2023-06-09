#include "CardOne.h"
#include <fstream>

CardOne::CardOne(const CellPosition & Position) : Card(Position) // set the Cell Position of the Card
{
	CardNumber = 1; // set the inherited CardNumber data member with the Card number (1 here)
	int WalletAmount=0; // the amount to  be decreased from the user
}

CardOne::CardOne()
{
	int WalletAmount=0; // the amount to  be decreased from the user
}

CardOne::~CardOne(void)
{
}

void CardOne :: setWallet(int n)
{
	WalletAmount = n;
}
int CardOne :: getWallet()
{
	return WalletAmount;
}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Input * pIn=pGrid -> GetInput();
	Output * pOut=pGrid -> GetOutput();
	// 2- Read an Integer from the user using the Input class and set the WalletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its Wallet amount ..."
	pOut->PrintMessage("Enter the value to decrement the Player with: ");
	int a = pIn ->GetInteger(pGrid->GetOutput());
	if ( a>0)
	{
	WalletAmount=a;
	}
	else 
		pOut->PrintMessage("sorry you enter either negative or zero: ");
	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "WalletAmount" value to decrease from Player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this Card number
	Card::Apply( pGrid,  pPlayer) ;
	// 2- Decrement the Wallet of pPlayer by the WalletAmount data member of CardOne
	int w=pPlayer->GetWallet();
	w=w-WalletAmount;
	pPlayer->SetWallet(w);
}

void CardOne::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 3)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() << " " << WalletAmount << endl;
	}
}

void CardOne::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	int Walletam;
	CardNumber = 1;
	Ifile>>CellPos;
	Ifile>>Walletam;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	WalletAmount = Walletam;
	pGrid->AddObjectToCell(type);
}
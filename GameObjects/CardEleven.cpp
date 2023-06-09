#include "CardEleven.h"
using namespace std;
#include <iostream>
#include <fstream>

//initalizing them with zero
Player * CardEleven :: Owner;
int CardEleven :: fee = 0;
int CardEleven :: CardPrice = 0;
int CardEleven :: count = 0; // to Check user enters once only

CardEleven::CardEleven(const CellPosition & Position) : Card(Position)
{
	CardNumber = 11;
}

CardEleven::CardEleven()
{
}

void CardEleven::ReadCardParameters(Grid * pGrid)
{
	if (count != 1)
	{
		pGrid -> GetOutput() ->PrintMessage("Enter the price of Card: ");
		int a = pGrid -> GetInput() ->GetInteger(pGrid->GetOutput());
		if (a>0)
		{
			CardPrice = a;
		}
		else
		{
				pGrid -> GetOutput() ->PrintMessage("Error! Cardprice cannot be negative");
				return;
		}

		pGrid -> GetOutput() ->PrintMessage("Enter the fee of Card: ");
		int b = pGrid -> GetInput() ->GetInteger(pGrid->GetOutput());
		if (b>0)
			fee = b;
		else
		{
				pGrid -> GetOutput() ->PrintMessage("Error! fee cannot be negative");
				return;
		}

		count ++;
	}
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	int PWallet = pPlayer->GetWallet();
	//If Cell was not bought asking if user wants to buy it
	if (Owner == NULL)
	{
		pOut->PrintMessage("this Card costs: " + to_string(CardPrice) + " do you want to buy it? Press 1 for yes, 2 for no");
		int a = pIn->GetInteger(pOut);
		if (a == 1)
		{
			if (PWallet<CardPrice)
			{
				pOut-> PrintMessage("Sorry, you dont have enough money in your Wallet to buy!");
			}
			else
			{
				PWallet = PWallet - CardPrice;
				pPlayer -> SetWallet(PWallet);
				Owner=(pGrid -> GetCurrentPlayer());
			}
		}
		else
		{
			pOut ->PrintMessage("click to continue");
			pIn->GetCellClicked();
		}
	}
	// Checking if any other Player steps on Cell
	else
	{
		int PlayerWallet = pPlayer -> GetWallet();
		if (pPlayer != Owner)
		{
			pOut->PrintMessage("You have visted the property of Player " + to_string(Owner->GetPlayerNum()) + " You have to pay him: " + to_string(fee) + " click to continue...");
			if (PlayerWallet < CardPrice)
			{
				pOut->PrintMessage("You dont have enough money to pay! Whatever was in your Wallet has been given to owner and you Wallet is set to zero");
			    Owner -> SetWallet(Owner ->GetWallet() + pPlayer->GetWallet());
				pPlayer -> SetWallet(0);
			}
			else
			{
				PlayerWallet = PlayerWallet - fee;
				pPlayer -> SetWallet(PlayerWallet);
				Owner -> SetWallet(Owner ->GetWallet() + fee);
			}
		}

	}
}

int CardEleven::getC11P()
{
	return CardPrice;
}
Player* CardEleven::getC11Owner()
{
	return Owner;
}
void CardEleven::setC11Owner(Player*newowner)
{
	Owner = newowner;
}


CardEleven :: ~CardEleven()
{
}

void CardEleven::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 13)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() << " " << CardPrice << " " << fee << endl;
	}
}

void CardEleven::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	int price;
	int fees;
	CardNumber = 11;
	Ifile>>CellPos;
	Ifile>> price;
	Ifile>> fees;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	CardPrice = price;
	fee = fees;
	pGrid->AddObjectToCell(type);
}
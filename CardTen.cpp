#include "CardTen.h"
using namespace std;
#include <iostream>
#include <fstream>
//initalizing them with zero
Player * CardTen :: Owner = NULL;
int CardTen :: fee = 0;
int CardTen :: CardPrice = 0;
int CardTen :: count = 0; // to check user enters once only

CardTen::CardTen(const CellPosition & pos) : Card(pos)
{
	cardNumber = 10;
}

CardTen::CardTen()
{
}

void CardTen::ReadCardParameters(Grid * pGrid)
{
	if (count != 1)
	{
		pGrid -> GetOutput() ->PrintMessage("Enter the price of card: ");
		int a = pGrid -> GetInput() ->GetInteger(pGrid->GetOutput());
		if (a>0)
		{
			CardPrice = a;
		}
		else
		{
				pGrid -> GetOutput() ->PrintMessage("Error! cardprice cannot be negative");
				return;
		}

		pGrid -> GetOutput() ->PrintMessage("Enter the fee of card: ");
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

void CardTen::Apply(Grid* pGrid, Player* pPlayer)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	int Pwallet = pPlayer->GetWallet();
	//If cell was not bought asking if user wants to buy it
	if (Owner == NULL)
	{
		pOut->PrintMessage("this card costs: " + to_string(CardPrice) + " do you want to buy it? Press 1 for yes, 2 for no");
		int a = pIn->GetInteger(pOut);
		if (a == 1)
		{
			if (Pwallet<CardPrice)
			{
				pOut-> PrintMessage("Sorry, you dont have enough money in your wallet to buy!");
			}
			else
			{
				Pwallet = Pwallet - CardPrice;
				pPlayer -> SetWallet(Pwallet);
				Owner=(pGrid -> GetCurrentPlayer());
			}
		}
		else
		{
			pOut ->PrintMessage("click to continue");
			pIn->GetCellClicked();
		}
	}
	// checking if any other player steps on cell
	else
	{
		int playerwallet = pPlayer -> GetWallet();
		if (pPlayer != Owner)
		{
			pOut->PrintMessage("You have visted the property of player " + to_string(Owner->GetPlayerNum()) + " You have to pay him: " + to_string(fee) + " click to continue...");
			if (playerwallet < CardPrice)
			{
				pOut->PrintMessage("You dont have enough money to pay! Whatever was in your wallet has been given to owner and you wallet is set to zero");
			    Owner-> SetWallet(Owner ->GetWallet() + pPlayer->GetWallet());
				pPlayer -> SetWallet(0);
			}
			else
			{
				playerwallet = playerwallet - fee;
				pPlayer -> SetWallet(playerwallet);
				Owner-> SetWallet(Owner ->GetWallet() + fee);
			}
		}

	}
}

int CardTen::getC10P()
{
	return CardPrice;
}
Player* CardTen::getC10Owner()
{
	return Owner;
}
void CardTen::setC10Owner(Player*newowner)
{
	Owner = newowner;
}


CardTen :: ~CardTen()
{
}

void CardTen::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 12)
	{
		OutFile << cardNumber << "\t" << position.GetCellNum() << " " << CardPrice << " " << fee << endl;
	}
}

void CardTen::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	int price;
	int fees;
	cardNumber = 10;
	Ifile>>CellPos;
	Ifile>> price;
	Ifile>> fees;
	position = CellPosition::GetCellPositionFromNum(CellPos);
	CardPrice = price;
	fee = fees;
	pGrid->AddObjectToCell(type);

}
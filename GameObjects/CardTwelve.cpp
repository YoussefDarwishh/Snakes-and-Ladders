#include "CardTwelve.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include <fstream>

CardTwelve::CardTwelve(const CellPosition & Position) : Card(Position) // set the Cell Position of the Card
{
	CardNumber = 12; // set the inherited CardNumber data member with the Card number (1 here)
}

CardTwelve::CardTwelve()
{
}

CardTwelve :: ~CardTwelve(void)
{
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this Card number
	Card::Apply(pGrid,pPlayer);
	Output *pOut = pGrid->GetOutput();      
	Input * pIn = pGrid->GetInput();
	Player*p = pGrid->GetPlayerLeastMoney();
	int C9P = CardNine::getC9P();
	int C10P = CardTen::getC10P();
	int C11P = CardEleven::getC11P();
	Player*C9Owner = CardNine::getC9Owner();
	Player*C10Owner = CardTen::getC10Owner();
	Player*C11Owner = CardEleven::getC11Owner();
	//i am changing so much in the code ya gama3a please Check my work

	pOut->PrintMessage("Card Twelve will move the most expensive station you own (if any) to one with least coins, click to continue");
	pIn->GetCellClicked();
	//this is NOT the most efficient thing at all should i do this in a switch case?

	if (pPlayer == C9Owner && pPlayer == C10Owner && pPlayer == C11Owner)
	{
		pOut->PrintMessage("You own the 3 stations! Your most expensive station will be moved, click to continue");
		pIn->GetCellClicked();

		if(C9P >=C10P && C9P >= C11P)
		{
		pOut->PrintMessage("Your Station 9 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
		CardNine::setC9Owner(p);
		}
		else if (C10P>= C9P && C10P >= C11P)
		{
		pOut->PrintMessage("Your Station 10 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
		CardTen::setC10Owner(p);
		}
		else if (C11P >= C9P && C11P >= C10P)
		{
		pOut->PrintMessage("Your Station 11 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
		CardEleven::setC11Owner(p);
		}
  
	}

	else if (pPlayer == C9Owner && pPlayer == C10Owner)
	{
		pOut->PrintMessage("You own the 2 stations! Your most expensive station will be moved, click to continue");
		pIn->GetCellClicked();
		if (C9P>= C10P)
		{
		pOut->PrintMessage("Your Station 9 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
			CardNine::setC9Owner(p);
		}
		else
		{
		pOut->PrintMessage("Your Station 10 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
		CardTen::setC10Owner(p);
		}
	}

	else if (pPlayer == C9Owner && pPlayer == C11Owner)
	{
		pOut->PrintMessage("You own the 2 stations! Your most expensive station will be moved, click to continue");
		pIn->GetCellClicked();
		if (C9P >= C11P)
		{
		pOut->PrintMessage("Your Station 9 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
			CardNine::setC9Owner(p);
		}
		else
		{
		pOut->PrintMessage("Your Station 11 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
			CardEleven::setC11Owner(p);
		}
	}

	else if (pPlayer == C10Owner && pPlayer == C11Owner)
	{
		pOut->PrintMessage("You own the 2 stations! Your most expensive station will be moved, click to continue");
		pIn->GetCellClicked();
		if (C10P>= C11P)
		{
		pOut->PrintMessage("Your Station 10 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
		CardTen::setC10Owner(p);
		}
		else
		{
		pOut->PrintMessage("Your Station 11 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
			CardEleven::setC11Owner(p);
		}
	}


	else if (pPlayer == C9Owner)
	{
		pOut->PrintMessage("Your Station 9 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
			CardNine::setC9Owner(p);
	}

	else if (pPlayer == C10Owner)
	{
		pOut->PrintMessage("Your Station 10 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
		CardTen::setC10Owner(p);
	}

	else if (pPlayer == C11Owner)
	{
		pOut->PrintMessage("Your Station 11 will be moved to Player " + to_string(p->GetPlayerNum()) + " as he has least money");
			CardEleven::setC11Owner(p);
	}
	else
	{
		pOut->PrintMessage("You do not own any station, nothing will happen. Click to continue");
		pIn->GetCellClicked();
	}

	pOut->ClearStatusBar();
}

void CardTwelve::Save(ofstream &OutFile, int a) //overriding 
{
	if (a == 14)
	{
		OutFile << CardNumber << "\t" << Position.GetCellNum() << endl;
	}
}

void CardTwelve::Load (ifstream &Ifile, Grid*pGrid, GameObject*type)//overriding
{
	int CellPos;
	CardNumber = 12;
	Ifile>>CellPos;
	Position = CellPosition::GetCellPositionFromNum(CellPos);
	pGrid->AddObjectToCell(type);
}
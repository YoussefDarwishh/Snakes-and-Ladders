#include "LoadGridAction.h"
#include "Grid.h"
#include "Ladder.h"
#include "CellPosition.h"
#include "AddLadderAction.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "Snake.h"
#include <fstream>

LoadGridAction::LoadGridAction (ApplicationManager *pApp) : Action(pApp)
{
}

void LoadGridAction :: ReadActionParameters()
{
	pGrid = pManager->GetGrid();
	pGrid->GetOutput()->PrintMessage("Please Enter The File Name"); //reading file name
	name = pGrid->GetInput()->GetSrting(pGrid->GetOutput());
}

void LoadGridAction :: Execute()
{
	ReadActionParameters();
	ifstream Ifile(name + ".txt", ios::in); //again if we dont put the .txt sometimes it doesnt actually work and makes a weird extension'
	if (Ifile.is_open())
	{
		int LadderNum=0;
		Ifile >> LadderNum;
		for (int i = 0; i<LadderNum; i++)
		{
			GameObject*pLadder = new Ladder(); //Creating empty object of ladder
			pLadder->Load(Ifile,pGrid,pLadder);
		}

		int SnakeNum=0;
		Ifile>>SnakeNum;
		for (int i=0; i<SnakeNum; i++)
		{
			GameObject*pSnake = new Snake();//empty object of snake
			pSnake->Load(Ifile,pGrid,pSnake);
		}
		int CardsNum = 0;
		int CardType = 1;
		Ifile >> CardsNum;
		for (int i=0; i<CardsNum; i++) //looping for all cards available
		{
			Ifile>>CardType; //i used if's to see which cardtype there is and calling its load function respectivly 
			if (CardType == 1)
			{
				GameObject*pCard1 = new CardOne();
				pCard1->Load(Ifile,pGrid,pCard1);
			}
			else if (CardType == 2)
			{
				GameObject*pCard2 = new CardTwo();
				pCard2->Load(Ifile,pGrid,pCard2);
			}
			else if (CardType == 3)
			{
				GameObject*pCard3 = new CardThree();
				pCard3->Load(Ifile,pGrid,pCard3);
			}
			else if (CardType == 4)
			{
				GameObject*pCard4 = new CardFour();
				pCard4->Load(Ifile,pGrid,pCard4);
			}
			else if (CardType == 5)
			{
				GameObject*pCard5 = new CardFive();
				pCard5->Load(Ifile,pGrid,pCard5);
			}
			else if (CardType == 6)
			{
				GameObject*pCard6 = new CardSix();
				pCard6->Load(Ifile,pGrid,pCard6);
			}
			else if (CardType == 7)
			{
				GameObject*pCard7 = new CardSeven();
				pCard7->Load(Ifile,pGrid,pCard7);
			}
			else if (CardType == 8)
			{
				GameObject*pCard8 = new CardEight();
				pCard8->Load(Ifile,pGrid,pCard8);
			}
			else if (CardType == 9)
			{
				GameObject*pCard9 = new CardNine();
				pCard9->Load(Ifile,pGrid,pCard9);
			}
			else if (CardType == 10)
			{
				GameObject*pCard10 = new CardTen();
				pCard10->Load(Ifile,pGrid,pCard10);
			}
			else if (CardType == 11)
			{
				GameObject*pCard11 = new CardEleven();
				pCard11->Load(Ifile,pGrid,pCard11);
			}
			else if (CardType == 12)
			{
				GameObject*pCard12 = new CardTwelve();
				pCard12->Load(Ifile,pGrid,pCard12);
			}
		}
	}
	Ifile.close();
}

LoadGridAction :: ~LoadGridAction()
{
}
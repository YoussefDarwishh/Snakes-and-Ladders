#include "RollDiceAction.h"
#include"Windows.h"
#include "Grid.h"
#include "Player.h"
#include<iostream>
using namespace std;
#include"Windows.h"
#include"MMSystem.h"
#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *ProjectApp) : Action(ProjectApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Grid* pGrid ;
	pGrid = ProjectManager->GetGrid();
	Output* pOut;
	pOut = pGrid->GetOutput();

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action



	if(pGrid->GetEndGame()==true)
	{
		//printing info of the winner
		Player *pwin;
		pwin=pGrid->GetCurrentPlayer();
		bool music;
		music=PlaySoundA((LPCSTR) "winning_charle.wav", NULL, SND_FILENAME | SND_ASYNC);
		//cout<<"success:"<<music;
		int pnum;
		pnum=pwin->GetPlayerNum();

		string snum=to_string(pnum);

		string msg="Player" +snum +" has Won";
		pOut->PrintMessage(msg);
	}

	else
	{
		// -- If not ended, do the following --:

		// 2- Generate a random number from 1 to 6 --> This step is done for you
		
		srand((int)time(NULL));              // time is for different seed each run
		int DiceNumber = 1 + rand() % 6;    // from 1 to 6 --> should change seed

		// 3- Get the "Current" Player from pGrid

		Player* CurrentPlayer;
		CurrentPlayer=pGrid->GetCurrentPlayer();

		//Check if the Player is going to win by omar

		Cell * CurrentPlayerCell;
		CurrentPlayerCell=CurrentPlayer->GetCell();
		CellPosition cp;
		cp =CurrentPlayerCell->GetCellPosition();
		int Cellnum;
		Cellnum=cp.GetCellNum();

		//make the Player win if rolled value >the last Cells
		int cond=99-Cellnum;
		if(cond<6)
		{
			if(DiceNumber>cond)
			{
				DiceNumber=cond;
			}
		}

		// 4- Move the CurrentPlayer using function Move of class Player

		CurrentPlayer->Move(pGrid,DiceNumber);

		// 5- Advance the Current Player number of pGrid

		pGrid->AdvanceCurrentPlayer();

	}
	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

RollDiceAction::~RollDiceAction()
{
}

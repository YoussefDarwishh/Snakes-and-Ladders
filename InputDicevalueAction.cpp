#include "InputDiceValueAction.h"
#include "Grid.h"
#include "Player.h"



InputDiceValueAction::InputDiceValueAction(ApplicationManager *pApp)  : Action(pApp)
{

}

void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	valid=false;
	int dicevalue=0;
	while (valid==false)
	{

		pOut->PrintMessage("enter dice value from 1 to 6");
		dicevalue=pIn->GetInteger(pOut);

		if(dicevalue<=0 || dicevalue>6)
		{
			pGrid->PrintErrorMessage("Invalid value, please click to Re-Enter");
		}
		else
		{
			valid=true;
		}

	}
	diceNumber=dicevalue;

	pOut->ClearStatusBar();

}

void InputDiceValueAction::Execute()
{
	ReadActionParameters();
	if(valid ==true)
	{
		
		Grid* pGrid = pManager->GetGrid();
		Input* pIn = pGrid->GetInput();
		Output* pOut = pGrid->GetOutput();
		///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

		// == Here are some guideline steps (numbered below) to implement this function ==

		// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action

		if(pGrid->GetEndGame()==true)
		{
			Player *pwin;
			pwin=pGrid->GetCurrentPlayer();



			int playernum;
			playernum=pwin->GetPlayerNum();

			string stringnum=to_string(playernum);

			string msg="Player" +stringnum +" has won";
			pOut->PrintMessage(msg);
		}

		else
		{
			// -- If not ended, do the following --:


			// 1- Get the "current" player from pGrid

			Player* currentPlayer;
			currentPlayer=pGrid->GetCurrentPlayer();

			//check if the player is going to win 

			Cell * currentcell;
			currentcell=currentPlayer->GetCell();
			CellPosition currentposition;
			currentposition =currentcell->GetCellPosition();
			int cellnum;
			cellnum=currentposition.GetCellNum();

			//make the player win if rolled value >the last cells
			int cond=99-cellnum;
			if(cond<=6)
			{
				if(diceNumber>cond)
				{
					diceNumber=cond;
				}
			}

			// 4- Move the currentPlayer using function Move of class player

			currentPlayer->Move(pGrid,diceNumber);

			// 5- Advance the current player number of pGrid

			pGrid->AdvanceCurrentPlayer();

		}
		// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
	}
}

InputDiceValueAction::~InputDiceValueAction(void)
{
}

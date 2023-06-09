#include "InputDiceValueAction.h"
#include "Grid.h"
#include "Player.h"



InputDiceValueAction::InputDiceValueAction(ApplicationManager *ProjectApp)  : Action(ProjectApp)
{

}

void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = ProjectManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	Valid=false;
	int Dicevalue=0;
	while (Valid==false)
	{

		pOut->PrintMessage("enter Dice value from 1 to 6");
		Dicevalue=pIn->GetInteger(pOut);

		if(Dicevalue<=0 || Dicevalue>6)
		{
			pGrid->PrintErrorMessage("InValid value, please click to Re-Enter");
		}
		else
		{
			Valid=true;
		}

	}
	DiceNumber=Dicevalue;

	pOut->ClearStatusBar();

}

void InputDiceValueAction::Execute()
{
	ReadActionParameters();
	if(Valid ==true)
	{
		
		Grid* pGrid = ProjectManager->GetGrid();
		Input* pIn = pGrid->GetInput();
		Output* pOut = pGrid->GetOutput();
		///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

		// == Here are some guideline steps (numbered below) to implement this function ==

		// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action

		if(pGrid->GetEndGame()==true)
		{
			Player *pwin;
			pwin=pGrid->GetCurrentPlayer();



			int Playernum;
			Playernum=pwin->GetPlayerNum();

			string stringnum=to_string(Playernum);

			string msg="Player" +stringnum +" has won";
			pOut->PrintMessage(msg);
		}

		else
		{
			// -- If not ended, do the following --:


			// 1- Get the "Current" Player from pGrid

			Player* CurrentPlayer;
			CurrentPlayer=pGrid->GetCurrentPlayer();

			//Check if the Player is going to win 

			Cell * CurrentCell;
			CurrentCell=CurrentPlayer->GetCell();
			CellPosition CurrentPosition;
			CurrentPosition =CurrentCell->GetCellPosition();
			int Cellnum;
			Cellnum=CurrentPosition.GetCellNum();

			//make the Player win if rolled value >the last Cells
			int cond=99-Cellnum;
			if(cond<=6)
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
}

InputDiceValueAction::~InputDiceValueAction(void)
{
}

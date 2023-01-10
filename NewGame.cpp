#include "NewGame.h"

#include "Output.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include"Cell.h"
#include"Player.h"

NewGame::NewGame(ApplicationManager *pApp)  : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void NewGame::ReadActionParameters()
{
	// no papameters needed from the user
}


void NewGame::Execute()
{
	    Grid* pGrid = pManager->GetGrid();
		Output* pOut = pGrid->GetOutput();


		Player* current;
		//set the turn back to zero
		pGrid->setplayernum(0);
		//setting the intial parameters of the players
		CellPosition pos(8,0);
		int wallet=100;
		int turn =0;
		//to loop for the four players
		for(int i=0;i<4;i++)
		{
			current=pGrid->GetCurrentPlayer();

			current->SetWallet(wallet);
			pGrid->UpdatePlayerCell(current,pos);
			current->SetTurnCount(turn);

			pGrid->AdvanceCurrentPlayer();
		}
		//set the turn back to zero
		pGrid->setplayernum(0);
		pGrid->SetEndGame(false);

		//setting the owners
		CardNine::setC9Owner(NULL);
		CardTen::setC10Owner(NULL);
		CardEleven::setC11Owner(NULL);

		pOut->ClearStatusBar();
}

NewGame::~NewGame(void)
{
}

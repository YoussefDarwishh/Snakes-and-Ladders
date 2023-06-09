#include "NewGame.h"

#include "Output.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include"Cell.h"
#include"Player.h"

NewGame::NewGame(ApplicationManager *ProjectApp)  : Action(ProjectApp)
{
	// Initializes the ProjectManager pointer of Action with the passed pointer
}


void NewGame::ReadActionParameters()
{
	// no papameters needed from the user
}


void NewGame::Execute()
{
	    Grid* pGrid = ProjectManager->GetGrid();
		Output* pOut = pGrid->GetOutput();


		Player* Current;
		//set the Turn back to zero
		pGrid->setPlayernum(0);
		//setting the intial parameters of the Players
		CellPosition Position(8,0);
		int Wallet=100;
		int Turn =0;
		//to loop for the four Players
		for(int i=0;i<4;i++)
		{
			Current=pGrid->GetCurrentPlayer();

			Current->SetWallet(Wallet);
			pGrid->UpdatePlayerCell(Current,Position);
			Current->SetTurnCount(Turn);

			pGrid->AdvanceCurrentPlayer();
		}
		//set the Turn back to zero
		pGrid->setPlayernum(0);
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

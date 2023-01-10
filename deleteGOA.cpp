#include"deleteGOA.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
deleteGOA::deleteGOA(ApplicationManager *pApp):Action(pApp) 
{
	Delete=0;
}

void deleteGOA::ReadActionParameters()
{
     Grid * pGrid = pManager->GetGrid();	
	Input *pIn = pGrid->GetInput();
	Output *pOut = pGrid ->GetOutput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("You are trying to delte a game object to delete select its start to deltet by double click.  ");
	
	if ( pGrid->checkIfIncludeGameObj(pIn->GetCellClicked())!=NULL )
	{
	
	Delete=1;
	}
	else
	{
	Delete=0;
	pOut->PrintMessage("This cell has no game object or you didnt clicked in cell contain start of the the object.");
	}
}
 
void deleteGOA:: Execute()
{
	ReadActionParameters();
	if (Delete==1)
	{
	Grid * pGrid = pManager->GetGrid();
	Output *pOut = pGrid ->GetOutput();
	Input *pIn = pGrid->GetInput();
	pOut->PrintMessage("click at the same cell agin to delete");
;	CellPosition cellpos= pIn->GetCellClicked();
	pGrid->RemoveObjectFromCell(cellpos);
	pOut->ClearStatusBar();
	}
}
deleteGOA::~deleteGOA()
 {
 }
#include"deleteGOA.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
deleteGOA::deleteGOA(ApplicationManager *ProjectApp):Action(ProjectApp) 
{
	Delete=0;
}

void deleteGOA::ReadActionParameters()
{
     Grid * pGrid = ProjectManager->GetGrid();	
	Input *pIn = pGrid->GetInput();
	Output *pOut = pGrid ->GetOutput();

	// 2- Read the "CardNumber" parameter and set its data member
	pOut->PrintMessage("You are trying to delte a game object to delete select its start to deltet by double click.  ");
	
	if ( pGrid->CheckIfIncludeGameObj(pIn->GetCellClicked())!=NULL )
	{
	
	Delete=1;
	}
	else
	{
	Delete=0;
	pOut->PrintMessage("This Cell has no game object or you didnt clicked in Cell contain start of the the object.");
	}
}
 
void deleteGOA:: Execute()
{
	ReadActionParameters();
	if (Delete==1)
	{
	Grid * pGrid = ProjectManager->GetGrid();
	Output *pOut = pGrid ->GetOutput();
	Input *pIn = pGrid->GetInput();
	pOut->PrintMessage("click at the same Cell agin to delete");
;	CellPosition CellPosition= pIn->GetCellClicked();
	pGrid->RemoveObjectFromCell(CellPosition);
	pOut->ClearStatusBar();
	}
}
deleteGOA::~deleteGOA()
 {
 }
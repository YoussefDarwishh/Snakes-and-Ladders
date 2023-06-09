#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *ProjectApp) : Action(ProjectApp)
{
	// Initializes the ProjectManager pointer of Action with the passed pointer
	Valid = true;
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = ProjectManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the StartPosition parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	StartPosition = pIn->GetCellClicked();

	// Read the EndPosition parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	EndPosition = pIn->GetCellClicked();

    

	///TODO: Make the needed Validations on the read parameters

	if(EndPosition.VCell()>StartPosition.VCell())
	{
		pGrid->PrintErrorMessage("end Cell cannot be smaller than start Cell");
		Valid=false;
	}

	if (StartPosition.VCell()==8 && StartPosition.HCell() == 0)
	{	
		pGrid->PrintErrorMessage("start Cell cannot be Cell num 1");
		Valid=false;
	}

	if (EndPosition.VCell()==0 && EndPosition.HCell() == 10)
	{	
		pGrid->PrintErrorMessage("end Cell cannot be Cell num 99");
		Valid=false;
	}

	if(StartPosition.HCell()!=EndPosition.HCell())
	{
		pGrid->PrintErrorMessage("end Cell and start Cell are not in the same column");
		Valid=false;
	}

	if(StartPosition.VCell()==0)
	{
		pGrid->PrintErrorMessage("start Cell can not be in the last column");
		Valid=false;
	}
	
	if(pGrid->EndofLadderandSnake(EndPosition)==true)
	{
		pGrid->PrintErrorMessage("end Cell cannot be a start of another ladder or snake");
		Valid=false;
	}

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
		ReadActionParameters();
	if(Valid==true)
	{

	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(StartPosition, EndPosition);

	Grid * pGrid = ProjectManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the Card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			//added=false;
	}
		if(pGrid->isoverlapping(pLadder)==true)
	{
		pGrid->PrintErrorMessage("Error:ladder is over lapping");
		pGrid->RemoveObjectFromCell(StartPosition);
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}

}
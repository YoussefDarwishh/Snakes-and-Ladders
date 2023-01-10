#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	valid = true;
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

    

	///TODO: Make the needed validations on the read parameters

	if(endPos.VCell()>startPos.VCell())
	{
		pGrid->PrintErrorMessage("end cell cannot be smaller than start cell");
		valid=false;
	}

	if (startPos.VCell()==8 && startPos.HCell() == 0)
	{	
		pGrid->PrintErrorMessage("start cell cannot be cell num 1");
		valid=false;
	}

	if (endPos.VCell()==0 && endPos.HCell() == 10)
	{	
		pGrid->PrintErrorMessage("end cell cannot be cell num 99");
		valid=false;
	}

	if(startPos.HCell()!=endPos.HCell())
	{
		pGrid->PrintErrorMessage("end cell and start cell are not in the same column");
		valid=false;
	}

	if(startPos.VCell()==0)
	{
		pGrid->PrintErrorMessage("start cell can not be in the last column");
		valid=false;
	}
	
	if(pGrid->EndofLadderandSnake(endPos)==true)
	{
		pGrid->PrintErrorMessage("end cell cannot be a start of another ladder or snake");
		valid=false;
	}

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
		ReadActionParameters();
	if(valid==true)
	{

	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
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
		pGrid->RemoveObjectFromCell(startPos);
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}

}
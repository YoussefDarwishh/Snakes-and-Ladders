#include "CutCard.h"
#include"Card.h"
#include "Output.h"
#include"CellPosition.h"
#include"Cell.h"


CutCard::CutCard(ApplicationManager *ProjectApp): Action(ProjectApp)
{
	// Initializes the ProjectManager pointer of Action with the passed pointer
	Valid = true;

}

void CutCard::ReadActionParameters()
{
	Grid*pGrid = ProjectManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//Reads CellPosition
	pOut->PrintMessage("Click on the soruce Cell");
	Position=pIn->GetCellClicked();

	//the needed Validations on the read parameters
	if(!(pGrid->CellHasCard(Position)))
	{
		pOut->PrintMessage("Cell does not have a Card");
		pIn->GetCellClicked();
		Valid =false;
	}

	// Clear messages
	pOut->ClearStatusBar();
}

void CutCard::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members

	ReadActionParameters();
	if(Valid==true)

	{

		Grid*pGrid= ProjectManager->GetGrid();

		//get the Card from the Cell
		pCard= dynamic_cast<Card *>(pGrid->GetCard(Position));
		
        pGrid->SetClipboard(pCard);
		pGrid->RemoveObjectFromCell(Position);

        pGrid->PrintErrorMessage("copied");      //test
		
	}
}

CutCard::~CutCard()
{

}
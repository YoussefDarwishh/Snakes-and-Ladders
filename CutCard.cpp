#include "CutCard.h"
#include"Card.h"
#include "Output.h"
#include"CellPosition.h"
#include"Cell.h"


CutCard::CutCard(ApplicationManager *pApp): Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	valid = true;

}

void CutCard::ReadActionParameters()
{
	Grid*pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//Reads cellposition
	pOut->PrintMessage("Click on the soruce cell");
	pos=pIn->GetCellClicked();

	//the needed validations on the read parameters
	if(!(pGrid->cellHasCard(pos)))
	{
		pOut->PrintMessage("cell does not have a card");
		pIn->GetCellClicked();
		valid =false;
	}

	// Clear messages
	pOut->ClearStatusBar();
}

void CutCard::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members

	ReadActionParameters();
	if(valid==true)

	{

		Grid*pGrid= pManager->GetGrid();

		//get the card from the cell
		pCard= dynamic_cast<Card *>(pGrid->Getcard(pos));
		
        pGrid->SetClipboard(pCard);
		pGrid->RemoveObjectFromCell(pos);

        pGrid->PrintErrorMessage("copied");      //test
		
	}
}

CutCard::~CutCard()
{

}
#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"

AddCardAction::AddCardAction(ApplicationManager *ProjectApp) : Action(ProjectApp)
{
	// Initializes the ProjectManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters() 
{	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid * pGrid = ProjectManager->GetGrid();
	Input *pIn = pGrid->GetInput();
	Output *pOut = pGrid ->GetOutput();

	// 2- Read the "CardNumber" parameter and set its data member
	pOut->PrintMessage("You are trying to add a Card.  Please Enter the Card number (1-12):");
	CardNumber = pIn->GetInteger(pOut);
	if (CardNumber<1 || CardNumber>12)
	{
		pOut->PrintMessage("Error! InValid Card number, click to continue");
		pIn->GetCellClicked();
	}
	else
	{
	// 3- Read the "CardPosition" parameter (its Cell Position) and set its data member
	pOut->PrintMessage("Click the Cell to add the Card number");
	CardPosition = pIn->GetCellClicked();

	// 4- Make the needed Validations on the read parameters
	if (CellPosition::GetCellNumFromPosition(CardPosition) == 1 || CellPosition::GetCellNumFromPosition(CardPosition) == 99) //Checking if user clicked on Cell 1 or 99
	{
		CheckPosition = false;
	}
	else
		CheckPosition = true;

	// 5- Clear status bar
	pOut->ClearStatusBar();
}
}

void AddCardAction::Execute() 
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
		Grid * pGrid = ProjectManager->GetGrid();
	Input *pIn = pGrid->GetInput();
	Output *pOut = pGrid ->GetOutput();

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	if (CheckPosition == false)
	{
		ProjectManager ->GetGrid()->PrintErrorMessage("Error! Card cannot be added, click to continue");
		pIn->GetCellClicked();
	}
	else
	{
	// 2- Switch case on CardNumber data member and create the appropriate Card object type
	Card * pCard = NULL; // will point to the Card object type
	switch (CardNumber)
	{
	case 1:
		pCard = new CardOne(CardPosition);
		break;
		// A- Add the remaining cases
	case 2:
		pCard = new CardTwo(CardPosition);
		break;
	case 3:
		pCard = new CardThree(CardPosition);
		break;

	case 4:
		pCard = new CardFour(CardPosition);
		break;

	case 5:
		pCard = new CardFive(CardPosition);
		break;

	case 6:
		pCard = new CardSix(CardPosition);
		break;

	case 7:
		pCard = new CardSeven(CardPosition);
		break;

	case 8:
		pCard = new CardEight(CardPosition);
		break;

	case 9:
		pCard = new CardNine(CardPosition);
		break;
	case 10:
		pCard = new CardTen(CardPosition);
		break;
	case 11:
		pCard = new CardEleven(CardPosition);
		break;
	case 12:
		pCard = new CardTwelve(CardPosition);
		break;
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = ProjectManager->GetGrid();
		// B- Make the "pCard" reads its Card parameters: ReadCardParameters(), It is virtual and depends on the Card type
		pCard->ReadCardParameters(pGrid);
		// C- Add the Card object to the GameObject of its Cell:
		bool Checkitbeadded = pGrid->AddObjectToCell(pCard);
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		if (Checkitbeadded==false)
		{
				pGrid->PrintErrorMessage("Error! Card cannot be added, click to continue");
				pIn->GetCellClicked();
		}
	// Here, the Card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

	}
}
}
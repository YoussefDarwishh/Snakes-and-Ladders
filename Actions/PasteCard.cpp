#include "PasteCard.h"
#include"Card.h"
#include "Output.h"
#include"CellPosition.h"
#include"Cell.h"
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


PasteCard::PasteCard(ApplicationManager *ProjectApp) : Action(ProjectApp)
{
	// Initializes the ProjectManager pointer of Action with the passed pointer
	Valid = true;

}

void PasteCard::ReadActionParameters()
{
	Grid*pGrid = ProjectManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//Reads CellPosition
	pOut->PrintMessage("Click on the destination Cell");
	CardPosition=pIn->GetCellClicked();

	//the needed Validations on the read parameters
	if(pGrid->CellHasCard(CardPosition)==true)
	{
		pGrid->PrintErrorMessage("Cell  have a Card already");
		Valid =false;
	}

	//Checkinf if copy worked
	if(pGrid->GetClipboard()==NULL)
	{
		pGrid->PrintErrorMessage("clipboard is empty");
		Valid =false;
	}

	//Cannot add Card in the first Cell
	if(CardPosition.HCell()==0 && CardPosition.VCell()==8)
	{
		pGrid->PrintErrorMessage("Cannot add Card in the first Cell");
		Valid =false;
	}

	//Cannot add Card in the last Cell
	if(CardPosition.HCell()==10 && CardPosition.VCell()==0)
	{
		pGrid->PrintErrorMessage("Cannot add Card in the last Cell");
		Valid =false;
	}

	//Card Cell cannot be a start of another ladder or snake
	if(pGrid->EndofLadderandSnake(CardPosition)==true)
	{
		pGrid->PrintErrorMessage("Card Cell cannot be a start of another ladder or snake");
		Valid=false;
	}

	// Clear messages
	pOut->ClearStatusBar();
}

void PasteCard::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members

	ReadActionParameters();
	if(Valid==true)
	{
		Grid*pGrid = ProjectManager->GetGrid();
		Input*pIn = pGrid->GetInput();
		Output*pOut = pGrid -> GetOutput();

		//get the copied and get the Card number
		PastedCard = pGrid->GetClipboard();
		int CardNumber=PastedCard->GetCardNumber();

		// will point to the Card whose has no parameters or static parameters to object type
		Card*noparameters=NULL;

		//same as add Card
		switch (CardNumber)
		{
		case 1:
			{
				//make pointer to Card
				CardOne*pCard = new CardOne(CardPosition);
				//down casting from Card to Card one
				CardOne*a = (CardOne*)PastedCard;
				//set parameters of the Card
				pCard->setWallet(a->getWallet());
				pCard->SetPosition(CardPosition);

				if(pCard!=NULL)
				{
					pOut->PrintMessage("Pasted");
					pGrid->AddObjectToCell(pCard);
				}
			}
			break;
			// A- Add the remaining cases
		case 2:
			noparameters = new CardTwo(CardPosition);
			break;
		case 3:
			noparameters = new CardThree(CardPosition);
			break;

		case 4:
			noparameters = new CardFour(CardPosition);
			break;
		case 5:
			noparameters = new CardFive(CardPosition);
		case 6:
			{
				//make pointer to Card
				CardSix*pCard = new CardSix(CardPosition);
				//down casting from Card to Card one
				CardSix*a = (CardSix*)PastedCard;
				//set parameters of the Card
				pCard->setInstructed(a->getInstructed());
				pCard->SetPosition(CardPosition);

				if(pCard!=NULL)
				{
					pOut->PrintMessage("Pasted");
					pGrid->AddObjectToCell(pCard);
				}
			}
			break;

		case 7:
			noparameters = new CardSeven(CardPosition);
			break;

		case 8:
			{
				//make pointer to Card
				CardEight*pCard = new CardEight(CardPosition);
				//down casting from Card to Card one
				CardEight*a = (CardEight*)PastedCard;
				//set parameters of the Card
				pCard->setfee(a->getfee());
				pCard->SetPosition(CardPosition);

				if(pCard!=NULL)
				{
					pOut->PrintMessage("Pasted");
					pGrid->AddObjectToCell(pCard);
				}
			}

		case 9:
			noparameters = new CardNine(CardPosition);
			break;

		case 10:
			noparameters = new CardTen(CardPosition);
			break;

		case 11:
			noparameters = new CardEleven(CardPosition);
			break;

		case 12:
			noparameters = new CardTwelve(CardPosition);
			break;
		}
	
		if(noparameters!=NULL)
		{
			//set the new Position of the Pasted Card
			noparameters->SetPosition(CardPosition);	
			pOut->PrintMessage("Pasted");
			pGrid->AddObjectToCell(noparameters);
		}
	}


}

PasteCard::~PasteCard(void)
{
}
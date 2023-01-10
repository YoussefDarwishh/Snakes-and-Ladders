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


PasteCard::PasteCard(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	valid = true;

}

void PasteCard::ReadActionParameters()
{
	Grid*pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//Reads cellposition
	pOut->PrintMessage("Click on the destination cell");
	cardPosition=pIn->GetCellClicked();

	//the needed validations on the read parameters
	if(pGrid->cellHasCard(cardPosition)==true)
	{
		pGrid->PrintErrorMessage("cell  have a card already");
		valid =false;
	}

	//checkinf if copy worked
	if(pGrid->GetClipboard()==NULL)
	{
		pGrid->PrintErrorMessage("clipboard is empty");
		valid =false;
	}

	//Cannot add card in the first cell
	if(cardPosition.HCell()==0 && cardPosition.VCell()==8)
	{
		pGrid->PrintErrorMessage("Cannot add card in the first cell");
		valid =false;
	}

	//Cannot add card in the last cell
	if(cardPosition.HCell()==10 && cardPosition.VCell()==0)
	{
		pGrid->PrintErrorMessage("Cannot add card in the last cell");
		valid =false;
	}

	//card cell cannot be a start of another ladder or snake
	if(pGrid->EndofLadderandSnake(cardPosition)==true)
	{
		pGrid->PrintErrorMessage("card cell cannot be a start of another ladder or snake");
		valid=false;
	}

	// Clear messages
	pOut->ClearStatusBar();
}

void PasteCard::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members

	ReadActionParameters();
	if(valid==true)
	{
		Grid*pGrid = pManager->GetGrid();
		Input*pIn = pGrid->GetInput();
		Output*pOut = pGrid -> GetOutput();

		//get the copied and get the card number
		pastedCard = pGrid->GetClipboard();
		int cardNumber=pastedCard->GetCardNumber();

		// will point to the card whose has no parameters or static parameters to object type
		Card*noparameters=NULL;

		//same as add card
		switch (cardNumber)
		{
		case 1:
			{
				//make pointer to card
				CardOne*pCard = new CardOne(cardPosition);
				//down casting from card to card one
				CardOne*a = (CardOne*)pastedCard;
				//set parameters of the card
				pCard->setwallet(a->getwallet());
				pCard->SetPosition(cardPosition);

				if(pCard!=NULL)
				{
					pOut->PrintMessage("pasted");
					pGrid->AddObjectToCell(pCard);
				}
			}
			break;
			// A- Add the remaining cases
		case 2:
			noparameters = new CardTwo(cardPosition);
			break;
		case 3:
			noparameters = new CardThree(cardPosition);
			break;

		case 4:
			noparameters = new CardFour(cardPosition);
			break;
		case 5:
			noparameters = new CardFive(cardPosition);
		case 6:
			{
				//make pointer to card
				CardSix*pCard = new CardSix(cardPosition);
				//down casting from card to card one
				CardSix*a = (CardSix*)pastedCard;
				//set parameters of the card
				pCard->setInstructed(a->getInstructed());
				pCard->SetPosition(cardPosition);

				if(pCard!=NULL)
				{
					pOut->PrintMessage("pasted");
					pGrid->AddObjectToCell(pCard);
				}
			}
			break;

		case 7:
			noparameters = new CardSeven(cardPosition);
			break;

		case 8:
			{
				//make pointer to card
				CardEight*pCard = new CardEight(cardPosition);
				//down casting from card to card one
				CardEight*a = (CardEight*)pastedCard;
				//set parameters of the card
				pCard->setfee(a->getfee());
				pCard->SetPosition(cardPosition);

				if(pCard!=NULL)
				{
					pOut->PrintMessage("pasted");
					pGrid->AddObjectToCell(pCard);
				}
			}

		case 9:
			noparameters = new CardNine(cardPosition);
			break;

		case 10:
			noparameters = new CardTen(cardPosition);
			break;

		case 11:
			noparameters = new CardEleven(cardPosition);
			break;

		case 12:
			noparameters = new CardTwelve(cardPosition);
			break;
		}
	
		if(noparameters!=NULL)
		{
			//set the new pos of the pasted card
			noparameters->SetPosition(cardPosition);	
			pOut->PrintMessage("pasted");
			pGrid->AddObjectToCell(noparameters);
		}
	}


}

PasteCard::~PasteCard(void)
{
}
#include "Grid.h"
#include "Snake.h"
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate Cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate Cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first Cell
		PlayerList[i]->Draw(pOut); // initially draw Players in the first Cell
	}

	// Initialize currPlayerNumber with 0 (first Player)
	currPlayerNumber = 0; // start with the first Player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any Validation is needed
{
	// Get the Cell Position of pNewObject
	CellPosition Position = pNewObject->GetPosition();
	if (Position.IsValidCell()) // Check if Valid Position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[Position.VCell()][Position.HCell()]->GetGameObject();
		if( pPrevObject)  // the Cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[Position.VCell()][Position.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a Valid Position
}

// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition & Position)
{
	if (Position.IsValidCell()) // Check if Valid Position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[Position.VCell()][Position.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * Player, const CellPosition & newPosition)
{
	// Clear the Player's circle from the old Cell Position
	Player->ClearDrawing(pOut);

	// Set the Player's CELL with the new Position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	Player->SetCell(newCell);	

	// Draw the Player's circle on the new Cell Position
	Player->Draw(pOut);
}


// ========= Setters and Getters Functions =========

void Grid::SetCurrPlayerNumber(int num)
{
	if (num >= 0 && num < 4)
		currPlayerNumber = num;

}

Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & Position)
{
	
	int startH = Position.HCell(); // represents the start hCell in the Current row to search for the ladder in
	for (int i = Position.VCell(); i >= 0; i--) // searching from Position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
			{
				return CellList[i][j]->HasLadder(); //de bt return 3la tool msh lazem n3ml variables w kda
			}

		}
		startH = 0; // because in the next above rows, we will search from the first left Cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw Cells with or without Cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other Cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw Players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string PlayersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(PlayersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last Player
				PlayersInfo += ", ";
		}
		PlayersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(PlayersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing Players in Play Mode
		//       so we do NOT need draw all Players again in UpdateInterface() of the Play mode
		// In addition, Cards/snakes/ladders do NOT change Positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::SaveAll(ofstream &of ,int a)
{
		for (int i = NumVerticalCells-1; i >= 0 ; i--) 
		{
			for (int j = 0; j < NumHorizontalCells; j++) 
			{
				if (CellList[i][j]->GetGameObject() != NULL)
				(CellList[i][j]->GetGameObject())->Save(of,a);
			}
		}
}

GameObject* Grid::CheckIfIncludeGameObj( CellPosition  Position)
{
	if (CellList[Position.VCell()][Position.HCell()]->HasLadder()!=NULL  || CellList[Position.VCell()][Position.HCell()]->HasSnake()!=NULL || CellList[Position.VCell()][Position.HCell()]->HasCard()!=NULL) 
	{
		return CellList[Position.VCell()][Position.HCell()]->GetGameObject();
	}
	else return NULL;
}

int Grid :: GetLadderNum()
{
	LadderNum = 0;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
		{
			for (int j = 0; j < NumHorizontalCells; j++) 
			{
				if (dynamic_cast < Ladder * >(CellList[i][j]->GetGameObject()) != NULL ) //Checking in every Cell if there's an object that we're looking for by dynamic casr
					LadderNum++;
			}
	}
	return LadderNum;
}

int Grid :: GetSnakeNum() //counts number of snake objects by dynamic cast
{
	SnakeNum = 0;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
		{
			for (int j = 0; j < NumHorizontalCells; j++) 
			{
				if (dynamic_cast < Snake * >(CellList[i][j]->GetGameObject()) != NULL ) // Checking in every Cell if there's an object that we're looking for by dynamic cast
					SnakeNum++;
			}
	}
	return SnakeNum;
}

int Grid :: GetCardsNum() //counts number of Cards objects by dynamic cast
{
	CardNum = 0;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
		{
			for (int j = 0; j < NumHorizontalCells; j++) 
			{
				if (dynamic_cast < Card * >(CellList[i][j]->GetGameObject()) != NULL ) // Checking in every Cell if there's an object that we're looking for by dynamic cast
					CardNum++;
			}
	}
	return CardNum;
}

bool Grid::isoverlapping(GameObject*a)
{
	bool Check = false;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		
		GameObject*p= CellList[i][a->GetPosition().HCell()]->GetGameObject();

			if(p!=NULL)
			{	
				Check=p->isoverlapping(a);
			}
			if(Check==true)
				break;	
	}

	return Check;

}

bool Grid::EndofLadderandSnake(CellPosition EndPositionition)
{
	if(CellList[EndPositionition.VCell()][EndPositionition.HCell()]->HasLadder()!=NULL  ||CellList[EndPositionition.VCell()][EndPositionition.HCell()]->HasSnake()!=NULL)
	{
		return true;
	}
	return false;
}

void Grid::setPlayernum(int num)
{
currPlayerNumber=num;
}


bool Grid::CellHasCard(CellPosition Position)
{
	if(CellList[Position.VCell()][Position.HCell()]->HasCard()!=NULL)
   {
      return true;
   }
	return false;
}

GameObject* Grid::GetCard(CellPosition Position)
{
		return CellList[Position.VCell()][Position.HCell()]->GetGameObject();
}

Player* Grid :: GetPlayerLeastMoney()
{ //made by youssef
	//i need this for Card 12
	Player*p = NULL;
	for (int i=0; i<3; i++)
	{
		if (i == 0)
			p = p->CompareforMinimum(PlayerList[i], PlayerList[i+1]); //just comapres two Players and returns the one with least money
		else
			p = p->CompareforMinimum(p,PlayerList[i]);
	}
	return p;
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}

Player* Grid::GetNextPlayer(Player* pPlayer)
{
	int numberOfPlayer = currPlayerNumber;   // get cuurent Player number
	int Stepcount = pPlayer->GetStepCount();  // to get step count to know who is infront of me
	int MinimumDiffrence=100;                     // Minimum diffrence between step count
	int count = 0;                           // counting Player infront of you
	int PlayerNumberToBeBack;                  // to know Player back to start Cell 
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		//Checking if there is a Card infront of you
		if ( ((PlayerList[i]->GetStepCount()) > Stepcount) ) 
		{count++;
		if ( (PlayerList[i]->GetStepCount()-Stepcount)< MinimumDiffrence )
		{
		MinimumDiffrence=PlayerList[i]->GetStepCount()-Stepcount;
		PlayerNumberToBeBack=i;
		}
		
		}
		    
	}
	if (count == 0)
		return NULL;
	else
	return PlayerList[PlayerNumberToBeBack];
}
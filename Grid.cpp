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
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
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

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
			{
				return CellList[i][j]->HasLadder(); //de bt return 3la tool msh lazem n3ml variables w kda
			}

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
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

GameObject* Grid::checkIfIncludeGameObj( CellPosition  pos)
{
	if (CellList[pos.VCell()][pos.HCell()]->HasLadder()!=NULL  || CellList[pos.VCell()][pos.HCell()]->HasSnake()!=NULL || CellList[pos.VCell()][pos.HCell()]->HasCard()!=NULL) 
	{
		return CellList[pos.VCell()][pos.HCell()]->GetGameObject();
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
				if (dynamic_cast < Ladder * >(CellList[i][j]->GetGameObject()) != NULL ) //checking in every cell if there's an object that we're looking for by dynamic casr
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
				if (dynamic_cast < Snake * >(CellList[i][j]->GetGameObject()) != NULL ) // checking in every cell if there's an object that we're looking for by dynamic cast
					SnakeNum++;
			}
	}
	return SnakeNum;
}

int Grid :: GetCardsNum() //counts number of cards objects by dynamic cast
{
	CardNum = 0;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
		{
			for (int j = 0; j < NumHorizontalCells; j++) 
			{
				if (dynamic_cast < Card * >(CellList[i][j]->GetGameObject()) != NULL ) // checking in every cell if there's an object that we're looking for by dynamic cast
					CardNum++;
			}
	}
	return CardNum;
}

bool Grid::isoverlapping(GameObject*a)
{
	bool check = false;
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		
		GameObject*p= CellList[i][a->GetPosition().HCell()]->GetGameObject();

			if(p!=NULL)
			{	
				check=p->isoverlapping(a);
			}
			if(check==true)
				break;	
	}

	return check;

}

bool Grid::EndofLadderandSnake(CellPosition endposition)
{
	if(CellList[endposition.VCell()][endposition.HCell()]->HasLadder()!=NULL  ||CellList[endposition.VCell()][endposition.HCell()]->HasSnake()!=NULL)
	{
		return true;
	}
	return false;
}

void Grid::setplayernum(int num)
{
currPlayerNumber=num;
}


bool Grid::cellHasCard(CellPosition pos)
{
	if(CellList[pos.VCell()][pos.HCell()]->HasCard()!=NULL)
   {
      return true;
   }
	return false;
}

GameObject* Grid::Getcard(CellPosition pos)
{
		return CellList[pos.VCell()][pos.HCell()]->GetGameObject();
}

Player* Grid :: GetPlayerLeastMoney()
{ //made by youssef
	//i need this for card 12
	Player*p = NULL;
	for (int i=0; i<3; i++)
	{
		if (i == 0)
			p = p->compareformin(PlayerList[i], PlayerList[i+1]); //just comapres two players and returns the one with least money
		else
			p = p->compareformin(p,PlayerList[i]);
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
	int numberOfPlayer = currPlayerNumber;   // get cuurent player number
	int Stepcount = pPlayer->GetStepCount();  // to get step count to know who is infront of me
	int minDiffrence=100;                     // min diffrence between step count
	int count = 0;                           // counting player infront of you
	int playerNumberToBeBack;                  // to know player back to start cell 
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		//checking if there is a card infront of you
		if ( ((PlayerList[i]->GetStepCount()) > Stepcount) ) 
		{count++;
		if ( (PlayerList[i]->GetStepCount()-Stepcount)< minDiffrence )
		{
		minDiffrence=PlayerList[i]->GetStepCount()-Stepcount;
		playerNumberToBeBack=i;
		}
		
		}
		    
	}
	if (count == 0)
		return NULL;
	else
	return PlayerList[playerNumberToBeBack];
}
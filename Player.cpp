#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	checkCardFourNotExist = true;
	checkCardEightNotExist=3;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::setTurnCount(int turn)
{
	turnCount = turn;
}

int Player::GetjustRolledDiceNum()const
{
	return justRolledDiceNum;
}

CellPosition Player :: GetCurrentPosition()
{
	return pCell->GetCellPosition();
}

// ====== Drawing Functions ====== //

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	CellPosition x;
	x = pCell->GetCellPosition();
	pOut->DrawPlayer(x,playerNum,playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	CellPosition x;
	x = pCell -> GetCellPosition();
	pOut->DrawPlayer(x,playerNum,cellColor);
}

void Player::SetTurnCount(int count)
{
	turnCount=count;
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{
	Output * pOut=pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// 3- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum=diceNumber;
	// == Here are some guideline steps (numbered below) to implement this function ==
	// if the player doenst have money he will stop for 3 turns
	if (wallet==0)
	{
		if (turnCount==2)
		{   
			pOut->PrintMessage("This is the recharge phase! You will not move,Click to Continue");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			wallet+=justRolledDiceNum*10;
			turnCount=0;
			return;
		}
		turnCount++;
		return;
	}

	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (checkCardFourNotExist==true && checkCardEightNotExist==3)
	{
		if (turnCount<2)
		{
			turnCount++;

		}
		else if (turnCount==2)
		{

			pOut->PrintMessage("This is the recharge phase! You will not move,Click to Continue");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			wallet+=justRolledDiceNum*10;
			turnCount=0;
			return;
		}




		// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
		//    Using the appropriate function of CellPosition class to update "pos"
		// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
		//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
		CellPosition currentPos; 
		CellPosition nextPos;
		Player* flag;
		flag=this;
		currentPos =pCell->GetCellPosition();
		int currentPosNum=currentPos.GetCellNum();
		if (wallet !=0)
		{stepCount=currentPosNum + justRolledDiceNum;
		nextPos=nextPos.GetCellPositionFromNum(stepCount);
		pGrid->UpdatePlayerCell(flag,nextPos);
		}

		// 6- Apply() the game object of the reached cell (if any)
		GameObject*gobj;
		gobj=pCell->GetGameObject();
		if (gobj!=NULL)
		{
			gobj->Apply(pGrid,flag);

		}

		// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
		/*CellPosition checkCurrentPos;
		checkCurrentPos=pCell->GetCellPosition();
		int f=checkCurrentPos.GetCellNum();*/
		if (stepCount>=99)
		{
			pGrid->SetEndGame(true);
		}
	}
	else if(checkCardFourNotExist ==false)
	{
		checkCardFourNotExist=true;
		if(turnCount==2)
		{
			pOut->PrintMessage("This is the recharge phase! You will not move,Click to Continue");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			wallet+=justRolledDiceNum*10;
			turnCount=0;
			return;

		}
	}

	else if(checkCardEightNotExist<3)
	{
		checkCardEightNotExist++;
		return;
	}
}

void Player:: setcheckCardEight(int x)
{
	if (x==1)
		checkCardEightNotExist=0;
	else 
		return;
}

Player* Player::compareformin(Player*p1,Player*p2)
{
	if (p1->GetWallet()<=p2->GetWallet())
		return p1;
	else
		return p2;
}

void Player::setcheckCardFour(bool f)
{
	checkCardFourNotExist=f;

}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

int Player::GetPlayerNum()
{
	return playerNum;
}

int Player::GetStepCount() const
{
	return stepCount;
}
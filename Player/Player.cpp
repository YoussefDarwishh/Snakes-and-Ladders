#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int PlayerNum) : stepCount(0), Wallet(100), PlayerNum(PlayerNum)
{
	this->pCell = pCell;
	this->TurnCount = 0;
	CheckCardFourNotExist = true;
	CheckCardEightNotExist=3;
	// Make all the needed initialization or Validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * Cell)
{
	pCell = Cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int Wallet)
{
	this->Wallet = Wallet;
	// Make any needed Validations
}

int Player::GetWallet() const
{
	return Wallet;
}

int Player::GetTurnCount() const
{
	return TurnCount;
}

void Player::setTurnCount(int Turn)
{
	TurnCount = Turn;
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
	color PlayerColor = UI.PlayerColors[PlayerNum];


	///TODO: use the appropriate output function to draw the Player with "PlayerColor"
	CellPosition x;
	x = pCell->GetCellPosition();
	pOut->DrawPlayer(x,PlayerNum,PlayerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color CellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the Player with "CellColor" (to clear it)
	CellPosition x;
	x = pCell -> GetCellPosition();
	pOut->DrawPlayer(x,PlayerNum,CellColor);
}

void Player::SetTurnCount(int count)
{
	TurnCount=count;
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int DiceNumber)
{
	Output * pOut=pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// 3- Set the justRolledDiceNum with the passed DiceNumber
	justRolledDiceNum=DiceNumber;
	// == Here are some guideline steps (numbered below) to implement this function ==
	// if the Player doenst have money he will stop for 3 Turns
	if (Wallet==0)
	{
		if (TurnCount==2)
		{   
			pOut->PrintMessage("This is the recharge phase! You will not move,Click to Continue");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			Wallet+=justRolledDiceNum*10;
			TurnCount=0;
			return;
		}
		TurnCount++;
		return;
	}

	// 1- Increment the TurnCount because calling Move() means that the Player has rolled the Dice once
	// 2- Check the TurnCount to know if the Wallet recharge Turn comes (recharge Wallet instead of move)
	//    If yes, recharge Wallet and reset the TurnCount and return from the function (do NOT move)
	if (CheckCardFourNotExist==true && CheckCardEightNotExist==3)
	{
		if (TurnCount<2)
		{
			TurnCount++;

		}
		else if (TurnCount==2)
		{

			pOut->PrintMessage("This is the recharge phase! You will not move,Click to Continue");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			Wallet+=justRolledDiceNum*10;
			TurnCount=0;
			return;
		}




		// 4- Get the Player Current Cell Position, say "Position", and add to it the DiceNumber (update the Position)
		//    Using the appropriate function of CellPosition class to update "Position"
		// 5- Use pGrid->UpdatePlayerCell() func to Update Player's Cell POINTER (pCell) with the Cell in the passed Position, "Position" (the updated one)
		//    the importance of this function is that it Updates the pCell pointer of the Player and Draws it in the new Position
		CellPosition CurrentPos; 
		CellPosition nextPos;
		Player* flag;
		flag=this;
		CurrentPos =pCell->GetCellPosition();
		int CurrentPosNum=CurrentPos.GetCellNum();
		if (Wallet !=0)
		{stepCount=CurrentPosNum + justRolledDiceNum;
		nextPos=nextPos.GetCellPositionFromNum(stepCount);
		pGrid->UpdatePlayerCell(flag,nextPos);
		}

		// 6- Apply() the game object of the reached Cell (if any)
		GameObject*gobj;
		gobj=pCell->GetGameObject();
		if (gobj!=NULL)
		{
			gobj->Apply(pGrid,flag);

		}

		// 7- Check if the Player reached the end Cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
		/*CellPosition CheckCurrentPos;
		CheckCurrentPos=pCell->GetCellPosition();
		int f=CheckCurrentPos.GetCellNum();*/
		if (stepCount>=99)
		{
			pGrid->SetEndGame(true);
		}
	}
	else if(CheckCardFourNotExist ==false)
	{
		CheckCardFourNotExist=true;
		if(TurnCount==2)
		{
			pOut->PrintMessage("This is the recharge phase! You will not move,Click to Continue");
			pIn->GetCellClicked();
			pOut->ClearStatusBar();
			Wallet+=justRolledDiceNum*10;
			TurnCount=0;
			return;

		}
	}

	else if(CheckCardEightNotExist<3)
	{
		CheckCardEightNotExist++;
		return;
	}
}

void Player:: setCheckCardEight(int x)
{
	if (x==1)
		CheckCardEightNotExist=0;
	else 
		return;
}

Player* Player::CompareforMinimum(Player*p1,Player*p2)
{
	if (p1->GetWallet()<=p2->GetWallet())
		return p1;
	else
		return p2;
}

void Player::setCheckCardFour(bool f)
{
	CheckCardFourNotExist=f;

}

void Player::AppendPlayerInfo(string & PlayersInfo) const
{
	PlayersInfo += "P" + to_string(PlayerNum) + "(" ;
	PlayersInfo += to_string(Wallet) + ", ";
	PlayersInfo += to_string(TurnCount) + ")";
}

int Player::GetPlayerNum()
{
	return PlayerNum;
}

int Player::GetStepCount() const
{
	return stepCount;
}
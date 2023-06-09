#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell * pCell;		   // pointer to the Current Cell of the Player

	const int PlayerNum;   // the Player number (from 0 to MaxPlayerCount-1)
	                       // Player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his CellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int Wallet;		       // Player's Wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the Current Dice number which is just rolled by the Player
	int TurnCount;         // a counter that starts with 0, is incremented with each Dice roll
	                       // and reset again when reached 3
	                       // it is used to indicate when to move and when to add to your Wallet
	bool CheckCardFourNotExist;     // Check if Card four occured or not
	int CheckCardEightNotExist;    // Check if Card Eight occured or not

public:

	Player(Cell * pCell, int PlayerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * Cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int Wallet);		// A setter for the Wallet
	int GetWallet() const;			// a getter for the Wallet

	int GetTurnCount() const;		// A getter for the TurnCount
	void setTurnCount(int Turn);
	///TODO: You can add setters and getters for data members here (if needed)
	CellPosition GetCurrentPosition();
	void SetTurnCount(int count);
	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its Current Cell
	int GetjustRolledDiceNum() const;
	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its Current Cell

	// ====== Game Functions ======

	void Move(Grid * pGrid, int DiceNumber);	// Moves the Player with the passed DiceNumber 
	                                            // and Applies the Game Object's effect (if any) of the end reached Cell 
	                                            // for example, if the end Cell contains a ladder, take it
	
	void AppendPlayerInfo(string & PlayersInfo) const; // Appends Player's info to the input string, 
	                                                   // for example: P0(Wallet, TurnCount)
	int GetPlayerNum();
	Player* CompareforMinimum(Player*,Player*);

	void setCheckCardEight(int x);

	void setCheckCardFour(bool);
	int GetStepCount() const;
};
#pragma once

#include "UI_Info.h"
#include "DEFS.h"

#include "Input.h"
#include "Output.h"
#include "CellPosition.h"

// forward declarations (the includes are in the cpp)
class Cell;
class GameObject;
class Ladder;
class Card;
class Player;

class Grid
{
	Output * pOut;   // A pointer to the Output object
	Input * pIn;     // A pointer to the Input object

	Cell * CellList[NumVerticalCells][NumHorizontalCells];  // An array of "Pointers" to All Cells of the Grid Cells
															// We make it array of pointers not objects because
															// there are NO default constructor for class Cell

	Player* PlayerList[MaxPlayerCount]; // An array of "Pointers" to the Players of the Game (MaxPlayerCount Players)
	int currPlayerNumber;   // The Player number that has the Turn to play 
							// currPlayerNumber is: from 0 to MaxPlayerCount - 1

	Card * Clipboard;	   // This is used in copy/cut/paste Card (should be set in copy/cut and got in paste)

	bool endGame;	       // A boolean indicating if the Game is ended or not (a Player reaches the end Cell of the grid or not)
	int LadderNum,SnakeNum,CardNum;

public:

	Grid(Input * pIn, Output * pOut);	  // Gives the Grid a Pointer to the Output Object and the Input Object
										  // and makes any needed initializations

	// ========= Adding or Removing GameObjects to Cells =========

	bool AddObjectToCell(GameObject * pNewObject);		 // Adds a GameObject to the Cell of its "Position" data member
	                                                     // only if the Cell does NOT already contain an object, 
	                                                     // otherwise return false and don't add

	void RemoveObjectFromCell(const CellPosition & Position); // Removes the GameObject of the Cell of the passed "Position"
	                                                     // Note: You may need to change the return type of this function (Think)

	void UpdatePlayerCell(Player * Player, const CellPosition & newPosition); // Update the Player's pCell with the CellList's Cell pointer of the "newPosition",
	                                                                          // Clears the Player's circle from the previous Cell
	    																	  // and  Draws it in the new Cell

	// ========= Setters and Getters Functions =========

	Input * GetInput() const;	// Gets a Pointer to the Input
	Output * GetOutput() const; // Gets a Pointer to the Output 

	void SetClipboard(Card * Card);  // A setter to be used in copy/cut (in order NOT to break class responsibilities)
	Card * GetClipboard() const;	 // A getter to be used in paste (in order NOT to break class responsibilities)

	void SetEndGame(bool endGame);	 // A setter for endGame data member
	bool GetEndGame() const;		 // A getter for endGame data member

	void AdvanceCurrentPlayer();     // Increments the currPlayerNum and if reaches MaxPlayerCount reset to 0 (using %)

	///TODO: add any needed setter/getter "EXCEPT" ANY setters or getters of "CellList" or "PlayerList" (Forbidden for class Responsibilities)

	// ========= Other Getters =========
	
	Player * GetCurrentPlayer() const;	// Gets a Pointer to the Current Player	                                    
	Ladder * GetNextLadder(const CellPosition & Position);  // Gets a Pointer to the first Ladder after the passed "Position"

	// ========= User Interface Functions =========

	void UpdateInterface() const;		// It Updates the Grid according to the last state of the game
	                                    // In Design mode, it draws all Cells/Cards THEN all ladders/snakes THEN all Players
	                                    // In Play mode, it only draws the Player's info on the right side of the toolbar
	                                    // Note: UpdatePlayerCell() function --> already update drawing Players in Play Mode
	                                    //       and the Cards/snakes/ladders Positions do NOT change already in Play Mode

	void PrintErrorMessage(string msg); // Prints an error message on statusbar, Waits for mouse click then clears statusbar
									    // We added this function once here because it is used many times by other classes
	GameObject*CheckIfIncludeGameObj( CellPosition  Position);
	void SaveAll(ofstream &outfile, int a);
	int GetLadderNum();
	int GetSnakeNum();
	int GetCardsNum();
	bool isoverlapping(GameObject*);
	bool EndofLadderandSnake(CellPosition);
	bool CellHasCard(CellPosition);
	GameObject* GetCard(CellPosition);
	Player* GetPlayerLeastMoney();
	void setPlayernum(int);
	void SetCurrPlayerNumber(int num);
	~Grid(); // A destructor for any needed deallcations

	Player* GetNextPlayer(Player* pPlayer);
};
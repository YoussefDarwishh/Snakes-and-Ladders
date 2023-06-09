#ifndef OUPTUT_H
#define OUPTUT_H

#include "DEFS.h"
#include "UI_Info.h" 
#include "CMUgraphicsLib\CMUgraphics.h"
#include "CellPosition.h"

// forward declarations (their includes are in the cpp)
class Input;

class Output	// The application manager & grid (phase 2) should have a pointer to this class
{
private:	

	window* pWind;	// Pointer to the Graphics Window
	
	// ========== Some Utility Functions (Private Functions) ==========

	///TODO: IMPLEMENT THE FOLLOWING FUNCTION
	int GetCellStartX(const CellPosition & CellPosition) const;	// Gets the X coordinate 
															// of the upper left corner of the passed CellPosition

	///TODO: IMPLEMENT THE FOLLOWING FUNCTION
	int GetCellStartY(const CellPosition & CellPosition) const;	// Gets the Y coordinate 
															// of the upper left corner of the passed CellPosition

	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION
	void DrawCardNumber(const CellPosition & CellPosition, int CardNum) const;	// Draws the passed Card "number"
																			// in the passed CellPosition

	void ClearToolBar() const;	// Clears the toolbar by drawing a filled rectangle

public:

	Output();	// A Constructor for any needed initializations

	window* CreateWind(int, int, int , int) const; // Creates the application window

	Input* CreateInput() const;	// Creates a pointer to the Input object	

	// ========== User Interface Functions ==========
	
	void ClearStatusBar() const;	// Clears the status bar by drawing a filled rectangle
	void ClearGridArea() const;	    // Draws an empty grid (horizontal and vertical lines with empty Cells)

	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION
	void CreateDesignModeToolBar() const;	// Creates the Design mode toolbar with all its menu icons

	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION
	void CreatePlayModeToolBar() const;		// Creates the Play mode toolbar with all its menu icons
	
	void PrintMessage(string msg) const;	// Prints a message on Status bar

	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION
	void PrintPlayersInfo(string info);		// Prints Players' info on the right-side of the toolbar

	// ========== Game Drawing Functions ==========

	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION	
	void DrawCell(const CellPosition & CellPosition, int CardNum=-1) const;	
													// Draws "Cell Rectangle" with "Cell Number"
													// and "Card Number" (if any), CardNum=-1 means no Card
													// the Cell rectangle's color depends on heving a Card or not

	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION	
	void DrawPlayer(const CellPosition & CellPosition, int PlayerNum, color PlayerColor) const;  
	                                                // Draws "Player Circle" filled with the passed color
													// "PlayerNum" parameter is used for locating the circle
													// ** Players' Circles Locations depending on "PlayerNum" is as follows: **
													//    Player_0   Player_1
													//    Player_2   Player_3
	
	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION	
	void DrawLadder(const CellPosition & fromCellPos, const CellPosition & toCellPos) const;
													// Draws Ladder from start Cell to end Cell (start < end)
													// Ladder is drawn as follows:
													// 1- two vertical lines
													// 2- horizontal lines as many as the Cell borders between the start and end
												    // Don't forget any needed Validations on fromCellPos and toCellPos
	
	///TODO: COMPLETE THE IMPLEMENTATIN OF THE FOLLOWING FUNCTION	
	void DrawSnake(const CellPosition & fromCellPos, const CellPosition & toCellPos) const;
													// Draws Snake from start Cell to end Cell (start > end)
													// 1- Snake's body is drawn as Line
													// 2- Snake's head is drawn as Polygon (with Diamond Shape)
													// Don't forget any needed Validations on fromCellPos and toCellPos

	void removeLadder(const CellPosition & CellStart ,const CellPosition & CellEnd) const;

	~Output();	// A Destructor for any needed deallocations
};

#endif
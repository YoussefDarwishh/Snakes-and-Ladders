#pragma once

#include "Action.h"

class AddSnakeAction : public Action
{

	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition StartPosition; // 1- The start Position of the ladder
	CellPosition EndPosition;   // 2- The end Position of the ladder

	// Note: These parameters should be read in ReadActionParameters()

	bool Valid;

public:

	AddSnakeAction(ApplicationManager *ProjectApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddLadderAction action parameters (StartPosition, EndPosition)
	
	virtual void Execute(); // Creates a new Ladder Object 
	                        // then Sets this Ladder object to the GameObject Pointer of its Cell
	

	virtual ~AddSnakeAction(); // Virtual Destructor

};


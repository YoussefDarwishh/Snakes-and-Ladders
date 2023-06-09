#pragma once
class Cell;
#include "Action.h"
#include "Cell.h"
class deleteGOA : public Action
{
private:
	// parameters
	int Delete;
	 // to choose the Cell that has the start of the game object
public:
	deleteGOA(ApplicationManager *ProjectApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (CardNumber, CardPosition)
	
	virtual void Execute(); // Creates a new Card Object of the specific Card Number
	                        // and Reads the Parameters of This Card Number (if any)
	                        // then Sets this Card Object to GameObject Pointer of its Cell
	
	virtual ~deleteGOA(); // A Virtual Destructor


};
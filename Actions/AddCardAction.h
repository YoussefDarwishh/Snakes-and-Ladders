#pragma once

#include "Action.h"

class AddCardAction : public Action
{
	// [Action Parameters]
	int CardNumber;            // 1- the Card number
	CellPosition CardPosition; // 2- Cell Position of the Card
	bool CheckPosition;
	// Note: These parameters should be read in ReadActionParameters()
	
public:
	AddCardAction(ApplicationManager *ProjectApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (CardNumber, CardPosition)
	
	virtual void Execute(); // Creates a new Card Object of the specific Card Number
	                        // and Reads the Parameters of This Card Number (if any)
	                        // then Sets this Card Object to GameObject Pointer of its Cell
	
	virtual ~AddCardAction(); // A Virtual Destructor
};
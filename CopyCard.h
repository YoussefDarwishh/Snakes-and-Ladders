#pragma once

#include "Action.h"
#include"Grid.h"

class CopyCard : public Action
{
private:
	Card* pCard;
	CellPosition pos;
	bool valid;

public:
	CopyCard(ApplicationManager *pApp); //constructor

	virtual void ReadActionParameters(); // Reads copy action parameters (pos)

	virtual void Execute(); // Copy card  
	                        
	virtual ~CopyCard();
};


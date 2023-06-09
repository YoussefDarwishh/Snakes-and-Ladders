#pragma once

#include "Action.h"
#include"Grid.h"

class CopyCard : public Action
{
private:
	Card* pCard;
	CellPosition Position;
	bool Valid;

public:
	CopyCard(ApplicationManager *ProjectApp); //constructor

	virtual void ReadActionParameters(); // Reads copy action parameters (Position)

	virtual void Execute(); // Copy Card  
	                        
	virtual ~CopyCard();
};


#pragma once


#include "Action.h"
#include"Grid.h"

class CutCard : public Action
{
private:
	Card* pCard;
	CellPosition Position;
	bool Valid;

public:
	CutCard(ApplicationManager *ProjectApp); //constructor

	virtual void ReadActionParameters(); // Reads copy action parameters (Position)

	virtual void Execute(); // Copy Card  
	                        
	virtual ~CutCard();
};


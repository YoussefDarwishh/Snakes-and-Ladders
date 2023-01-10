#pragma once

#include "Action.h"
#include"Grid.h"



class PasteCard  : public Action
{

	Card* pastedCard;
	CellPosition cardPosition;
	bool valid;
public:
	PasteCard(ApplicationManager *pApp);

	virtual void ReadActionParameters(); // Reads paste action parameters (cell pos)

	virtual void Execute(); // paste card  
	                        
	virtual ~PasteCard();
};


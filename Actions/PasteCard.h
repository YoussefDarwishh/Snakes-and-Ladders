#pragma once

#include "Action.h"
#include"Grid.h"



class PasteCard  : public Action
{

	Card* PastedCard;
	CellPosition CardPosition;
	bool Valid;
public:
	PasteCard(ApplicationManager *ProjectApp);

	virtual void ReadActionParameters(); // Reads paste action parameters (Cell Position)

	virtual void Execute(); // paste Card  
	                        
	virtual ~PasteCard();
};


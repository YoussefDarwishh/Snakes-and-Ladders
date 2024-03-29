#pragma once

#include "Action.h"

class NewGame : public Action
{

public:
	NewGame(ApplicationManager *ProjectApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddLadderAction action parameters 
	
	virtual void Execute();  // starts new game
	

	~NewGame(); 
};


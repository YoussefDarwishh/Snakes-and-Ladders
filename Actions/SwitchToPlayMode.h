#pragma once

#include "Action.h"
#include"Grid.h"


class SwitchToPlayMode  : public Action
{

public:

	SwitchToPlayMode(ApplicationManager *ProjectApp);  //constructor

	virtual void ReadActionParameters(); // Reads  action parameters 

	virtual void Execute(); // Copy Card  
	                        
	virtual ~SwitchToPlayMode();
};


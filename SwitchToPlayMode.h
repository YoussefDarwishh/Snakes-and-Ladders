#pragma once

#include "Action.h"
#include"Grid.h"


class SwitchToPlayMode  : public Action
{

public:

	SwitchToPlayMode(ApplicationManager *pApp);  //constructor

	virtual void ReadActionParameters(); // Reads  action parameters 

	virtual void Execute(); // Copy card  
	                        
	virtual ~SwitchToPlayMode();
};


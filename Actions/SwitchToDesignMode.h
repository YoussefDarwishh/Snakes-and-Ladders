#pragma once

#include "Action.h"
#include"Grid.h"

class SwitchToDesginMode  : public Action
{
public:
	SwitchToDesginMode(ApplicationManager *ProjectApp);  //constructor

	virtual void ReadActionParameters(); // Reads  action parameters 

	virtual void Execute(); // Copy Card  

	~SwitchToDesginMode(void);
};


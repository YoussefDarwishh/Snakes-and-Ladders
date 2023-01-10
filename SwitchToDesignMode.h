#pragma once

#include "Action.h"
#include"Grid.h"

class SwitchToDesginMode  : public Action
{
public:
	SwitchToDesginMode(ApplicationManager *pApp);  //constructor

	virtual void ReadActionParameters(); // Reads  action parameters 

	virtual void Execute(); // Copy card  

	~SwitchToDesginMode(void);
};


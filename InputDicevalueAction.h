#pragma once

#include "Action.h"


class InputDiceValueAction :public Action
{
	int diceNumber;
	bool valid;

public:
	InputDiceValueAction(ApplicationManager *pApp);
	
	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceValueAction();
};


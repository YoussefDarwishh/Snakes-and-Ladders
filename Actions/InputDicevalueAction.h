#pragma once

#include "Action.h"


class InputDiceValueAction :public Action
{
	int DiceNumber;
	bool Valid;

public:
	InputDiceValueAction(ApplicationManager *ProjectApp);
	
	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceValueAction();
};


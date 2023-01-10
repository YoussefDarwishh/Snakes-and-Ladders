#include "SwitchToPlayMode.h"


SwitchToPlayMode::SwitchToPlayMode(ApplicationManager *pApp)  : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

void SwitchToPlayMode::ReadActionParameters()
{
	// no parameters to read from user
}


void SwitchToPlayMode::Execute()
{
	Grid*pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->CreatePlayModeToolBar();
}

SwitchToPlayMode::~SwitchToPlayMode(void)
{
}

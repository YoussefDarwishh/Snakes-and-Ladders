#include "SwitchToDesignMode.h"

SwitchToDesginMode::SwitchToDesginMode(ApplicationManager *ProjectApp)  : Action(ProjectApp)
{
	// Initializes the ProjectManager pointer of Action with the passed pointer
}

void SwitchToDesginMode::ReadActionParameters()
{
	// no parameters to read from user
}

void SwitchToDesginMode::Execute()
{
	Grid*pGrid = ProjectManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->CreateDesignModeToolBar();
}

SwitchToDesginMode::~SwitchToDesginMode(void)
{
}
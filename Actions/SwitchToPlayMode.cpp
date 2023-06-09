#include "SwitchToPlayMode.h"


SwitchToPlayMode::SwitchToPlayMode(ApplicationManager *ProjectApp)  : Action(ProjectApp)
{
	// Initializes the ProjectManager pointer of Action with the passed pointer
}

void SwitchToPlayMode::ReadActionParameters()
{
	// no parameters to read from user
}


void SwitchToPlayMode::Execute()
{
	Grid*pGrid = ProjectManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->CreatePlayModeToolBar();
}

SwitchToPlayMode::~SwitchToPlayMode(void)
{
}

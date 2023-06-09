#include "SaveGridAction.h"
#include "Grid.h"
#include <fstream>

SaveGridAction::SaveGridAction (ApplicationManager *ProjectApp) : Action(ProjectApp)
{
}

void SaveGridAction :: ReadActionParameters()
{
	pGrid = ProjectManager->GetGrid();
	pGrid->GetOutput()->PrintMessage("Please Enter The File Name"); //asking user to enter file name to save
	name = pGrid->GetInput()->GetSrting(pGrid->GetOutput()); //setting member with given name
}

void SaveGridAction :: Execute()
{
	ReadActionParameters();
	ofstream Ofile(name+".txt",ios::out); //For some reason if i dont add the .txt it sometimes wont open?
	Ofile.close();
	Ofile.open(name+ ".txt",ios::app); //GUYS THIS IS NEW I UNDERSTOOD IT MN SELF STUDY MATERIAL SO WE DONT OVERWRITE IT
	Ofile<<pGrid->GetLadderNum()<<endl;
	pGrid->SaveAll(Ofile,1); // 1 for ladders
	Ofile<<pGrid->GetSnakeNum()<<endl;
	pGrid->SaveAll(Ofile,2); // 2 for snakes
	Ofile<<pGrid->GetCardsNum()<<endl;
	for (int i=3; i<15; i++)
	{
	pGrid->SaveAll(Ofile,i); // 3 = CardOne, 4 = CardTwo ... 14 = CardTwelve
	}
	Ofile.close();
}

SaveGridAction :: ~SaveGridAction()
{
}
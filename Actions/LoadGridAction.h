#include "Action.h"
#include <fstream>

class LoadGridAction : public Action
{
private:
	Grid*pGrid;
	string name;
	//removing the ifile here also like savegrid since we dont actually use it
public:

	LoadGridAction (ApplicationManager *ProjectApp);  // Constructor
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~LoadGridAction();
};
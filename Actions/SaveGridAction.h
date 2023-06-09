#include "Action.h"
#include <fstream>

class SaveGridAction : public Action
{
private:
	Grid*pGrid;
	string name;

public:
	//I AM REMOVING THE "ofstream Ofile" 
	//I HAVE TO MAKE A NEW ONE GOWA KDA KDA
	SaveGridAction (ApplicationManager *ProjectApp);  // Constructor
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~SaveGridAction();
};
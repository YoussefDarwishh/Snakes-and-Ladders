#pragma once
#include "Grid.h"

// Base Class for All Game Objects ( ladders, snakes and Cards )
class GameObject
{

protected:

	CellPosition Position; // The Current Cell Position of the GameObject
	
public:

	GameObject(const CellPosition & Position); // Constructor for initializing data members
	GameObject();
	
	CellPosition GetPosition() const;     // A Getter for Position
	void SetPosition(CellPosition Position);
	// ============ Virtual Functions ============

	virtual void Draw(Output* pOut) const = 0;	 // Draws the game object in the window in his Position Cell 
											     // (drawing depends on GameObject Type, so virtual)

	virtual void Apply(Grid* pGrid, Player* pPlayer) = 0;  // Applys the effect of the GameObject on the passed Player
	                                                       // (The effect depends on the GameObject type, so virtual)
	                                                       // For example, applying a ladder is by moving Player up, and so on
	virtual bool isoverlapping(GameObject*a) const;

	// The following functions are examples of what should be supported by the GameObject class
	// They should be overridden by each inherited class

	// Decide the parameters that you should pass to each function	
	
	virtual void Save(ofstream &OutFile, int a) = 0;	// Saves the GameObject parameters to the file
	virtual void Load(ifstream &Infile, Grid*pGrid, GameObject*object) = 0;	// Loads and Reads the GameObject parameters from the file
	CellPosition getStartPos();
	virtual ~GameObject(); // Virtual destructor
};
#pragma once

#include "GameObject.h"

class Snake :	public GameObject
{

	// Note: the "Position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the ladder's End Cell Position

public:

	Snake(const CellPosition & startCellPos, const CellPosition & endCellPos);
	Snake();

	virtual void Draw(Output* pOut) const; // Draws a snake from its start Cell to its end Cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the snake by moving Player to ladder's end Cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	virtual void Save(ofstream &OutFile, int a);
	virtual void Load(ifstream &Infile,Grid*pGrid,GameObject*type);

	virtual bool isoverlapping(GameObject*a) const;

	virtual ~Snake();
};
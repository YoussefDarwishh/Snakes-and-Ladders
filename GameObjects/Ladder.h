#pragma once

#include "GameObject.h"

class Ladder :	public GameObject // inherited from GameObject
{
	// Note: the "Position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the ladder's End Cell Position
		int notDeleted;  // if =1 then not deleted if 0 then deleted
public:

	Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos); // A constructor for initialization
	Ladder();
	virtual void Draw(Output* pOut) const; // Draws a ladder from its start Cell to its end Cell
		void remove(Output* pOut) ; // removes a ladder from its start Cell to its end Cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving Player to ladder's end Cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	virtual bool isoverlapping (GameObject*a) const;

	virtual void Save(ofstream &OutFile, int a); //override
	virtual void Load(ifstream &Infile,Grid*pGrid,GameObject*type);
	virtual ~Ladder(); // Virtual destructor
};


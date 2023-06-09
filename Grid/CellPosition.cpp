#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an inValid Cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an inValid Cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int CellNum)
{
	(*this) = GetCellPositionFromNum(CellNum); // the function call with build a Cell Position (vCell and hCell)
												// from the passed (CellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	if (v>-1 && v<9)
	{
		vCell = v;
		return true;
	}
	else
	{
		vCell = -1;
		return false;
	}
}

bool CellPosition::SetHCell(int h) 
{
	if (h>-1 && h<11)
	{
		hCell = h;
		return true;
	}
	else
	{
		hCell = -1;
		return false;
	}
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	int v = VCell();
	int h = HCell();
	if (h>-1 && h<11 && v>-1 && v<9)
		return true;
	else
		return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the Current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & CellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents Cell number and calculate it using the passed CellPosition then return it

	int Cellnumber;
	Cellnumber = (8-CellPosition.VCell())*11 + CellPosition.HCell() + 1;
	if (Cellnumber>99 || Cellnumber<1)
		return -1;
	else
	return Cellnumber;
}

CellPosition CellPosition::GetCellPositionFromNum(int CellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition Position;

	int V,H;
	if (CellNum<1 || CellNum>99)
	{
		Position.vCell = -1;
		Position.hCell = -1;
	}
	else
	{
	V = 8 - ((CellNum-1)/11);
	H = (CellNum-1)%11;
	Position.SetHCell(H);
	Position.SetVCell(V);
	}

	// Note: use the passed CellNum to set the vCell and hCell of the "Position" variable declared inside the function
	//       I mean: Position.SetVCell(...) and Position.SetHCell(...) then return it


	return Position;
}

void CellPosition::AddCellNum (int addedNum)
{
	
	/// TODO: Implement this function as described in the .h file
	int v,h,add;
	CellPosition A;
	add = GetCellNum() + addedNum;
	A=GetCellPositionFromNum(add);
	v = A.VCell();
	h = A.HCell();
	SetVCell(v);
	SetHCell(h);

	// Note: this function updates the data members (vCell and hCell) of the calling object

}
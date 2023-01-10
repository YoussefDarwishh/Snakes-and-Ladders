#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
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
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	int cellnumber;
	cellnumber = (8-cellPosition.VCell())*11 + cellPosition.HCell() + 1;
	if (cellnumber>99 || cellnumber<1)
		return -1;
	else
	return cellnumber;
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	int V,H;
	if (cellNum<1 || cellNum>99)
	{
		position.vCell = -1;
		position.hCell = -1;
	}
	else
	{
	V = 8 - ((cellNum-1)/11);
	H = (cellNum-1)%11;
	position.SetHCell(H);
	position.SetVCell(V);
	}

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
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
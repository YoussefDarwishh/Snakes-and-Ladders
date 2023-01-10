#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

GameObject::GameObject()
{
}

void GameObject :: SetPosition(CellPosition pos)
{
	position = pos;
}

CellPosition GameObject::GetPosition() const
{
	return position;
}


bool GameObject :: isoverlapping(GameObject*a) const
{
	return false;
}

CellPosition GameObject:: getStartPos()
{
	return position;

}

GameObject::~GameObject()
{
}
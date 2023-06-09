#include "GameObject.h"


GameObject::GameObject(const CellPosition & Position)
{
	Position = Position; // Sets Position
}

GameObject::GameObject()
{
}

void GameObject :: SetPosition(CellPosition Position)
{
	Position = Position;
}

CellPosition GameObject::GetPosition() const
{
	return Position;
}


bool GameObject :: isoverlapping(GameObject*a) const
{
	return false;
}

CellPosition GameObject:: getStartPos()
{
	return Position;

}

GameObject::~GameObject()
{
}
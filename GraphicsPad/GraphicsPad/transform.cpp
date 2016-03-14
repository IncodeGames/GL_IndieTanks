#include "transform.h"

bool Transform::HasChanged()
{
	/*if (parent != 0 && parent->HasChanged())
	{
		return true;
	}*/

	if (position != oldPos)
	{
		return true;
	}

	if (rotation != oldRot)
	{
		return true;
	}

	if (scale != oldScale)
	{
		return true;
	}

	return false;
}

void Transform::UpdateTransforms()
{
	if (initializedOldStuff)
	{
		oldPos = position;
		oldRot = rotation;
		oldScale = scale;
	}
	else
	{
		oldPos = position + glm::vec3(1, 1, 1);
		oldRot = rotation * 0.5f;
		oldScale = scale + glm::vec3(1, 1, 1);
		initializedOldStuff = true;
	}
}

void Transform::Rotate(const glm::vec3& axis, float angle)
{
	glm::rotate(angle , axis);
}

void Transform::Rotate(const glm::quat& rot)
{
	rotation = glm::normalize(rotation * rot);
	
}




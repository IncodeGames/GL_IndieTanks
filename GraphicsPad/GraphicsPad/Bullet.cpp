#include "Bullet.h"
#include "..\Rendering\Mesh.h"

Bullet::Bullet(glm::vec3 pos, float lifeSecs): lifetime(lifeSecs)
{
	GO_transform.SetPos(pos);
}

Bullet::Bullet(float lifeSecs) : lifetime(lifeSecs)
{
}

void Bullet::Move(glm::vec3 newPos)
{
	Mesh mesh("./Assets/Bullet.obj");
	mesh.Draw();
	GO_transform.SetPos(newPos);
}

Bullet::~Bullet()
{
}

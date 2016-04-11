#ifndef BULLET_H
#define BULLET_H

#include "..\core\Entity.h";
#include "..\Rendering\Mesh.h"

class Bullet : Entity
{
public:
	Bullet(glm::vec3 pos, float lifeSecs);
	Bullet(float lifeSecs);
	~Bullet();

	void Move(glm::vec3 newPos);

private:

	float lifetime;

	//void Move(glm::vec3 newPos);
};

#endif //BULLET_H
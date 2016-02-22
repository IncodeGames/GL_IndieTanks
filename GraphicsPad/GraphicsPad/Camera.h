#ifndef	CAMERA_H
#define CAMERA_H

#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar)
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar); //TODO: change if window is resized
		position = pos;

		//Create getters to modify these
		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return perspective * glm::lookAt(position, position + forward, up);
	}

protected:
private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif

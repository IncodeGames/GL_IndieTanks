#ifndef	CAMERA_H
#define CAMERA_H

#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>

class Camera
{
public:
	Camera()
	{
		perspective = glm::perspective(70.0f, 16.0f/9.0f, 0.01f, 1000.0f);
		position = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar)
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar); //TODO: change if window is resized
		position = pos;

		//Create setters to modify these?
		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);

		rotator = glm::rotate(0.0f, up);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return perspective * glm::lookAt(position, position + forward, up);
	}

	void move(glm::vec3 dir)
	{
		position +=  dir;
	}

	void rotate(float x, float y)
	{
		rotator = glm::rotate(-x, up) * glm::rotate(y, glm::cross(forward, up));
		forward = glm::mat3(rotator) * forward;
	}
protected:
private:
	glm::mat4 perspective;
	glm::mat4 rotator;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif

#ifndef	CAMERA_H
#define CAMERA_H

#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include "Entity.h"

class Camera : Entity
{
public:
	Camera()
	{
		perspective = glm::perspective(70.0f, 16.0f/9.0f, 0.01f, 1000.0f);
		GO_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar)
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar); //TODO: change if window is resized
		GO_transform.position = pos;

		//Create setters to modify these?
		forward = glm::vec3(0.0f, 0.0f, 1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		rotator = glm::rotate(0.0f, up);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return perspective * glm::lookAt(GO_transform.position, GO_transform.position + forward, up);
	}

	const glm::vec3 getForward() const { return forward; }
	glm::vec3 getPosition() { return GO_transform.position; }

	void moveForward(float speed)
	{
		GO_transform.position +=  speed * forward;
		printf("forward position: %f %f %f \n\n", forward.x, forward.y, forward.z);
	}

	void strafe(float speed)
	{
		GO_transform.position += speed * glm::cross(forward, up);
	}

	void rotate(float x, float y)
	{
		rotator = glm::rotate(-x, up) * glm::rotate(y, glm::cross(forward, up));
		forward = glm::mat3(rotator) * forward;
		printf("forward position: %f %f %f \n\n", forward.x, forward.y, forward.z);
	}
protected:
private:
	glm::mat4 perspective;
	glm::mat4 rotator;
	//glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif

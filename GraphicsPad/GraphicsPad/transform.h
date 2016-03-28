#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include <GLM\gtc\quaternion.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(0, 0, 0), const glm::quat& rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f), float scale = 1.0f) :
		position(pos),
		rotation(rot),
		scale(scale),
		//parent(0),
		//parentMatrix(Matrix4f().InitIdentity()),
		initializedOldStuff(false) {}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(position);
		glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	//glm::mat4 GetTransformation() const;
	bool HasChanged();
	void UpdateTransforms();
	void Rotate(const glm::vec3& axis, float angle);
	void Rotate(const glm::quat& rotation);
	//void LookAt(const glm::vec3& point, const glm::vec3& up);

	/*glm::quat GetLookAtRotation(const glm::vec3& point, const glm::vec3& up)
	{
		return glm::quat(Matrix4f().InitRotationFromDirection((point -position).Normalized(), up));
	}*/

	inline glm::vec3* GetPos()					 { return &position; }
	inline const glm::vec3& GetPos()       const { return position; }
	inline glm::quat* GetRot()					 { return &rotation; }
	inline const glm::quat& GetRot()	   const { return rotation; }
	inline glm::vec3 GetScale()			   const { return scale; }
	//inline glm::vec3 GetTransformedPos()   const { return glm::vec3(GetParentMatrix().Transform(position)); }
	glm::quat GetTransformedRot()          const;

	inline void SetPos(const glm::vec3& pos) { position = pos; }
	inline void SetRot(const glm::quat& rot) { rotation = rot; }
	inline void SetScale(float scale) { scale = scale; }
	inline void SetParent(Transform* parent) { parent = parent; }

private:
	//const glm::mat4& GetParentMatrix() const;

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	/*Transform* parent;
	mutable glm::mat4 parentMatrix;*/ //TODO: May need to specify fmat4, and check if parent matrix is needed

	mutable glm::vec3 oldPos;
	mutable glm::quat oldRot;
	mutable glm::vec3 oldScale;
	mutable bool initializedOldStuff;
};

#endif
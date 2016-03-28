/*#ifndef ENTITYOBJECT_H
#define ENTITYOBJECT_H

#include <vector>
#include "GLM\glm.hpp"
#include "..\transform.h"
#include <SDL2\SDL.h>
class Camera;
class CoreEngine;
class EntityComponent;
class Shader;
class RenderingEngine;

class Entity
{
public:
	Entity(const glm::vec3& pos = glm::vec3(0, 0, 0), const glm::quat& rot = glm::quat(0, 0, 0, 1), float scale = 1.0f) :
		m_transform(pos, rot, scale),
		m_coreEngine(0) {}

	virtual ~Entity();

	Entity* AddChild(Entity* child);
	Entity* AddComponent(EntityComponent* component);

	void ProcessInputAll(const SDL_Event& input, float delta);
	void UpdateAll(float delta);
	void RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;

	std::vector<Entity*> GetAllAttached();

	inline Transform* GetTransform() { return &m_transform; }
	void SetEngine(CoreEngine* engine);
protected:
private:
	std::vector<Entity*>          m_children;
	std::vector<EntityComponent*> components;
	Transform                     m_transform;
	CoreEngine*                   m_coreEngine;

	void ProcessInput(const SDL_Event& input, float delta);
	void Update(float delta);
	void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;

	Entity(const Entity& other) {}
	void operator=(const Entity& other) {}
};

#endif // GAMEOBJECT_H
*/
#ifndef ENTITYOBJECT_H
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
		GO_transform(pos, rot, scale),
		coreEngine(0) {}

	virtual ~Entity();

	Entity* AddChild(Entity* child);
	Entity* AddComponent(EntityComponent* component);

	void ProcessInputAll(const SDL_Event& input, float delta);
	void UpdateAll(float delta);
	void RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;

	std::vector<Entity*> GetAllAttached();

	inline Transform* GetTransform() { return &GO_transform; }
	void SetEngine(CoreEngine* engine);
protected:
	Transform GO_transform;
private:
	std::vector<Entity*>          children;
	std::vector<EntityComponent*> components;
	CoreEngine*                   coreEngine;

	void ProcessInput(const SDL_Event& input, float delta);
	void Update(float delta);
	void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;

	Entity(const Entity& other) {}
	void operator=(const Entity& other) {}
};

#endif // GAMEOBJECT_H

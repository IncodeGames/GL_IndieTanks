#include "Entity.h"
#include "Entity_Component.h"
#include "Main_IndieTanks.h"

Entity::~Entity()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		if (components[i])
		{
			delete components[i];
		}
	}

	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i])
		{
			delete children[i];
		}
	}
}

Entity* Entity::AddChild(Entity* child)
{
	children.push_back(child);
	child->GetTransform()->SetParent(&GO_transform);
	child->SetEngine(coreEngine);
	return this;
}

Entity* Entity::AddComponent(EntityComponent* component)
{
	components.push_back(component);
	component->SetParent(this);
	return this;
}

void Entity::ProcessInputAll(const SDL_Event& input, float delta)
{
	ProcessInput(input, delta);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->ProcessInputAll(input, delta);
	}
}

void Entity::UpdateAll(float delta)
{
	Update(delta);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->UpdateAll(delta);
	}
}

void Entity::RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
{
	Render(shader, renderingEngine, camera);

	for (unsigned int i = 0; i < children.size(); i++)
	{
		children[i]->RenderAll(shader, renderingEngine, camera);
	}
}

void Entity::ProcessInput(const SDL_Event& input, float delta)
{
	GO_transform.UpdateTransforms();

	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->ProcessInput(input, delta);
	}
}

void Entity::Update(float delta)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->Update(delta);
	}
}

void Entity::Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->Render(shader, renderingEngine, camera);
	}
}

void Entity::SetEngine(CoreEngine* engine)
{
	if (coreEngine != engine)
	{
		coreEngine = engine;

		for (unsigned int i = 0; i < components.size(); i++)
		{
			components[i]->AddToEngine(engine);
		}

		for (unsigned int i = 0; i < children.size(); i++)
		{
			children[i]->SetEngine(engine);
		}
	}
}

std::vector<Entity*> Entity::GetAllAttached()
{
	std::vector<Entity*> result;

	for (unsigned int i = 0; i < children.size(); i++)
	{
		std::vector<Entity*> childObjects = children[i]->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	result.push_back(this);
	return result;
}

#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
	World::World(Application* owningApp):
		mOwningApp{owningApp},mBeginPlay{false}
	{
	}
	World::~World()
	{
	}

	void World::BeginPlayInternal()
	{
		if (!mBeginPlay) {
			mBeginPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void World::BeginPlay()
	{
		LOG("began play");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Tick at frame rate %f", 1.f / deltaTime);
	}
}

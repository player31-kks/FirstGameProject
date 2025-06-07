#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
	World::World(Application* owningApp):
		mOwningApp{ owningApp }, mBeginPlay{ false }, 
		mActors{}, 
		mPendingActors{}
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
		for (shared<Actor> actor : mPendingActors) {
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}
		mPendingActors.clear();

		for (auto iter = mActors.begin(); iter != mActors.end();) {
			if (iter->get()->isPendingObject()) {
				iter = mActors.erase(iter);
			}
			else {
				iter->get()->Tick(deltaTime);
				++iter;
			}
		}
		Tick(deltaTime);
	}

	void World::BeginPlay()
	{
	}

	void World::Tick(float deltaTime)
	{
	}

	void World::Render(sf::RenderWindow& window) {
		for (auto& actor : mActors) {
			actor->Render(window);
		}
	}
}

#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include <type_traits>

namespace ly
{
	class Actor;
	class Application;


	template<typename T>
	concept DerivedFromActor = std::is_base_of_v<Actor, T>;

	class World {
	public:
		World(Application* owningApp);
		virtual ~World();

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		template<DerivedFromActor ActorType>
		weak<ActorType> SpawnActor() {
			shared<ActorType> newActor{ new ActorType{this} };
			mPendingActors.emplace_back(newActor);
			return newActor;
		}

	private:
		void BeginPlay();
		void Tick(float deltaTime);

		Application* mOwningApp;
		bool mBeginPlay;

		List<shared<Actor>> mActors;
		List<shared<Actor>> mPendingActors;
	};
}
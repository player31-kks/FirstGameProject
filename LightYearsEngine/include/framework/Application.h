#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/World.h"

namespace ly 
{
	class World;
	class Application
	{
		public:
			Application(unsigned int windowWidth,unsigned int windowHeight, const std::string& title, sf::Uint32 style);
			void Run();

			template<typename WorldType>
			weak<WorldType> LoadWorld();

		private:
			void TickInternal(float deltaTime);
			void RenderInternal();

			virtual void Render();
			virtual void Tick(float delatTime);

			sf::RenderWindow mWindow;
			sf::Clock mTickClock;
			float mTargetFrameRate;
			shared<ly::World> currentWorld;
			sf::Clock mCleanCycleClock;
			float mCleanCycleInterval;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld() {
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}
}

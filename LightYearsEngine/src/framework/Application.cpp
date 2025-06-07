#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include <iostream>

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		:mWindow{ sf::VideoMode(windowWidth,windowHeight),title,style },
		mTargetFrameRate(60.f),
		mTickClock{},
		currentWorld{ nullptr },
		mCleanCycleClock{},
		mCleanCycleInterval{ 2.f }

	{
	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		const float targetDelatTime = 1.f / mTargetFrameRate;
		while (mWindow.isOpen()) {
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed) {
					mWindow.close();
				}
			}
			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDelatTime)
			{
				accumulatedTime -= targetDelatTime;
				TickInternal(targetDelatTime);
				RenderInternal();
			}
		}
	}
	void Application::TickInternal(const float deltaTime)
	{
		Tick(deltaTime);
		if (currentWorld) {
			currentWorld->BeginPlayInternal();
			currentWorld->TickInternal(deltaTime);
		}

		if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval) {
			mCleanCycleClock.restart();
			AssetManager::Get().ClearCycle();
		}
	}
	void Application::RenderInternal()
	{
		mWindow.clear();
		Render();
		mWindow.display();
	}
	void Application::Render()
	{
		if (currentWorld) {
			currentWorld->Render(mWindow);
		}
	}
	void Application::Tick(float delatTime)
	{
	}
}

#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include <iostream>

namespace ly
{
	Application::Application()
		:mWindow{ sf::VideoMode(1024,1440),"MyWindow" },
		mTargetFrameRate(60.f),
		mTickClock{},
		currentWorld{ nullptr }
	{
	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDelatTime = 1.f / mTargetFrameRate;
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
			LOG("ticking at frameter : %f", 1.f / frameDeltaTime);
		}
	}
	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (currentWorld) {
			currentWorld->BeginPlayInternal();
			currentWorld->TickInternal(deltaTime);
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
		sf::RectangleShape rect{ sf::Vector2f{100,100} };
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(50, 50);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);
		mWindow.draw(rect);
	}
	void Application::Tick(float delatTime)
	{

	}
}

#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"


ly::Application* GetApplication()
{
	return new ly::GameApplication();
}

namespace ly
{
	GameApplication::GameApplication()
		:Application{600,980,"LightYear",sf::Style::Titlebar|sf::Style::Close}
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		actorToDestory = newWorld.lock()->SpawnActor<Actor>();
		actorToDestory.lock()->SetTexture(GetResourceDir()+"SpaceShooterRedux/PNG/playerShip1_blue.png");
		actorToDestory.lock()->SetLocation(sf::Vector2f(300.f,490.f));
		actorToDestory.lock()->SetRotation(90.f);
		counter = 0;
	}
	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
		if (counter > 2.f) {
			if (!actorToDestory.expired()) {
				actorToDestory.lock()->Destory();
			}
		}
	}
}

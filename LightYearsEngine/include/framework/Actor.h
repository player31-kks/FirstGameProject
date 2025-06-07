#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Object.h"
#include "framework/Core.h"


namespace ly {
	class World;

	class Actor:public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		void TickInternal(float deltaTime);
		void BeginPlayInternal();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);
		void SetLocation(const sf::Vector2f& newLoc);
		void SetRotation(float newRotate);

		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);

		sf::Vector2f GetActorLocation() const;
		float GetActorRoatation() const;

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;



	private:
		void centerPivot();
		World* mOwingWorld;
		bool mHasBeginPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
	};
}

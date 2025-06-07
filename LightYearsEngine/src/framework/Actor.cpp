#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtil.h"



namespace ly {
	Actor::Actor(World* owningWorld, const std::string& texturePath):
		mOwingWorld{ mOwingWorld },
		mSprite{},
		mTexture{}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor() {
		LOG("Actor destory");
	}

	void Actor::BeginPlayInternal() {
		if (!mHasBeginPlay) {
			mHasBeginPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime) {
		if (!isPendingObject()) {
			Tick(deltaTime);
		}
	}

	void Actor::BeginPlay(){
	}

	void Actor::Tick(float deltaTime) {
	}

	void Actor::SetTexture(const std::string& texturePath) {
		mTexture = AssetManager::Get().LoadTexture(texturePath);
		
		if (!mTexture)return;
		mSprite.setTexture(*mTexture);
		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect(sf::Vector2i{}, sf::Vector2i{textureWidth,textureHeight}));
		centerPivot();
	}
	
	void Actor::Render(sf::RenderWindow& window) {
		if (isPendingObject())
			return;
		window.draw(mSprite);
	}

	void Actor::SetLocation(const sf::Vector2f& newLoc) {
		mSprite.setPosition(newLoc);
	}

	void Actor::SetRotation(float newRotate) {
		mSprite.setRotation(newRotate);
	}

	sf::Vector2f Actor::GetActorLocation() const {
		return mSprite.getPosition();
	}

	float Actor::GetActorRoatation() const {
		return mSprite.getRotation();
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt) {
		SetLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(float offsetAmt) {
		SetRotation(GetActorRoatation() + offsetAmt);
	}

	void Actor::centerPivot() {
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}

	sf::Vector2f Actor::GetActorForwardDirection() const {
		return RotationToVector(GetActorRoatation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const{
		return RotationToVector(GetActorRoatation() + 90.f);
	}
}

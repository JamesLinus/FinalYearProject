#include <include\Camera.hpp>

Camera::Camera(sf::Vector2u const &screenSize, sf::Vector2f const &boundingArea) :
View(sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Vector2f(screenSize)),
mScreenSize(screenSize),
mBoundingArea(boundingArea)
{
	_ASSERT(screenSize.x < boundingArea.x);
	_ASSERT(screenSize.y < boundingArea.y);
}

Camera::Camera(sf::Vector2u const &screenSize, sf::Vector2f const &boundingArea, Actor * target) :
View(sf::Vector2f(screenSize.x / 2, screenSize.y / 2), sf::Vector2f(screenSize)),
mScreenSize(screenSize),
mBoundingArea(boundingArea),
mTarget(target)
{
	_ASSERT(screenSize.x < boundingArea.x);
	_ASSERT(screenSize.y < boundingArea.y);
}

void Camera::setTarget(Actor* target)
{
	mTarget = target;
}

Actor * Camera::getTarget() const {
	return mTarget;
}

void Camera::clearTarget()
{
	mTarget = nullptr;
}

sf::Vector2f Camera::getDisplacement() const {
	//return the point at the top left corner
	return getCenter() - (getSize() * 0.5f);
}

void Camera::update()
{
	if (mTarget)
	{
		sf::Vector2f newCenter = mTarget->getPosition();

		//stop edge of camera going out of bounds
		const sf::Vector2f halfSize = getSize() * 0.5f;
		clamp(newCenter, halfSize, mBoundingArea - halfSize);

		setCenter(newCenter);
	}
}

void Camera::clamp(sf::Vector2f& value, sf::Vector2f const& min, sf::Vector2f const& max) const {
	//assert that min is less than max
	_ASSERT(min.x < max.x && min.y < max.y);

	//clamp x value
	if (value.x < min.x) {
		value.x = min.x;
	}
	else if (value.x > max.x) {
		value.x = max.x;
	}

	//clamp y value
	if (value.y < min.y) {
		value.y = min.y;
	}
	else if (value.y > max.y) {
		value.y = max.y;
	}
}
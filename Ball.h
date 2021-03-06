#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
private:
	sf::Vector2f pos;
	float mass,radius;
	sf::Color color;

	sf::Vector2f acc, vel;

public:
	Ball(const sf::Vector2f& Pos, float Mass=1.f);

	void Update(float dt);
	void ApplyForce(const sf::Vector2f& F);
	void ApplyGravity(const sf::Vector2f& G);
	void Hit(const sf::Vector2f N);
	sf::CircleShape getShape();
	sf::Vector2f getPos() const { return pos; };
	void ClearForces();
	void RotateForces(float angle);

	float getMass() const { return mass; };
	float getRadius() const { return radius; };
};


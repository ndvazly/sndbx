#include "Ball.h"
#include "Vec.h"
#include <iostream>

Ball::Ball(const sf::Vector2f& Pos, float Mass): pos(Pos), mass(Mass)
{
	//mass = 0.25f;
	radius = mass * 10.f;
	color = sf::Color::Green;
	std::cout << "New Ball.\n mass = " << mass << "\n";
}

void Ball::Update(float dt)
{
	float air = 0.99f;
	acc *= air;
	vel *= air;
	sf::Vector2f lastvel = vel;
	vel += acc;
	//pos += (vel * dt);
	pos += 0.5f * (lastvel + vel) * dt;

	const float minmovement = 0.001f;
	if (Vec::LengthSqr(acc) < minmovement && Vec::LengthSqr(vel) < minmovement)
		ClearForces();
}

void Ball::ApplyForce(const sf::Vector2f& F)
{
	acc += F/mass;
	//Vec::Print(acc, "acc");
	//Vec::Print(vel, "vel");
}

void Ball::ApplyGravity(const sf::Vector2f& G)
{
	acc += G;
}

void Ball::Hit(const sf::Vector2f N)
{
	sf::Vector2f n(Vec::Normalized(N));		
	acc *= 0.9f;
	//vel *= 0.9f;
	vel = (vel - (n * 2.f * Vec::Dot(vel, n)));	
	const float friction = 0.1f;
	const float elastic = 0.5f;
	const float energyloss = 1 - (friction - elastic);
	vel *= energyloss;
	// v1' = v1 - (2*m2/(m1+m2))
	//const float m1 = mass;
	//const float m2 = 1.f;
	//const float theta = Vec::Angle(n);
	//Vec::Print(vel, "vel");
	//vel *= sqrt(m1*m1+m2*m2+2.f*m1*m2*cos(theta))/m1+m2;
	//Vec::Print(vel, "velafter");
}

sf::CircleShape Ball::getShape()
{
	sf::CircleShape c(radius);
	c.setOrigin(sf::Vector2f(radius, radius) / 2.f);
	c.setPosition(pos);
	c.setFillColor(color);
	return c;
}

void Ball::ClearForces()
{
	acc *= 0.f; 
	vel *= 0.f;
	//std::cout << "Ball::ClearForces()\n";
}

void Ball::RotateForces(float angle)
{
	acc = Vec::Rotate(acc, angle)*0.95f;
	vel = Vec::Rotate(vel, angle) * 0.95f;
}

//sf::Vector2f un(n * 2.f);
//float dot = Vec::Dot(vel, n);
//vel = vel - un * dot;

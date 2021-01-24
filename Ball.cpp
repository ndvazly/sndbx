#include "Ball.h"
#include "Vec.h"
#include <iostream>

Ball::Ball(const sf::Vector2f& Pos, float Mass): pos(Pos), mass(Mass)
{
	//mass = 0.25f;
	radius = mass * 10.f;
	color = sf::Color::Green;
}

void Ball::Update(float dt)
{
	float air = 0.99f;
	acc *= air;
	vel *= air;
	vel += acc;
	pos += (vel * dt);

	const float minmovement = 0.001f;
	if (Vec::LengthSqr(acc) < minmovement && Vec::LengthSqr(vel) < minmovement)
		ClearForces();
}

void Ball::ApplyForce(const sf::Vector2f& F)
{
	acc += F;
}

void Ball::Hit(const sf::Vector2f N)
{
	sf::Vector2f n(Vec::Normalized(N));	
	//acc = (acc - (n * 2.f * Vec::Dot(acc, n)))*0.5f;
	//vel = (vel - (n * 2.f * Vec::Dot(vel, n)))*0.9f;
	//vel *= 0.1f;
	//acc = (acc - (n * 2.f * Vec::Dot(acc, n)))/mass*0.7f;
	//vel = (vel - (n * 2.f * Vec::Dot(vel, n)))/mass*0.7f;
	vel = vel - (n * 2.f * Vec::Dot(vel, n))*(1.f/mass);	
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
	std::cout << "Ball::ClearForces()\n";
}

void Ball::RotateForces(float angle)
{
	acc = Vec::Rotate(acc, angle)*0.95f;
	vel = Vec::Rotate(vel, angle) * 0.95f;
}

//sf::Vector2f un(n * 2.f);
//float dot = Vec::Dot(vel, n);
//vel = vel - un * dot;

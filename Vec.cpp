#include "Vec.h"
#include <iostream>

void Vec::Print(const sf::Vector2f& v, const std::string& Name, bool Endline)
{
	std::cout << Name << ": " << v.x << ", " << v.y << ( (Endline) ? "\n" : "");
}

float Vec::LengthSqr(const sf::Vector2f& v)
{
	return (v.x * v.x) + (v.y * v.y);
}

float Vec::Length(const sf::Vector2f& v)
{
	return sqrt(LengthSqr(v));
}

float Vec::Angle(const sf::Vector2f& v)
{
	return atanf(v.y/v.x);
}

sf::Vector2f Vec::Rotate(const sf::Vector2f v, float theta)
{
	float xtag, ytag;
	xtag = v.x * cos(theta) - v.y * sin(theta);
	ytag = v.x * sin(theta) + v.y * cos(theta);
	return { xtag,ytag };
}

sf::Vector2f Vec::Normalized(const sf::Vector2f& v)
{
	return v/ sqrt(LengthSqr(v));
}

float Vec::Dot(const sf::Vector2f& a, const sf::Vector2f&  b)
{
	return a.x * b.x + a.y * b.y;
}

// POINT/CIRCLE Collision
bool Vec::CollPointCircle(const sf::Vector2f& p, const sf::Vector2f& c, float r) {

	// get distance between the point and circle's center
	// using the Pythagorean Theorem
	float distance = Vec::Length({ p.x - c.x,p.y - c.y });

	// if the distance is less than the circle's
	// radius the point is inside!
	return (distance <= r);
}
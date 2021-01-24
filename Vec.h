#pragma once
#include <SFML/Graphics.hpp>

class Vec
{
public:
	static void Print(const sf::Vector2f& v, const std::string& Name="", bool Endline=true);
	static void Print(const sf::Vector2i v);
	static float LengthSqr(const sf::Vector2f& v);
	static float Length(const sf::Vector2f& v);
	static float Dot(const sf::Vector2f& a, const sf::Vector2f& b);
	static float Angle(const sf::Vector2f& v);
	static sf::Vector2f Normalized(const sf::Vector2f& v);
	static sf::Vector2f Rotate(const sf::Vector2f v, float theta);

	static bool CollPointCircle(const sf::Vector2f& p, const sf::Vector2f& c, float r);
};


#pragma once
#include <utility>
#include "Vec.h"
#include <SFML/Graphics.hpp>
typedef  std::pair<sf::Vector2f, sf::Vector2f> vfPair;

class Line
{
public:
	static void Print(const vfPair& l, const std::string& Name = "", bool Endline = true);
	static sf::RectangleShape getLineRect(const vfPair& l, float Width=5);
	static float Length(const vfPair& l);
	static float LengthSqr(const vfPair& l);
	static bool CollLinePoint(const vfPair& l, const sf::Vector2f& p);
	static bool CollLineCircle(const vfPair& l, const sf::Vector2f& c, float r);
};
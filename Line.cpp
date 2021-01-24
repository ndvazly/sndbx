#include "Line.h"
#include <iostream>

void Line::Print(const vfPair& l, const std::string& Name, bool Endline)
{	
	Vec::Print(l.first, Name + " From", false);
	Vec::Print(l.second, Name + " To");
}

sf::RectangleShape Line::getLineRect(const vfPair& l,float Width)
{
	sf::Vector2f d(l.first - l.second);
	int dir = (l.first.x < l.second.x) ? 1 : -1;
	float len = Vec::Length(d) * dir;
	sf::RectangleShape linerect({ len,Width });
	linerect.setPosition(l.first);
	linerect.setRotation(Vec::Angle(d) * 57.295779513);
	return linerect;
}

float Line::Length(const vfPair& l)
{
	sf::Vector2f distance(l.first.x - l.second.x, l.first.y - l.second.y);	
	return Vec::Length(distance);
}

float Line::LengthSqr(const vfPair& l)
{
	sf::Vector2f distance(l.first.x - l.second.x, l.first.y - l.second.y);	
	return Vec::LengthSqr(distance);
}

bool Line::CollLinePoint(const vfPair& l, const sf::Vector2f& p) {

	auto sqrdist = [&](float x1, float y1, float x2, float y2) {		
			return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	};

	// get distance from the point to the two ends of the line
	float d1 = sqrt(sqrdist(p.x, p.y, l.first.x, l.first.y));
	float d2 = sqrt(sqrdist(p.x, p.y, l.second.x, l.second.y));

	// get the length of the line
	float lineLen = sqrt(sqrdist(l.first.x, l.first.y, l.second.x, l.second.y));

	// since floats are so minutely accurate, add
	// a little buffer zone that will give collision
	float buffer = 0.1;    // higher # = less accurate

	// if the two distances are equal to the line's 
	// length, the point is on the line!
	// note we use the buffer here to give a range, 
	// rather than one #
	if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
		return true;
	}
	return false;
}

bool Line::CollLineCircle(const vfPair& l, const sf::Vector2f& c, float r)
{
	float x1 = l.first.x; float x2 = l.second.x;
	float y1 = l.first.y; float y2 = l.second.y;

	/// Check if the line is inisde the circle
	bool inside1 = Vec::CollPointCircle(l.first, c, r);
	bool inside2 = Vec::CollPointCircle(l.second, c, r);
	if (inside1 || inside2) return true;

	float lensqr = Line::LengthSqr(l);
	
	/// Find closest point on line to c
	float dot = (((c.x - x1) * (x2 - x1)) + ((c.y - y1) * (y2 - y1))) / lensqr;
	float closestX = x1 + (dot * (x2 - x1));
	float closestY = y1 + (dot * (y2 - y1));

	/// Check if it's inside our line segment
	bool onSegment = Line::CollLinePoint(l, { closestX, closestY });
	if (!onSegment) 
		return false;

	/// Get distance to closest point on segment  distance = sqrt((distX * distX) + (distY * distY));	
	float distance = Vec::Length({ closestX - c.x,closestY - c.y });	
	/// If distance is smaller than the circle's radius, collision happened.
	if (distance <= r)
		return true;	

	return false;
}

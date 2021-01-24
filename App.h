#pragma once
#include <SFML/Graphics.hpp>
#include "Line.h"
#include "Ball.h"
#include <vector>

class App
{
private:
	int m_width, m_height;
	sf::RenderWindow* window;

	std::vector<vfPair> obstacles;
	vfPair *currentline;
	float line_width;

	float newball_mass = 1.f;
	std::vector<Ball> balls;

	sf::Vector2f gravity;

	void HandleEvents();
	void MouseInput(const sf::Event& event);

	void AddBoundingRect();

	void Update(float dt);

public:
	App(int Width, int Height); 
	void Run();
	~App();
};


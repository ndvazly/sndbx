#include "App.h"
#include "Vec.h"
#include <iostream>

App::App(int Width, int Height): m_width(Width), m_height(Height)
{
	window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "sndbx");
	currentline = nullptr;
	line_width = 5;
	gravity = { 0.f, 0.1f };
	AddBoundingRect();
}

void App::HandleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		MouseInput(event);		
	}
}

void App::MouseInput(const sf::Event& event)
{
	sf::Vector2f mpos = sf::Vector2f(sf::Mouse::getPosition(*window));
	// Left MouseButton Click
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			std::cout << "LClick\n";
			if (!currentline)
				currentline = new vfPair(mpos, mpos);
		}
		else {
			std::cout << "RClick\n";
			balls.push_back(Ball(mpos, newball_mass));
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) {// && event.mouseButton.button == sf::Mouse::Left) {				
		if (currentline) {
			Line::Print(*currentline);
			obstacles.push_back(*currentline);
			delete currentline;
			currentline = nullptr;
		}
	}

	//if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
	//	
	//}

	// LMB Drag
	if (event.type == sf::Event::MouseMoved)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (currentline)
				currentline->second = mpos;
		}

	// Mouse Wheel
	if (event.type == sf::Event::MouseWheelMoved) {
		/// Change between increments of +/-0.1 or +/-0.5  according to mass size 
		float stepsize = (newball_mass <= 1.f) ? 10.f :  2.f;
		newball_mass += (float)event.mouseWheel.delta/stepsize;
		if (!newball_mass)
			newball_mass = 0.1f;
	}
}

void App::AddBoundingRect()
{
	obstacles.push_back({ {0.f,0.f}, { (float)m_width,0.f } });
	obstacles.push_back({ {0.f,(float)m_height-line_width}, { (float)m_width,(float)m_height - line_width } });
	obstacles.push_back({ {0.f,0.f}, {0.f,(float)m_height } });
	obstacles.push_back({ {(float)m_width-line_width,0.f}, { (float)m_width - line_width,(float)m_height - line_width } });
}

void App::Update(float dt)
{
	//std::cout << "dt:" << dt << "\n";
	for (auto& b : balls) {
		bool collision=false;
		b.ApplyGravity(gravity);
		//collision = false;
		for (auto& o : obstacles) {
			sf::Vector2f p(b.getPos());
			//if (Line::CollLinePoint(o,p)) {				
			if (Line::CollLineCircle(o,p,b.getRadius())) {				
				sf::Vector2f d(o.second - o.first);
				sf::Vector2f normal(-d.y, d.x);												
				b.Hit(normal);
				collision = true;
				
				//std::cout << "Collision\n";
			}			
		}

		//if (!collision)
		//	b.ApplyGravity(gravity);

		b.Update(dt);
	}
}

void App::Run()
{
	sf::Clock sfdt;

	while (window->isOpen())
	{
		HandleEvents();
		window->clear();

		float dt = sfdt.restart().asSeconds();
		//std::cout << "dt: " << dt <<"\n";
		if (dt > 0.002f)
			dt = 0.002f;

		Update(dt);
		/// Draw Current Line
		if (currentline)
			window->draw(Line::getLineRect(*currentline));		

		/// Draw Obstacles
		for (auto& o : obstacles) {
			sf::RectangleShape rect(Line::getLineRect(o));
			rect.setFillColor(sf::Color::Yellow);

			sf::Vector2f d(o.second - o.first);
			sf::Vector2f normal(-d.y, d.x);		
			sf::Vector2f origin = o.first + d / 2.f;
			
			vfPair nline(origin, origin - Vec::Normalized(normal)*20.f);
			sf::RectangleShape normalrect(Line::getLineRect(nline));

			window->draw(normalrect);
			window->draw(rect);
		}

		/// Draw Balls
		for (auto& b : balls) {			
			window->draw(b.getShape());
		}

		window->display();
	}
}

App::~App()
{	
	delete window;
}

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	sf::Text text;
	//text.setFont(sf::Font); // font is a sf::Font
	text.setString("Click 3 times to set triangle vertices and 4th time to start the algorithm.");
	text.setCharacterSize(40); 
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					Vector2f click(event.mouseButton.x, event.mouseButton.y);
					if (vertices.size() < 3)
					{
						vertices.push_back(click);
					}
					else if (points.size() == 0)
					{
						///fourth click
						points.push_back(click); 
						///push back to points vector
						cout << "Starting point: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";

					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			///generate more point(s)
			for (int i = 0; i < 100; ++i) 
			{
				///select random vertex
				int randVer = rand() % 3; 

				///calculate midpoint between random vertex and the last point in the vector
				Vector2f mid; 
				mid.x = (points.back().x + vertices[randVer].x) / 2;
				mid.y = (points.back().y + vertices[randVer].y) / 2;

				///push back the newly generated coord.
				points.push_back(mid);
			}

		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(text);

		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::White);
			window.draw(rect);
		}


		///TODO:  Draw points
		for (auto& p : points) {
			CircleShape dot(1);
			dot.setPosition(p);
			dot.setFillColor(Color::Red);
			window.draw(dot);
		}

		window.display();
		
	}
}


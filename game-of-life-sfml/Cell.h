#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell
{
private:
	sf::RectangleShape rectangle;

	// Cell properties
	int m_Row, m_Col;
	int m_Width, m_Height;

	bool isAlive;

	// Color definitions
	sf::Color liveColor = sf::Color::Green;
	sf::Color deadColor = sf::Color::White;
	sf::Color gridColor = sf::Color(211, 211, 211);
public:
	void addCell(int row, int col, int width, int height); // Creates a cell
	void setState(bool state); // Sets the cells state

	bool getState(); // Returns the cells state
	bool tempState; // Stores the cells temporary state

	sf::RectangleShape getRectangle();
};
#endif
#include "Cell.h"

void Cell::addCell(int row, int col, int width, int height)
{
	isAlive = false; // A cell is DEAD by default

	m_Row = row;
	m_Col = col;
	m_Width = width;
	m_Height = height;

	// Grid cell properties
	rectangle = sf::RectangleShape(sf::Vector2f(m_Width, m_Height));
	rectangle.setPosition(m_Col, m_Row);
	rectangle.setFillColor(isAlive ? liveColor : deadColor);
	rectangle.setOutlineColor(gridColor);
	rectangle.setOutlineThickness(1);
}

void Cell::setState(bool state)
{
	isAlive = state;

	rectangle.setFillColor(isAlive ? liveColor : deadColor);
}

bool Cell::getState()
{
	return isAlive;
}

sf::RectangleShape Cell::getRectangle()
{
	return rectangle;
}
#ifndef CELLMAP_H
#define CELLMAP_H

#include "Util.h"
#include "Cell.h"

class CellMap
{
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Time time;

	Cell** m_CellMap; // Array to store the cellmap

	// Cellmap properties
	int m_Size;
	int m_Columns;
	int m_Rows;

	bool updated;
	bool paused;

	// Cellmap generation methods
	void initialise(int width, int height);
	void generate();
	void render();

	void deadState();
	void initialState();
	void nextState();

	int countCells(int col, int row);
	bool checkBounds(int col, int row);

	// User input methods
	void input();
public:
	// Starts the simulation
	void start(int width, int height);
};
#endif
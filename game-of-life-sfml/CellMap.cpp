#include "CellMap.h"

/**
  * Initialises the SFML window & m_CellMap array
  *
  * @param width The window width
  * @param width The window height
  *
  */
void CellMap::initialise(int width, int height)
{
	// Window properties
	window.create(sf::VideoMode(width, height), "Game of Life", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	// Grid properties
	m_Size = 20; // Cell size
	m_Columns = (window.getSize().y / m_Size) - 1; // Number of columns
	m_Rows = (window.getSize().x / m_Size) - 1; // Number of rows

	paused = true;

	// Dynamically allocates the 2D m_CellMap array
	m_CellMap = new Cell *[m_Columns];

	for (int col = 0; col < m_Columns; ++col)
	{
		m_CellMap[col] = new Cell[m_Rows];
	}
}

/**
  * Displays the simulation
  *
  */
void CellMap::generate()
{
	window.clear(sf::Color::Black);

	if (!paused)
	{
		nextState();
	}

	render();

	window.display();
}

/**
  * Displays each cell in m_CellMap
  *
  */
void CellMap::render()
{
	for (int col = 0; col < m_Columns; ++col)
	{
		for (int row = 0; row < m_Rows; ++row)
		{
			window.draw(m_CellMap[col][row].getRectangle());
		}
	}
}

/**
  * Sets the state of every cell in m_CellMap to DEAD
  *
  */
void CellMap::deadState()
{
	for (int col = 0; col < m_Columns; ++col)
	{
		for (int row = 0; row < m_Rows; ++row)
		{
			m_CellMap[col][row].setState(false);
		}
	}
}

/**
  * Generates the initial state of m_CellMap
  *
  */
void CellMap::initialState()
{
	for (int col = 0; col < m_Columns; ++col)
	{
		for (int row = 0; row < m_Rows; ++row)
		{
			m_CellMap[col][row].addCell((m_Size / 2) + m_Size * col, (m_Size / 2) + m_Size * row, m_Size, m_Size);

			// If the random integer is less than/equal to 50,
			// the cell state is set to ALIVE, otherwise it is set to DEAD
			int rand = random(1, 100);
			rand <= 50 ? m_CellMap[col][row].setState(true) : m_CellMap[col][row].setState(false);
		}
	}
}

/**
  * Generates the next state of m_CellMap
  *
  */
void CellMap::nextState()
{
	for (int col = 0; col < m_Columns; ++col)
	{
		for (int row = 0; row < m_Rows; ++row)
		{
			bool state = m_CellMap[col][row].getState();
			int neighbors = countCells(col, row); // Counts the cells surrounding neighbors

			if (state) // If alive
			{
				// If neigbors is less than 2 or greater than 3
				// the cell tempState is set to DEAD, otherwise it is set to ALIVE
				neighbors < 2 || neighbors > 3 ? m_CellMap[col][row].tempState = false : m_CellMap[col][row].tempState = true;
			}
			else if (!state) // Otherwise
			{
				// If neigbors is equal to 3
				// the cell tempState is set to ALIVE, otherwise it is set to DEAD
				neighbors == 3 ? m_CellMap[col][row].tempState = true : m_CellMap[col][row].tempState = false;
			}
		}
	}

	// The cells isAlive value is set to the cells current tempState value
	for (int col = 0; col < m_Columns; ++col)
	{
		for (int row = 0; row < m_Rows; ++row)
		{
			m_CellMap[col][row].setState(m_CellMap[col][row].tempState);
		}
	}
}

/**
  * Counts the number of surrounding cells that are ALIVE
  *
  * @param col Current column value
  * @param row Current row value
  *
  * @return Number of alive cells
  *
  */
int CellMap::countCells(int col, int row)
{
	int alive = 0;

	// Iterates through the immediate surrounding cells
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (!(i == 0 && j == 0) && checkBounds(col + i, row + j) && m_CellMap[col + i][row + j].getState())
			{
				alive++;
			}
		}
	}

	return alive;
}

/**
  * Ensures we are not stepping outside of the array bounds
  *
  * @param col Current column value
  * @param row Current row value
  *
  * @return TRUE if we are within the arrays bounds, FALSE if not
  *
  */
bool CellMap::checkBounds(int col, int row)
{
	return ((col >= 0 && col < m_Columns) && (row >= 0 && row < m_Rows));
}

/**
  * Handles the users input
  *
  */
void CellMap::input()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::P) // Pause simulation
			{
				paused = !paused;
			}
			else if (event.key.code == sf::Keyboard::C) // Clear screen
			{
				deadState();
			}
			else if (event.key.code == sf::Keyboard::I) // Generate random state
			{
				if (paused)
				{
					initialState();
				}
			}
			else if (event.key.code == sf::Keyboard::Right) // Next state
			{
				if (paused)
				{
					nextState();
				}
			}
			else if (event.key.code == sf::Keyboard::Escape) // Exit key
			{
				window.close();
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (paused)
			{
				int mouseY = double(event.mouseButton.y) / m_Size - 0.5; // Mouse Y coordinate
				int mouseX = double(event.mouseButton.x) / m_Size - 0.5; // Mouse X coordinate

				// If mouse pointer is within the array bounds
				if (checkBounds(mouseY, mouseX))
				{
					// If left click, the cell state is ALIVE
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						m_CellMap[mouseY][mouseX].setState(true);
					}
					// If right click, the cell state is DEAD
					else if (event.mouseButton.button == sf::Mouse::Right)
					{
						m_CellMap[mouseY][mouseX].setState(false);
					}
				}
			}
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

/**
  * Starts the simulation
  *
  * @param width The window width
  * @param width The window height
  *
  */
void CellMap::start(int width, int height)
{
	initialise(width, height);

	initialState();
	render();

	while (window.isOpen())
	{
		input();

		generate();
	}
}
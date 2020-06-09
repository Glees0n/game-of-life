#include "Util.h"

// Random integer
int random(int min, int max)
{
	return rand() % (max + 1 - min) + min;
}

std::string setColour(const uint8_t colour, const std::string str)
{
	return "\x1b[0;38;5;" + std::to_string(colour) + "m" + str + "\x1b[0m";
}

// Red string
std::string red(const std::string str)
{
	const uint8_t colour = 1;
	return setColour(colour, str);
}

// Green string
std::string green(const std::string str)
{
	const uint8_t colour = 2;
	return setColour(colour, str);
}

// Console introductory text
void start()
{
	std::cout << red("ESC") << "\t\t: Exit" << "\n";
	std::cout << red("P") << "\t\t: Play/Pause" << "\n";
	std::cout << red("C") << "\t\t: Clear" << "\n";
	std::cout << red("I") << "\t\t: Generate Random State" << "\n";
	std::cout << red("RightArrow") << "\t: Next State" << "\n";
	std::cout << red("MouseLeft") << "\t: Place Tile" << "\n";
	std::cout << red("MouseRight") << "\t: Remove Tile" << "\n";

	int width;
	int height;

	std::cout << "\n";
	std::cout << green("Window Width\t: "); std::cin >> width;
	std::cout << green("Window Height\t: "); std::cin >> height;

	CellMap cellmap;
	cellmap.start(width, height);
}
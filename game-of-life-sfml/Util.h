#include <iostream>
#include <string>
#include <time.h>

#include "CellMap.h"

int random(int min, int max); // Generates a random integer

std::string setColour(const uint8_t colour, const std::string str); // Formats a coloured string
std::string red(const std::string str); // Outputs a red string
std::string green(const std::string str); // Outputs a green string

void start();
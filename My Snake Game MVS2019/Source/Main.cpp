//#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Application.h"

using namespace sf;

int main()
{
	//Adjusting window size and segments size of the field
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	const int ARENA_SEGMENT_SIZE = 40;

	Application snake(WINDOW_WIDTH, WINDOW_HEIGHT, ARENA_SEGMENT_SIZE);

	snake.run();
	
}
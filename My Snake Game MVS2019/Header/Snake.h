#include <SFML/Graphics.hpp>
#include <sstream>
#include "Arena.h"


class Snake
{
public:

	enum class Direction
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	Snake(RenderWindow& rWindow, Arena& rArena, Text& rScoreText, int windowWidth, int windowHeight, int blockSize);

	bool update(Time dt, Event& rEvent);

	void draw();

	void restart();

private:
	void bodySegmentsShift();

	RenderWindow& mRWindow;

	Arena& mRArena;

	vector<RectangleShape> mBody;

	int mWindowWidth;
	int mWindowHeight;

	int mBlockWidth;
	int mBlockHeight;

	int mBodySegments;

	int mBlockSize;

	int mScore;

	Time mTimeSinceLastUpdate;
	Time mUpdateRate;

	Text& mRScoreText;

	Direction mDirection;
};



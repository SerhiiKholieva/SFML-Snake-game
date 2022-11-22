#include "Arena.h"


//Arena::Arena()
//{

//}

Arena::Arena(RenderWindow& rWindow, int windowWidth, int windowHeight, int blockSize)
: mRWindow(rWindow)
, mWindowHeight(windowHeight)
, mWindowWidht(windowWidth)
, mBlockSize(blockSize)
, mBlockWidth(windowWidth / blockSize)
, mBlockHeight(windowHeight / blockSize)
, mApple(RectangleShape(Vector2f(blockSize, blockSize)))
, mAppleTimer(Time::Zero)
, mAppleLifetime(sf::seconds(12.0f))
{
	mApple.setFillColor(Color::Cyan);
	mApple.setPosition(Vector2f((mBlockWidth / 2 + 2) * mBlockSize, (mBlockHeight / 2 + 2) * mBlockSize));

	//Setting the grid
	//Set up the horizontal lines
	int horizontaLines = mBlockHeight + 1;
	
	for (int i = 0; i < horizontaLines; i++)
	{
		mGridHorizontalLines.push_back(RectangleShape());
		mGridHorizontalLines[i].setSize(Vector2f(mWindowWidht, 1.0f));
		mGridHorizontalLines[i].setFillColor(Color::Red);
		mGridHorizontalLines[i].setPosition(Vector2f(0.0f, mBlockSize * i));
	}

	//Set up the verrtical lines
	int verticalLines = mBlockWidth + 1;

	for (int i = 0; i < verticalLines; i++)
	{
		mGridWerticalLines.push_back(RectangleShape());
		mGridWerticalLines[i].setSize(Vector2f(1.0f, mWindowHeight));
		mGridWerticalLines[i].setFillColor(Color::Red);
		mGridWerticalLines[i].setPosition(Vector2f(mBlockSize * i, 0.0f));
	}
}



void Arena::update(Time dt)
{
	mAppleTimer += dt;

	if (mAppleTimer > mAppleLifetime)
		spawnApple();
}



void Arena::draw()
{
	//Draw grid
	int horizontaLines = mBlockHeight + 1;
	for (int i = 0; i < horizontaLines; i++)
		mRWindow.draw(mGridHorizontalLines[i]);

	int verticalLines = mBlockWidth + 1;
	for (int i = 0; i < verticalLines; i++)
		mRWindow.draw(mGridWerticalLines[i]);

	mRWindow.draw(mApple);
}


void Arena::spawnApple()
{
	srand((int)time(0));
	float xPosition = (rand() % mBlockWidth) * mBlockSize;
	float yPosition = (rand() % mBlockHeight) * mBlockSize;


	mApple.setPosition(Vector2f(xPosition, yPosition));

	mAppleTimer = Time::Zero;
}


FloatRect Arena::getApplePosition()
{
	return mApple.getGlobalBounds();
}



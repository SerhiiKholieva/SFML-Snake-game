#include "Snake.h"


Snake::Snake(RenderWindow& rWindow, Arena& rArena, Text& mScoreText, int windowWidth, int windowHeight, int blockSize)
: mRWindow(rWindow)
, mRArena(rArena)
, mWindowHeight(windowHeight)
, mWindowWidth(windowWidth)
, mBlockSize(blockSize)
, mBlockWidth(windowWidth / blockSize)
, mBlockHeight(windowHeight / blockSize)
, mBodySegments(3)
, mDirection(Direction::RIGHT)
, mTimeSinceLastUpdate(Time::Zero)
, mUpdateRate(sf::milliseconds(230))
, mRScoreText(mScoreText)
, mScore(0)
{
	for (int i = 0; i < mBodySegments; i++)
	{
		mBody.push_back(RectangleShape(Vector2f(mBlockSize, mBlockSize)));
		mBody[i].setFillColor(Color::Green);
	}

	//Set start position of the snake horizontally approximately in the cehter of  the arena
	mBody[0].setPosition(Vector2f(mBlockWidth / 2 * mBlockSize, mBlockHeight / 2 * mBlockSize));
	mBody[1].setPosition(Vector2f((mBlockWidth / 2 - 1) * mBlockSize, mBlockHeight / 2 * mBlockSize));
	mBody[2].setPosition(Vector2f((mBlockWidth / 2 - 2) * mBlockSize, mBlockHeight / 2 * mBlockSize));
}



bool Snake::update(Time dt, Event& rEvent)
{
	if (rEvent.type == Event::KeyPressed)
	{
		if (rEvent.key.code == Keyboard::Up)
		if (mDirection != Direction::DOWN)
			mDirection = Direction::UP;

		if (rEvent.key.code == Keyboard::Down)
		if (mDirection != Direction::UP)
			mDirection = Direction::DOWN;

		if (rEvent.key.code == Keyboard::Right)
		if (mDirection != Direction::LEFT)
			mDirection = Direction::RIGHT;

		if (rEvent.key.code == Keyboard::Left)
		if (mDirection != Direction::RIGHT)
			mDirection = Direction::LEFT;
	}

	mTimeSinceLastUpdate += dt;

	if (mTimeSinceLastUpdate > mUpdateRate)
	{
		Vector2f lastSegmentPosition(mBody[mBodySegments - 1].getPosition());

		if (mDirection == Direction::UP)
		{
			bodySegmentsShift();
			mBody[0].setPosition(Vector2f(mBody[0].getPosition().x, mBody[0].getPosition().y - mBlockSize));

			if (mBody[0].getPosition().y < 0)
				mBody[0].setPosition(Vector2f(mBody[0].getPosition().x, mBlockHeight * mBlockSize));
		}

		if (mDirection == Direction::DOWN)
		{
			bodySegmentsShift();
			mBody[0].setPosition(Vector2f(mBody[0].getPosition().x, mBody[0].getPosition().y + mBlockSize));

			if (mBody[0].getPosition().y + mBlockSize > mWindowHeight)
				mBody[0].setPosition(Vector2f(mBody[0].getPosition().x, 0.0f));
		}

		if (mDirection == Direction::RIGHT)
		{
			bodySegmentsShift();
			mBody[0].setPosition(Vector2f(mBody[0].getPosition().x + mBlockSize, mBody[0].getPosition().y));

			if (mBody[0].getPosition().x + mBlockSize > mWindowWidth)
				mBody[0].setPosition(Vector2f(0.0f, mBody[0].getPosition().y));
		}

		if (mDirection == Direction::LEFT)
		{
			bodySegmentsShift();
			mBody[0].setPosition(Vector2f(mBody[0].getPosition().x - mBlockSize, mBody[0].getPosition().y));

			if (mBody[0].getPosition().x < 0)
				mBody[0].setPosition(Vector2f(mBlockWidth * mBlockSize, mBody[0].getPosition().y));
		}

		if (mBody[0].getGlobalBounds().findIntersection(mRArena.getApplePosition()))
		{
			mBody.push_back(RectangleShape(Vector2f(mBlockSize, mBlockSize)));
			mBody.back().setFillColor(Color::Green);
			mBody.back().setPosition(lastSegmentPosition);

			mBodySegments++;

			mRArena.spawnApple();

			mScore += 10;

			std::stringstream ss;
			ss << "Score " << mScore;
			mRScoreText.setString(ss.str());
		}

		for (int i = 1; i < mBodySegments; i++)
			if (mBody[0].getGlobalBounds().findIntersection(mBody[i].getGlobalBounds()))
			{
				return true;
			}

		mTimeSinceLastUpdate = Time::Zero;
	}

	return false;
}


void Snake::draw()
{
	for (int i = 0; i < mBodySegments; i++)
		mRWindow.draw(mBody[i]);
}


void Snake::bodySegmentsShift()
{
	for (int i = mBodySegments - 1; i >= 1; i--)
		mBody[i].setPosition(mBody[i - 1].getPosition());
}


void Snake::restart()
{
	mScore = 0;
	mRScoreText.setString("Score 0");
	mBodySegments = 3;

	mBody.clear();

	for (int i = 0; i < mBodySegments; i++)
	{
		mBody.push_back(RectangleShape(Vector2f(mBlockSize, mBlockSize)));
		mBody[i].setFillColor(Color::Green);
	}

	//Set start position of the snake horizontally approximately in the cehter of  the arena
	mBody[0].setPosition(Vector2f(mBlockWidth / 2 * mBlockSize, mBlockHeight / 2 * mBlockSize));
	mBody[1].setPosition(Vector2f((mBlockWidth / 2 - 1) * mBlockSize, mBlockHeight / 2 * mBlockSize));
	mBody[2].setPosition(Vector2f((mBlockWidth / 2 - 2) * mBlockSize, mBlockHeight / 2 * mBlockSize));

	mRArena.spawnApple();
}
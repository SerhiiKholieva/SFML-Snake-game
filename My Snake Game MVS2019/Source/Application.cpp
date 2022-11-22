#include <Application.h>


Application::Application(int windowWidth, int windowHeight, int arenaSegmentSize)
: mWindowWidht(windowWidth)
, mWindowHeght(windowHeight)
, mBlockSize(arenaSegmentSize)
, mWindow(VideoMode(Vector2u(windowWidth, windowHeight)), "Snake!!")
, mArena(mWindow, windowWidth, windowHeight, arenaSegmentSize)
, mSnake(mWindow, mArena, mScoreText, windowWidth, windowHeight, arenaSegmentSize)
, mDt(Time::Zero)
, mPaused(true)
{
	mFont.loadFromFile("fonts/DS-DIGI.ttf");

	mGameOverText.setFont(mFont);
	mGameOverText.setCharacterSize(mBlockSize);
	mGameOverText.setFillColor(Color::Red);
	mGameOverText.setString("Press Enter to start");
	FloatRect textRect = mGameOverText.getLocalBounds();
	mGameOverText.setOrigin(Vector2f(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f));
	mGameOverText.setPosition(Vector2f(mWindowWidht / 2, mWindowHeght / 2));
	
	mScoreText.setFont(mFont);
	mScoreText.setCharacterSize(mBlockSize);
	mScoreText.setFillColor(Color::Cyan);
	mScoreText.setString("Score 0");
	mScoreText.setPosition(Vector2f(0.0f, 0.0f));

	mClock = Clock();
	//mArena(mWindow, mWindowWidht, mWindowHeght, mBlockSize);
}


void Application::clearWindow()
{
	mWindow.clear();
}


void Application::update(Event& rEvent)
{
	mDt = mClock.restart();

	mArena.update(mDt);

	if (mSnake.update(mDt, rEvent))
	{
		mPaused = true;

		mGameOverText.setString("Game Over! Press Enter to restart");
	}
}


void Application::draw()
{
	mSnake.draw();
	mArena.draw();

	mWindow.draw(mScoreText);

	if (mPaused)
		mWindow.draw(mGameOverText);	
}


void Application::display()
{
	mWindow.display();
}


void Application::run()
{
	while (mWindow.isOpen())
	{
		Event event;
		while (mWindow.pollEvent(event))
		{
			if (mPaused)
			{
				if (event.type == Event::KeyPressed)
					if (event.key.code == Keyboard::Enter)
					{
						mPaused = false;

						mSnake.restart();
					}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			mWindow.close();

		clearWindow();

		if (!mPaused)
			update(event);

		draw();
		display();
	}
}
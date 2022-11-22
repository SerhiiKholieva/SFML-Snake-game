#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Arena.h"
#include "Snake.h"

using namespace sf;


class Application
{
	public:
					 Application(int windowWidth, int windowHeight, int arenaSegmentSize);

		void		 run();

	private:
		void		 clearWindow();
		void		 update(Event& rEvent);
		void		 draw();
		void		 display();


		RenderWindow mWindow;

		Clock		 mClock;

		Arena		 mArena;

		Snake		 mSnake;

		Font		 mFont;
		Text		 mGameOverText;
		Text		 mScoreText;

		Time		 mDt;

		int			 mScore;

		int		     mWindowWidht;
		int		     mWindowHeght;

		//Set size of an arena segment
		int		     mBlockSize;

		bool		 mPaused;
};
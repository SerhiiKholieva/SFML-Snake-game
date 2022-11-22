#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Arena
{
	public:
		//					   Arena();

							   Arena(RenderWindow& rWindow, int windowWidth, int windowHeight, int blockSize);

		void				   update(Time dt);
		void				   draw();

		void				   spawnApple();

		FloatRect		       getApplePosition();

	private:
		//Window size in pixels
		int				   mWindowWidht;
		int				   mWindowHeight;

		//Window size in blocks quantity
		int				   mBlockWidth;
		int				   mBlockHeight;

		int			       mBlockSize;

		Time			   mAppleTimer;
		Time			   mAppleLifetime;

		RectangleShape        mApple;

		//Arrays for grid drawing
		vector<RectangleShape> mGridHorizontalLines;
		vector<RectangleShape> mGridWerticalLines;

		RenderWindow&		   mRWindow;
};

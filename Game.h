#pragma once
//Game class
class Game
{
	public:
							Game();
		void				 run();
		

	private:
		void				processEvents();
		void				update(sf::Time deltaTime);
		void				render();
		void				handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		void				handlePlayerMouse(sf::Mouse::Button button, bool isPressed);


	private:
		sf::RenderWindow	mWindow;
		sf::Sprite			mPlayer;
		sf::Sprite			mSprite;
		sf::Texture			mTexture;
		sf::Texture			mTexture2;
		bool				mIsMovingUp;
		bool				mIsMovingDown;
		bool				mIsMovingLeft;
		bool				mIsMovingRight;
		int					counter;
		const sf::Time		TimePerFrame;
		const float			PlayerSpeed;
		bool				mIsMouseLeftDown;
		bool				mIsMouseRightDown;
		int					windowX;
		int					windowY;

		//for trsanslating the screen
		bool				moveScreenRight;
		bool				moveScreenLeft;
		bool				moveScreenUp;
		bool				moveScreenDown;
		sf::Sprite			spriteList[30]; 
		
};
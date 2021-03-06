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
		void				spriteMenu();


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
		bool				addToMap;
		bool				zoomIn, zoomOut;
		int					windowX;
		int					windowY;

		//for trsanslating the screen
		bool				moveScreenRight;
		bool				moveScreenLeft;
		bool				moveScreenUp;
		bool				moveScreenDown;
		
		sf::Sprite*			spriteList[30]; 
		sf::Sprite			tile[100];
		sf::Sprite			objects[100];
		sf::Texture			tileTex[100];

		int					numTiles;
		int					numSprites;
		int					numObjects;
		

		
};
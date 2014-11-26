#include <SFML/Graphics.hpp>
#include "resources.cpp";



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
		sf::Texture			mTexture;
		bool				mIsMovingUp;
		bool				mIsMovingDown;
		bool				mIsMovingLeft;
		bool				mIsMovingRight;
		int					counter;
		const sf::Time		TimePerFrame;
		const float			PlayerSpeed;
		bool				mIsMouseLeftDown;
		bool				mIsMouseRightDown;
		
};

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, mPlayer()
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
	, mIsMouseLeftDown(false)
	, mIsMouseRightDown(false)
	, mTexture()
	, TimePerFrame(sf::seconds(1.f / 60.f))
	, PlayerSpeed(100.0f)
	{
		TextureHolder texHolder;

		texHolder.load(Textures::Character, "Media/head.png");

		
		mPlayer.setPosition(100.f, 100.f);
		mTexture = texHolder.get(Textures::Character);
		

		mPlayer.setTexture(mTexture);
		
		
	}
	void Game::run()
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (mWindow.isOpen())
		{
			processEvents();
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				processEvents();
				update(TimePerFrame);
			}
		render();
		}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	

	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	
}

void Game::handlePlayerMouse(sf::Mouse::Button button, bool isPressed)
{
	

	if (button == sf::Mouse::Left)
	{
		mIsMouseLeftDown = isPressed;
	}
	else if (button == sf::Mouse::Right)
	{
		mIsMouseRightDown = isPressed;
	}
	
	
}


void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch(event.type)
		{
			
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				handlePlayerMouse(event.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				handlePlayerMouse(event.mouseButton.button, false);
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	//added mouse follow
	if (mIsMouseLeftDown)
	{
		sf::Vector2f texXY(mTexture.getSize());
		sf::Vector2f mouseXY(sf::Mouse::getPosition());

		mPlayer.setPosition(mouseXY.x - texXY.x, mouseXY.y - texXY.y);
	}
	
	mPlayer.move(movement * deltaTime.asSeconds());

}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

int main()
{
	Game game;
	game.run();
}
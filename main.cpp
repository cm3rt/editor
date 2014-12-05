#include <SFML/Graphics.hpp>
#include "resources.cpp";
#include "parse_file.cpp";
#include "Game.h";


Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, mPlayer()
	, mSprite()
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
	, mIsMouseLeftDown(false)
	, mIsMouseRightDown(false)
	, moveScreenRight(false)
	, moveScreenLeft(false)
	, moveScreenUp(false)
	, moveScreenDown(false)
	, mTexture()
	, mTexture2()
	, TimePerFrame(sf::seconds(1.f / 60.f))
	, PlayerSpeed(100.0f)
	, windowX(0)
	, windowY(0)
	{
		TextureHolder texHolder;
		texHolder.load(Textures::Character, "Media/head.png");
		mTexture = texHolder.get(Textures::Character);
		mPlayer.setTexture(mTexture);
		mPlayer.setPosition(100.f, 100.f);
		
		texHolder.load(Textures::Logo, "Media/logo.png");
		mSprite.setPosition(20.0f, 20.0f);
		mTexture2 = texHolder.get(Textures::Logo);
		mSprite.setTexture(mTexture2);
		
		spriteList[0] = mPlayer;
		spriteList[1] = mSprite;
		/*this should be used to load all local resources
		  this may have to change considering it's static and we're
		  going to have to load and unload resources constantly
		  but then again, this is only a map editor
		*/

		/*
		  also, should use parse_file.cpp to load the filenames into the texHolder
		*/
		
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
	else if (key == sf::Keyboard::Right)
		moveScreenRight = isPressed;
	else if(key == sf::Keyboard::Left)
		moveScreenLeft = isPressed;
	else if(key == sf::Keyboard::Up)
		moveScreenUp = isPressed;
	else if(key == sf::Keyboard::Down)
		moveScreenDown = isPressed;
		
	

	
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
	sf::Vector2f screenMove(0.f, 0.f);
	
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	if (moveScreenUp){
		screenMove.y -= 100;
		windowY -= 100;
	}
	if (moveScreenDown){
		screenMove.y += 100;
		windowY += 100;
	}
	if (moveScreenLeft){
		screenMove.x -= 100;
		windowX -= 100;
	}
	if (moveScreenRight){
		screenMove.x += 100;
		windowX += 100;
	}

	//added mouse follow
	if (mIsMouseLeftDown)
	{
		sf::Vector2f texXY(mTexture.getSize());
		sf::Vector2f mouseXY(sf::Mouse::getPosition());

		mPlayer.setPosition(mouseXY.x - texXY.x, mouseXY.y - texXY.y);
	}
	
	mPlayer.move(movement * deltaTime.asSeconds());
	mPlayer.move(screenMove * deltaTime.asSeconds());
	mSprite.move(screenMove * deltaTime.asSeconds());
	 
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.draw(mSprite);
	mWindow.display();
}

int main()
{
	Parser p;
	Game game;
	game.run();
}
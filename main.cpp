#include <SFML/Graphics.hpp>
#include "resources.cpp"
#include "parse_file.cpp"
#include "Game.h"
#include "tinyxml2.h"


Game::Game()
	: mWindow(sf::VideoMode(800, 600), "Map Editor")
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
	, tile()
	, tileTex()
	, numTiles(0)
	, numSprites(0)
	, objects()
	, numObjects(0)
	, addToMap(false)
	, zoomIn(false)
	, zoomOut(false)
	{
		//create a texture resource manager
		ResourceHolder<sf::Texture, Textures::ID> texHolder; 
		//load a texture under the name Character and set its position
		texHolder.load(Textures::Character, "Media/tiles/tent.png");
		mTexture = texHolder.get(Textures::Character);
		mPlayer.setTexture(mTexture);
		mPlayer.setPosition(100.f, 100.f);

		//load the map tile menu
		spriteMenu();
		
		//load the logo for the top left
		texHolder.load(Textures::Logo, "Media/logo.png");
		mSprite.setPosition(20.0f, 20.0f);
		mTexture2 = texHolder.get(Textures::Logo);
		mSprite.setTexture(mTexture2); //(Doesn't work this way)
		//mSprite.setTexture(texHolder.get(Textures::Logo)); (Doesn't work this way)
		
		//the sprite list holds the map objects
		spriteList[0] = &mPlayer;
		spriteList[1] = &mSprite;
		numSprites = 2;
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
		//make sure the frames are rendered equally
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
	else if(key == sf::Keyboard::Return)
		addToMap = isPressed;
	else if(key == sf::Keyboard::Z)
		zoomIn = isPressed;
	else if(key == sf::Keyboard::X)
		zoomOut = isPressed;


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
		screenMove.y -= 200;
	}
	if (moveScreenDown){
		screenMove.y += 200;
	}
	if (moveScreenLeft){
		screenMove.x -= 200;
	}
	if (moveScreenRight){
		screenMove.x += 200;
	}


	//added mouse follow
	if (mIsMouseLeftDown)
	{
		sf::Vector2f texXY;
		texXY.x = mPlayer.getGlobalBounds().width;
		texXY.y = mPlayer.getGlobalBounds().height;
		sf::Vector2f mouseXY(sf::Mouse::getPosition());

		//set mPlayer's sprite as the tile clicked on
		for (int counter = 0; counter < numTiles; counter++)
		{
			
			if (((mouseXY.x - mWindow.getPosition().x) > tile[counter].getGlobalBounds().left)
				&& ((mouseXY.x -mWindow.getPosition().x) < tile[counter].getGlobalBounds().left + tile[counter].getGlobalBounds().width)
				&& ((mouseXY.y - mWindow.getPosition().y) > tile[counter].getGlobalBounds().top)
				&& ((mouseXY.y - mWindow.getPosition().y) < tile[counter].getGlobalBounds().top + tile[counter].getGlobalBounds().height))
			{
				
				mPlayer.setTexture(*tile[counter].getTexture(), true);
				mPlayer.setScale(tile[counter].getScale());
			}
			
		}


		mPlayer.setPosition(mouseXY.x -mWindow.getPosition().x - texXY.x/2, mouseXY.y -mWindow.getPosition().y - texXY.y/2);
	}

	//add the object in its current position to the map
	if (addToMap)
	{
		if (numObjects > 0 && objects[numObjects-1].getPosition() == mPlayer.getPosition())
		{}
		else
		{
			objects[numObjects].setTexture(*mPlayer.getTexture(), true);
			objects[numObjects].setPosition(mPlayer.getPosition().x, mPlayer.getPosition().y);
			objects[numObjects].setScale(mPlayer.getScale().x, mPlayer.getScale().y);
			objects[numObjects].setRotation(mPlayer.getRotation());
			++numObjects;
			//add the sprite to the current position
		}
	}
	if (zoomIn)
	{
		mPlayer.setScale(mPlayer.getScale().x * 1.05, mPlayer.getScale().y * 1.05);
	}
	if (zoomOut)
	{
		mPlayer.setScale(mPlayer.getScale().x * .95, mPlayer.getScale().y * .95);
	}
	
	//move the player with ASDF
	mPlayer.move(movement * deltaTime.asSeconds());
	//move the object tiles
	for (int i = 0; i < numTiles; i++)
	{
		tile[i].move(screenMove * deltaTime.asSeconds());
	}

	//mPlayer.move(screenMove * deltaTime.asSeconds());
	//mSprite.move(screenMove * deltaTime.asSeconds());
	 
}

void Game::render()
{
	mWindow.clear();
	
	for (int i = 0; i <= numObjects; i++){
		mWindow.draw(objects[i]);
	}
	
	for (int i = 0; i < numSprites; i++){
		mWindow.draw(*spriteList[i]);
	}

	for (int i = 0; i <= numTiles; i++){
		mWindow.draw(tile[i]);
	}

	

	mWindow.display();
}

void Game::spriteMenu()
{
	//remove
	int top = 425;
	int left = 0;
	numTiles = 15;
	
		ResourceHolder<sf::Texture, Textures::ID> sprites;
		sprites.load(Textures::House, "Media/tiles/house1.png");
		sprites.load(Textures::House2, "Media/tiles/house2.png");
		sprites.load(Textures::House3, "Media/tiles/house3.png");
		sprites.load(Textures::House4, "Media/tiles/house4.png");
		sprites.load(Textures::House5, "Media/tiles/house5.png");
		sprites.load(Textures::Grass, "Media/tiles/grass.png");
		sprites.load(Textures::Altar, "Media/tiles/altar.png");
		sprites.load(Textures::Bridge, "Media/tiles/bridge.png");
		sprites.load(Textures::Market, "Media/tiles/market.png");
		sprites.load(Textures::Market2, "Media/tiles/market2.png");
		sprites.load(Textures::Table1, "Media/tiles/table1.png");
		sprites.load(Textures::Tent, "Media/tiles/tent.png");
		sprites.load(Textures::Tent2, "Media/tiles/tent2.png");
		sprites.load(Textures::Tent3, "Media/tiles/tent3.png");
		sprites.load(Textures::Building, "Media/tiles/building1.png");
		

		tileTex[0] = sprites.get(Textures::House);
		tileTex[1] = sprites.get(Textures::House2);
		tileTex[2] = sprites.get(Textures::House3);
		tileTex[3] = sprites.get(Textures::House4);
		tileTex[4] = sprites.get(Textures::House5);
		tileTex[5] = sprites.get(Textures::Grass);
		tileTex[6] = sprites.get(Textures::Altar);
		tileTex[7] = sprites.get(Textures::Bridge);
		tileTex[8] = sprites.get(Textures::Market);
		tileTex[9] = sprites.get(Textures::Market2);
		tileTex[10] = sprites.get(Textures::Table1);
		tileTex[11] = sprites.get(Textures::Tent);
		tileTex[12] = sprites.get(Textures::Tent2);
		tileTex[13] = sprites.get(Textures::Tent3);
		tileTex[14] = sprites.get(Textures::Building);

		sf::FloatRect tileRect;

		for (int i = 0; i < numTiles; i++)
		{
			tileTex[i].setSmooth(1);
			tile[i].setTexture(tileTex[i]);
			tile[i].setScale(.5, .5);
			tileRect = tile[i].getGlobalBounds();
			top = mWindow.getSize().y - tileRect.height;
			tile[i].setPosition(left, top);
			
			left+=tileRect.width;
		}
		
		

}

int main()
{	
	Parser p;
	Game game;
	game.run();
}

using namespace tinyxml2;
void XMLTest()
{
	
}
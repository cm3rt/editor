#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>


namespace Textures
{
	enum ID 
	{ 
		Landscape, 
		Character, 
		Bullet, 
		Rocks, 
		Dirt_Path, 
		House, 
		Grass, 
		Bushes,
		River,
		Logo
	};
};

class TextureHolder
{

	public:
		TextureHolder();

	public: //functions
		void					load(Textures::ID id, const std::string& filename);
		sf::Texture&			get(Textures::ID id);


	private: //vars
		std::map<Textures::ID, 
			std::unique_ptr<sf::Texture>> mTextureMap;
	
};

TextureHolder::TextureHolder()
	:
mTextureMap()
{

} 
void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(filename);
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}
sf::Texture& TextureHolder::get(Textures::ID id)
{
	auto found = mTextureMap.find(id);
	return *found->second;
}



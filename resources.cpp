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
		House2,  
		House3,  
		House4,  
		House5, 
		Grass, 
		Bushes,
		River,
		Logo
	};
};

//generic resource manager

template <typename Resource, typename Identifier>
class ResourceHolder
{

	public:
		ResourceHolder();

	public: //functions
		void					load(Identifier id, const std::string& filename);
		Resource&				get(Identifier id);


	private: //vars
		std::map<Identifier, 
			std::unique_ptr<Resource>> mResourceMap;
	
};

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder()
	:
mResourceMap()
{

} 

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	resource->loadFromFile(filename);
	mResourceMap.insert(std::make_pair(id, std::move(resource)));
}



template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	return *found->second;
}



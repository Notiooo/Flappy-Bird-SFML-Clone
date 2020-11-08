#ifndef RESOURCES_H_
#define RESOURCES_H_


// Further declarations
namespace sf
{
	class Texture;
	class Font;
}


/**
* \brief Wide resource identifiers inside the game.
* 
* Here you will find the identifiers of the various resources, which are managed by any (x)Manager.
*/
namespace Resources
{
	/**
	* \brief The identifiers of almost all textures in the game are stored here.
	*
	* As the textures are kept in the map Resources::Textures to std::unique_ptr<sf::Texture>
	* we use the identifiers to easily pull out the textures we need.
	*
	* The TextureManager that allows you to do this should be available in most of the code.
	*/
	enum class Textures
	{
		// Objects
		Bird,
		Bird_Spritesheet,
		Pipe_Green,
		
		// Scene Textures
		Background,
		Ground,

		// GUI
		Instructions,
		Logo_Label,
		Game_Over_Label,
		Get_Ready_Label,

		// SCORE
		Panel_Score,
		Medal_Bronze,
		Medal_Gold,
		Medal_Platinum,
		Medal_Silver,

	};

	/**
	* \brief The identifiers of almost all fonts in the game are stored here.
	*
	* As the fonts are kept in the map Resources::Fonts to std::unique_ptr<sf::Font>
	* we use the identifiers to easily pull out the font we need.
	*
	* The FontManager that allows you to do this should be available in most of the code.
	*/
	enum Fonts
	{
		Flappy_Font,
	};
}

// Further declaration to use aliases
template <typename ResourceType, typename Identifier>
class ResourceManager;

/**
* \brief Very simple alias of ResourceManager, that allows to hold Textures
* 
* Since the ResourceManager is a template function and we intend to use 
* textures frequently in the game, we use an alias to avoid writing too often.
*/
using TextureManager = ResourceManager<sf::Texture, Resources::Textures>;

/**
* \brief Very simple alias of ResourceManager, that allows to hold Fonts
*
* Since the ResourceManager is a template function and we intend to use
* fonts frequently in the game, we use an alias to avoid writing too often.
*/
using FontManager = ResourceManager<sf::Font, Resources::Fonts>;


#endif
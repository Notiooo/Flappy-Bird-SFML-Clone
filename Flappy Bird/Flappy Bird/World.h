#ifndef WORLD_H_
#define WORLD_H_

#include <array>

#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"

#include "Resources/ResourceManager.h"
#include "Resources/Resources.h"
#include "Signals/Signals_Queue.h"
#include "Nodes/Specified Nodes/Bird.h"


// Further declaration
namespace sf
{
	class RenderWindow;
}


/**
* \brief A game world class that includes everything that happens inside the game world.
* 
* It stores the main scene called "root_scene". Draws all objects and
* sets them according to the layers on the main game scene.
*/
class World : private sf::NonCopyable
{
public:

	/**
	* \brief The designer of the game world
	* 
	* In its current state, it calls up a function that reads textures, and creates a scene.
	* @param window The window to which we draw objects.
	* @param bird	The player's object -- the bird that the player controls.
	*/
	World(sf::RenderWindow& window, Bird*& bird);

	/** @return Reference to Queue of Signals */
	Signals_Queue& getSignalQueue();

	/** Removes all objects in the main scene "root_scene" and creates them again. */
	void resetWorld();
	
	// ==== Typical SFML cyclic functions ==== //

	/**
	* Updates the status of all objects inside the game world.
	* @param dt The time elapsed between the previous and the new frame.
	*/
	void update(sf::Time dt);

	/** Draw all objects inside the game world */
	void draw();

	// ==== End of typical SFML cyclic functions ==== //

	/**
	* \brief It checks if there have been any collisions in 
	*		 the game world between the player and the environment.
	* 
	* It checks for collisions on each scene between players. 
	* Assigns the type of collision that occurred and assigns 
	* it to a variable inside the Bird class.
	* @return True if there are collisions between the player and the environment.
	*/
	bool handleCollisions();

private:
	/** Loads textures typical of the game world */
	void loadTextures();

	/** Creates a scene by drawing each object one by one and 
	assigning it to the appropriate values of the scene. */
	void createScene();
	
	/**
	* \brief This enum allows you to specify the level of drawing.
	* 
	* It can be used to set a certain drawing order so 
	* that some layers are drawn in the right order before others.
	*/
	enum SceneLayer
	{
		Background, // render first
		Middle, // renders second
		Front, // renders third
		Number_of_Layers // counter of layers
	};

	/** Window we should render into */
	sf::RenderWindow& window;
	
	/** The camera we look through */
	sf::View camera;

	/** Place where textures are stored */
	TextureManager textures;

	/** The root scene we put "things on" */
	NodeScene root_scene;

	/** An array that hold all the layers as pointer to the scenes*/
	std::array<NodeScene*, Number_of_Layers> sceneLayers;

	/** Queue with signal across all the game*/
	Signals_Queue signal_queue;

	/** 
	* \brief The player - It is created here to be available in the class area
	* 
	* Originally, it is dynamically allocated inside the class forming the scene.
	* Declared here allows you to use it inside and outside this class.
	* @return Reference to the bird -- player's object
	*/
	Bird*& thePlayer;

	/**
	* \brief It describes as a percentage the floor of the game world on which Y is located
	*
	* For 0.85 the floor will take up 15% of the space at the bottom of the screen.
	*/
	float GroundLevel;


};


#endif
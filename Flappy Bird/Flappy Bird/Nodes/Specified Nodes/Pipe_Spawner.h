#ifndef PIPE_SPAWNER_H_
#define PIPE_SPAWNER_H_

#include <memory>
#include <deque>

#include "Pipe.h"
#include "Coin.h"


/** 
* A pipe generator which, based on the given parameters, 
* generates pipes at appropriate speed and at appropriate intervals
* 
* Pipe Spawner should have been placed in (0,0) (left up corner of the screen) 
*/
class Pipe_Spawner : public NodeScene
{
public:
	/**
	* Initializes all variables
	* @param textures The Texture Manager that hold the textures
	* @param spawn_position Position at which the pipes should be generated
	* @param thePlayer Reference to the object of the bird, which the player controls.
	*/
	Pipe_Spawner(const TextureManager& textures, sf::Vector2f spawn_position, Bird& thePlayer);

	/** This function makes the generator start to generate pipes */
	void start_spawning();

	/** This function makes the generator stop to generate pipes */
	void stop_spawning();

	/**
	* Returns a category of this specific node used for signals and colisions
	* @return Category of this object
	*/
	virtual unsigned int getCategory() const override;

protected:
	/** What should be the space between the pipes in the Y axis */
	int offset_Y = 60;

	/** What space should be on X axis between Pipes*/
	int offset_X = 25;

	/** Minimal distance between pipes */
	int distance_between_pipes = 35;

	/** How fast spawned pipes move */
	float scrollingSpeed = 30.2f;

private:
	/* Spawn new pipes */
	void spawnPipes();

	/**
	* Updates the status of this state (informations in it)
	* @param dt The time elapsed between the previous and the new frame.
	* @return If false, this is information to stop the update on the lower layers of the stack.
	*/
	virtual void updateThis(sf::Time dt);

	/** Deque of all created pipes, so we can track them*/
	std::deque<Pipe*> list_of_pipes;

	/** Text Manager containing the textures*/
	const TextureManager& textures;

	/** Position at which we spawn the pipes */
	sf::Vector2f spawn_position;

	/** Reference to the object of the bird, which the player controls. */
	Bird& thePlayer;

	/** Flag saying if the generator spawns pipes */
	bool spawning = false;
};


#endif // ! PIPE_SPAWNER_H_

#ifndef STATES_LIST_H_
#define STATES_LIST_H_


namespace States
{
	/**
	* \brief Identifications of all states in the game.
	*
	* States in StateStack are stored in map of States::ID to std::function(State_Pointer()).
	* Later on, depending on the States::ID we can create new object of given State by just
	* using its States::ID. Call on std::function(State_Pointer()) returns new object of that state.
	*/
	enum class ID
	{
		None,

		// More "Global" States
		Title,
		Game,
		Pause,
		Score,


		// Birb States
		Flying,
		Flapping,
		Hit,
		Ground

	};
}


#endif
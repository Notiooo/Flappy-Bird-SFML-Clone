#ifndef SIGNAL_CATEGORY_H_
#define SIGNAL_CATEGORY_H_


namespace Signals
{
	/**
	* \brief Signal categories allow to define for which type of object
	*		 a particular signal is intended.
	*
	* Each object can specify its category. When signals are interpreted
	* by objects, then their categories are compared with the category
	* for which the signal is intended. It is then possible to determine
	* whether any category of signal and object overlap and can be linked.
	*/
	enum Category
	{
		None = 0,
		Scene = 1 << 0,
		Player = 1 << 1,
		CollideObject = 1 << 2, // Object from which player should "die" from
		
		Pipe = 1 <<  3,
		Ground = 1 << 4,
		Pipe_Spawner = 1 << 5,
	};
}
#endif
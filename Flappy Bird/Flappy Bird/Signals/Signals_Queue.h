#ifndef SIGNALS_QUEUE_H_
#define SIGNALS_QUEUE_H_

#include <queue>
#include "Signal.h"


/**
* \brief This is a class that acts as a stack or queue of the 
*		 "FIFO" type and allows the storage of signals.
* 
* This queue is being passed on to a huge number of game areas.
* It allows communication of unconnected game objects.
*/
class Signals_Queue
{
	public:
		/** 
		* Pushes the signal to the queue
		* @param signal Signal to be pushed to the queue
		*/
		void push(const Signal& signal);

		/** 
		* Pops the signal from the queue, and returns it 
		* @return The signal that was popped from the queue.
		*/
		Signal pop();

		/** Check if the queue is empty */
		bool isEmpty() const;

	private:
		/** Queue with signals */
		std::queue<Signal> _queue;
};


#endif
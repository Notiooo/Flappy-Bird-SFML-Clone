#include "Signals_Queue.h"

void Signals_Queue::push(const Signal& signal)
{
	_queue.push(signal);
}

Signal Signals_Queue::pop()
{
	Signal signal = _queue.front();
	_queue.pop();
	return signal;
}

bool Signals_Queue::isEmpty() const
{
	return _queue.empty();
}

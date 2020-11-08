#ifndef GENERAL_STATE_H_
#define GENERAL_STATE_H_

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "States_List.h"
#include "../Resources/Resources.h"


// Further declaration of StateStack
template <typename State>
class StateStack;

// Further Declaration (as there are only pointers to this type)
namespace sf
{
	class RenderWindow;
}


/**
* \brief An abstract General_State other states can inherit from.
* 
* This abstract class defines all general behaviours of the State
* like for example:
* 1) request Push -- push given state onto the stack
* 2) request Pop -- pops state from the top of the stack
* 3) request Clear  -- clears the stack
* 
* Also it defines some typical SFML functions like: update, draw
* or handle events.
* 
* @tparam StateType type of the State so it can be a General State
*		of specfic StateStack of given type.
*/
template <typename StateType>
class General_State
{
	public:
		/**
		* Only the statestack is being initialized.
		* @param stack The stack that stores this state
		*/
		General_State(StateStack<StateType>& stack);

		/** Declared for the purpose of correct implementation of the inheritance*/
		virtual ~General_State();


		// ==== Typical SFML cyclic functions ==== //

		/**
		* Updates the status of this state
		* @param dt The time elapsed between the previous and the new frame.
		* @return If false, this is information to stop the update on the lower layers of the stack.
		*/
		virtual bool update(sf::Time dt) = 0;

		/** Draws this state */
		virtual void draw() = 0;

		/**
		* Handles all events for this state
		* @param event Events stored in the window.
		* @return If false, this is information to stop to handle events on the lower layers of the stack.
		*/
		virtual bool handleEvent(const sf::Event& event) = 0;

		// ==== End of typical SFML cyclic functions ==== //


	protected:

		// == Operations related with state == //

		/** 
		* \brief Sends a request to the stack to push the state to the stack. 
		* 
		* Ask for the push -- but it can't do it instantly, because it would be
		* program breaking, so it request for it to be done in next frame.
		* The request lands in the queue, which will be read in the next loop run.
		* @param state The identifier of the state to push onto the stack.
		*/
		void requestStackPush(States::ID state);

		/**
		* \brief Sends a request to the stack to pop state (from the top) from the stack.
		*
		* Ask for the pop -- but it can't do it instantly, because it would be
		* program breaking, so it request for it to be done in next frame.
		* The request lands in the queue, which will be read in the next loop run.
		*/
		void requestStackPop();

		/**
		* \brief Sends a request to clear the stack
		*
		* Ask for the clear -- but it can't do it instantly, because it would be
		* program breaking, so it request for it to be done in next frame.
		* The request lands in the queue, which will be read in the next loop run.
		*/
		void requestStackClear();

		/** Pointer to the stack to which this state belongs. */
		StateStack<StateType>* stack;

};

// ====== THERE IS IMPLEMENTATION (WILL MOVE IT LATER) ======= //

template <typename StateType>
General_State<StateType>::General_State(StateStack<StateType>& stack) :
	stack(&stack)
{
}

template <typename StateType>
General_State<StateType>::~General_State()
{
}

template <typename StateType>
void General_State<StateType>::requestStackPush(States::ID state)
{
	stack->pushState(state);
}

template <typename StateType>
void General_State<StateType>::requestStackClear()
{
	stack->clearStack();
}

template <typename StateType>
void General_State<StateType>::requestStackPop()
{
	stack->popState();
}


#endif
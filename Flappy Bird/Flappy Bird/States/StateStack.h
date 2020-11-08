#ifndef STATESTACK_H_
#define STATESTACK_H_
/** A simpler version of finite state machine called State Stack. Made according to practices in "SFML Game Development Book" */

#include <functional>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>

#include "SFML/System/NonCopyable.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/System/Time.hpp"

#include "States_List.h"


/**
* \brief StateStack that stores states of the game.
* 
* In its overall operation, it allows it to act similarly to
* the behaviour of a stack. Certain states of the game can be 
* overlapped or removed from the stack.
* 
* For example:
* 1) We can have TitleState which displays logo of the company.
* 2) Then TitleState is removed from the stack, and GameState is Pushed
* 3) While the game works, and player is playing we can push PauseState
*	 on the stack. Now PauseState code execute first, and it can (but
*	 do not have to) block layers of stack underneath.
* This way we can easily make PauseState draw transparent darkish
* rectangle on the screen, while GameState underneath is still working,
* or not if we want to block it inside PauseState.
* 
* @tparam StateType type of State we want to put on stack later on.
*	They might define different Data, or parameters that will be passed
*	to the stack.
*/
template <typename StateType>
class StateStack : private sf::NonCopyable
{
public:
	/**
	* \brief All operations that can be performed on our stack.
	*
	* Specifically, these are their identifiers, which easily
	* allow you to send information to the stack about what 
	* operation should be performed.
	*/
	enum Operation
	{
		Push,
		Pop,
		Clear
	};

public:
	/** Easier name for the data the stack transfers to its states. */
	using State_Data = typename StateType::Game_Data;

	/** Easier name on the pointer for the type of state that is stacked. */
	using State_Pointer = typename StateType::Pointer;

	/**
	* At the moment, it only initialize the variables.
	* @param gamedata Information that is transferred to the states at the stake.
	*/
	explicit StateStack(State_Data gamedata);


	// == State operations (similar to std::stack) == //

	/** 
	* Alternative possibility to perform Push operation on the stack.
	* @param state The identifier of the state to push onto the stack.
	*/
	StateStack<StateType>& operator+=(States::ID state);

	/** Alternative possibility to perform Pop operation on the stack. */
	StateStack<StateType>& operator--();

	/**
	* \brief Loads the given state, so it can easily use it later
	*
	* Under a given identifier in the States map::ID to std::function<State_Pointer()> 
	* a callable object is created, which creates a state object for us. 
	* This object is then used by createState(...) to create the state and push it onto the stack.
	* @tparam T A specific state class that inherits from the class that StateStack stores.
	* @param state The name of the identifier that you want to assign to the class of the loaded state.
	*/
	template <typename T>
	void loadState(States::ID state);

	/** 
	* Push the state on the stack (on top of the stack) 
	* @param state The identifier of the state to push onto the stack.
	*/
	void pushState(States::ID state);

	/** Pop the state from the stack (from top of the stack) */
	void popState();

	/** Removes all states from the stack */
	void clearStack();

	/** 
	* Checks if there is any state on the stack.
	* @return True if there is no state on the stack
	*/
	bool isEmpty() const;

	/**
	* Returns collected logs, and cleans them.
	* @return Collected logs since the last getLogs() function was called
	*/
	std::string getLogs();


	
	// ==== Typical SFML cyclic functions ==== //

	/**
	* Updates the status of all states inside the state stack.
	* @param dt The time elapsed between the previous and the new frame.
	*/
	void update(sf::Time dt);

	/** Draw all states inside the stack (calls their draw() method) */
	void draw();

	/** 
	* \brief Handles all events inside the stack. 
	* 
	* Calls a function that handles events in any state present in the stack.
	* @param event Events stored in the window.
	*/
	void handleEvent(const sf::Event& event);

	// ==== End of typical SFML cyclic functions ==== //



	private:
		/** 
		* \brief It creates States and returns pointer to it
		* 
		* Calls a callable object contained in the map states::ID to std::function<State_Pointer()>.
		* It creates and returns a new object of a specified state class.
		* @param state The identifier of the state to create.
		* @return Pointer to the newly create state object
		*/
		State_Pointer createState(States::ID state);

		/** It applies all the changes requested by to the state stack */
		void applyWaitingChanges();


		/* It's the message with information what operation should be done on the stack */
		struct WaitingChange
		{
			/**
			* Creates a new stack change request object.
			* @param operation Operation we should execute onto the stack
			* @param state State in case we want to push a state onto the stack
			*/
			explicit WaitingChange(Operation operation, States::ID state = States::ID::None);

			/** Operation to execute onto the stack */
			Operation operation;
			/** State identificator of state we may want to push onto the stack */
			States::ID state;
		};

		/** The stack holding pointer to states stores on it */
		std::vector<State_Pointer> stack;

		/** A kind of queue with operations waiting to be executed onto the stack*/
		std::vector<WaitingChange> list_of_changes;

		/** Informations we want to send through states of the stack */
		State_Data game_data;

		/** Logs of stack stored inside of the string */
		std::string logs;

		/** 
		* Variable contains a callable lambda that 
		* creates new State, and stores it by its state ID.
		* It works like a factory
		*/
		std::map<States::ID, std::function<State_Pointer()>> state_objects;


};

// ====== THERE IS IMPLEMENTATION (WILL MOVE IT LATER) ======= //

template<typename StateType>
template<typename T>
void StateStack<StateType>::loadState(States::ID state)
{
	// At the key of given State ID we create a callable object that will create 
	// the State object for us. It will be later used in CreateState function
	// that will use this callable object to create a state.
	state_objects[state] = [this]() { return State_Pointer(new T(*this, game_data)); };
}

// INLINE LATER

template <typename StateType>
void StateStack<StateType>::update(sf::Time dt)
{
	// Later on we would like to definetely top layers make to stop
	// make any updates. For example pause state definetely has to
	// dominate and block other, lower layers of state stack
	// thats why if any state will return false, then we stop
	// to iterate further!
	for (auto beg = stack.rbegin(); beg != stack.rend(); ++beg)
	{

		if (!(*beg)->update(dt))
			break;
	}
	applyWaitingChanges();
}

template <typename StateType>
void StateStack<StateType>::draw()
{
	for (auto& state : stack)
	{
		state->draw();
	}
}

template <typename StateType>
void StateStack<StateType>::handleEvent(const sf::Event& event)
{
	// Later on we would like to definetely top layers make to stop
	// take any events. For example pause state definetely has to
	// dominate and block other, lower layers of state stack
	// thats why if any state will return false, then we stop
	// to iterate further!
	for (auto beg = stack.rbegin(); beg != stack.rend(); ++beg)
	{
		if (!(*beg)->handleEvent(event))
			break;
	}
	applyWaitingChanges();
}

template <typename StateType>
typename StateType::Pointer StateStack<StateType>::createState(States::ID state)
{
	// Find the appropriate state to create
	auto found = state_objects.find(state);

	// Return a pointer to the state that will be created by calling
	// the call operator on the lambda inside the state_object variable
	return (found->second)();
}

template <typename StateType>
void StateStack<StateType>::applyWaitingChanges()
{
	for (auto& change : list_of_changes)
	{
		switch (change.operation)
		{
		case Push:
			stack.push_back(createState(change.state));
			logs.append("\nPushed state nr " + std::to_string(static_cast<unsigned int>(change.state)));
			break;
		case Pop:
			stack.pop_back();
			logs.append("\nPopped out a state");
			break;
		case Clear:
			stack.clear();
			logs.append("\nCleared a stack");
			break;
		}
	}
	list_of_changes.clear();
}

template <typename StateType>
StateStack<StateType>::StateStack(State_Data gamedata) :
	stack(),
	list_of_changes(),
	game_data(gamedata),
	state_objects(),
	logs()
{

}

template<typename StateType>
inline StateStack<StateType>& StateStack<StateType>::operator+=(States::ID state)
{
	pushState(state);
	return *this;
}

template<typename StateType>
inline StateStack<StateType>& StateStack<StateType>::operator--()
{
	popState();
	return *this;
}

template <typename StateType>
void StateStack<StateType>::pushState(States::ID state)
{
	list_of_changes.push_back(WaitingChange(Push, state));
}

template <typename StateType>
void StateStack<StateType>::popState()
{
	list_of_changes.push_back(WaitingChange(Pop));
}

template <typename StateType>
void StateStack<StateType>::clearStack()
{
	list_of_changes.push_back(WaitingChange(Clear));
}

template <typename StateType>
bool StateStack<StateType>::isEmpty() const
{
	return stack.empty();
}

template<typename StateType>
inline std::string StateStack<StateType>::getLogs()
{
	if (logs.empty())
		return std::string();

	std::string logs_to_return = "[ " + std::string(typeid(StateType).name()) + " ] " + logs;
	logs.clear();
	return logs_to_return;
}

template <typename StateType>
StateStack<StateType>::WaitingChange::WaitingChange(Operation operation, States::ID state) :
	operation(operation),
	state(state)
{
}


#endif

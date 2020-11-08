template <typename StateType>
General_State<StateType>::General_State(StateStack<General_State>& stack):
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



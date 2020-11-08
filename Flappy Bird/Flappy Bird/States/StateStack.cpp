void StateStack::update(sf::Time dt)
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

void StateStack::draw()
{
	for(auto& state : stack)
	{
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event)
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

State::Pointer StateStack::createState(States::ID state)
{
	// Find the appropriate state to create
	auto found = state_objects.find(state);
	
	// Return a pointer to the state that will be created by calling
	// the call operator on the lambda inside the state_object variable
	return (found->second)();
}

void StateStack::applyWaitingChanges()
{
	for (auto& change : list_of_changes)
	{
		switch (change.operation)
		{
		case Push:
			stack.push_back(createState(change.state));
			break;
		case Pop:
			stack.pop_back();
			break;
		case Clear:
			stack.clear();
			break;
		}
	}
	list_of_changes.clear();
}

StateStack::StateStack(State::Game_Data gamedata):
	stack(),
	list_of_changes(),
	game_data(gamedata),
	state_objects()
{

}
void StateStack::pushState(States::ID state)
{
	list_of_changes.push_back(WaitingChange(Push, state));
}

void StateStack::popState()
{
	list_of_changes.push_back(WaitingChange(Pop));
}

void StateStack::clearStack()
{
	list_of_changes.push_back(WaitingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return stack.empty();
}

StateStack::WaitingChange::WaitingChange(Operation operation, States::ID state): 
	operation(operation), 
	state(state)
{
}

#include "NodeScene.h"
#include "Specified Nodes/Bird.h"

NodeScene::NodeScene():
	pinned_Nodes(),
	_parent(nullptr)
{
}

NodeScene::NodeScene(NodeScene&& rhs) noexcept
{
	pinned_Nodes = std::move(rhs.pinned_Nodes);
	rhs.removePinnedNodes();
		
	_parent = rhs._parent;
	rhs._parent = nullptr;
}

NodeScene& NodeScene::operator=(NodeScene&& rhs) noexcept
{
	if (this != &rhs)
	{
		removePinnedNodes();
		pinned_Nodes = std::move(rhs.pinned_Nodes);
		rhs.removePinnedNodes();

		_parent = rhs._parent;
		rhs._parent = nullptr;
	}
	return *this;
}

void NodeScene::pin_Node(Node node)
{
	// Make this node it's parent
	node->_parent = this;

	// Save the node as the "pinned one"
	pinned_Nodes.push_back(std::move(node));
}

NodeScene::Node NodeScene::unpin_Node(const NodeScene& node)
{

	// Find the scene we want to unpin
	auto found = std::find_if(pinned_Nodes.begin(), pinned_Nodes.end(),
		[&node](Node& node_ptr) { return node_ptr.get() == &node; });

	// Take it out, and remember std::find_if returns an iterator
	Node found_node = std::move(*found);

	// Remove parent of the node, as we unpinned it
	found_node->_parent = nullptr;

	// Erase it from pinned nodes list, as it is not pinned anymore
	pinned_Nodes.erase(found);

	return found_node;

}

void NodeScene::removePinnedNodes()
{
	/*
	while (!pinned_Nodes.empty())
		pinned_Nodes.pop_back();
		*/
	pinned_Nodes.clear();
}

sf::Transform NodeScene::GetAbsoluteTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const NodeScene* node = this; node != nullptr; node = node->_parent)
		transform = node->getTransform() * transform;

	return transform;
}

void NodeScene::update(sf::Time dt)
{
	updateThis(dt);
	updatePinnedNodes(dt);
}

void NodeScene::interpretSignal(const Signal& signal, sf::Time dt)
{
	// Check if we should care about this signal
	if (signal.category_id & getCategory())
	{
		signal.emit(*this, dt);
	}

	// Send it to pinned nodes too
	for (auto &pinned_node : pinned_Nodes)
		pinned_node->interpretSignal(signal, dt);
}

void NodeScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// We want both of them to move in relation to the stage that has been clipped. 
	// For this reason, we calculate the appropriate offset.
	states.transform *= getTransform();

	drawThisNode(target, states);

	for (auto& pinned_node : pinned_Nodes)
	{
		pinned_node->draw(target, states);
	}
}

void NodeScene::drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void NodeScene::updateThis(sf::Time dt)
{
}

void NodeScene::updatePinnedNodes(sf::Time dt)
{
	for (auto& pinned_node : pinned_Nodes)
		pinned_node->update(dt);
}

unsigned int NodeScene::getCategory() const
{
	return Signals::Scene;
}

sf::FloatRect NodeScene::getBoundingRect() const
{
	// It has to be there, even empty so we can iterate through scenes
	return sf::FloatRect();
}

/** Based on "Signals" it gains what type of object collide with the player at the moment*/
unsigned int NodeScene::checkNodeCollision(Bird& bird)
{
	// This kind of check collision should run only on the bird
	unsigned int all_collisions = 0;
	if (getCategory() & Signals::CollideObject)
	{
		if (this->getBoundingRect().intersects(bird.getBoundingRect()))
			all_collisions |= this->getCategory();
	}
	for (Node& node : pinned_Nodes)
	{
		all_collisions |= node->checkNodeCollision(bird);
	}
	return all_collisions;
}

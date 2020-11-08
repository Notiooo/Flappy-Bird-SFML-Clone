#ifndef NODESCENE_H_
#define NODESCENE_H_
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "../Signals/Signal.h"
#include "../Signals/Signals_Category.h"

#include <memory>
#include <vector>

// Further declaration
class Bird;


/**
* \brief The class is a kind of "canvas" on which we can draw certain objects and combine them.
* 
* NodeScene works like a bit more complex canvas and is called a scene for a reason. 
* First of all, you can draw and manage certain objects on the scenes. You can clip 
* other scenes to the scene. Scenes resemble a kind of tree, which can perform 
* operations on scenes that are pinned to them. Also, scenes pinned to another
* subordinate scene move in relation to the subordinate scene.
* 
* Scenes can transmit a signal downwards, so that the signal will be interpreted by
* each of them. It is enough that only one main scene is updated, or drawn, and all
* the scenes pinned to it will also be.
*
*                    +--------+
*                    | Root   |
*                    | Scene  |
*                    ++------++
*                     |      |
*                     v      v
*              +------+-+  +-+------+
*              | Pinned |  | Pinned |
*              | Scene  |  | Scene  |
*        +-----++-------+  +-------++-----+
*        |      |                  |      |
*        v      v                  v      v
* +------+-+  +-+------+    +------+-+  +-+------+
* | Pinned |  | Pinned |    | Pinned |  | Pinned |
* | Scene  |  | Scene  |    | Scene  |  | Scene  |
* +--------+  +--------+    +--------+  +--------+
* 
*/
class NodeScene : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		/** Easier naming on Pointer for this type */
		typedef std::unique_ptr<NodeScene> Node;

	public:
		/** Initializes the scene with default values. */
		NodeScene();
		
		/** I don't want copy-assignment in that type */
		NodeScene(const NodeScene&) = delete;

		/** 
		* Move constructor
		* @param node Node we should steal values from
		*/
		NodeScene(NodeScene&& node) noexcept;

		/**
		* Move assignment operator
		* @param node Node we should steal values from
		*/
		NodeScene& operator=(NodeScene&& node) noexcept;


		/** 
		* It "pins" to itself another node, in other words it attaches it as its child 
		* @param node The node we want to pin to this node.
		*/
		void pin_Node(Node node);

		/** 
		* It "unpins" from itself another node, in other words it deattaches its child
		* @param node The node we want to unpin from this node.
		* @return The unpinned node
		*/
		Node unpin_Node(const NodeScene& node);

		/** Remove all pinned nodes to this node */
		void removePinnedNodes();

		/** It gets absolute transform relative to the window -- not relative to the scene to which it is attached. 
		* @return The global transform of this object
		*/
		sf::Transform GetAbsoluteTransform() const;

		/**
		* Updates the status of this node scene (informations in it)
		* @param dt The time elapsed between the previous and the new frame.
		*/
		void update(sf::Time dt);

		/** 
		* Checks if the signal is for his category, and if so then it interprets it
		* @param signal Signal to be interpreted
		* @param dt The time elapsed between the previous and the new frame.
		*/
		void interpretSignal(const Signal& signal, sf::Time dt);

		/**
		* Give the Rect of the object -- a certain box surrounding this object in size
		* @return The Rect of this object
		*/
		virtual sf::FloatRect getBoundingRect() const;

		/** 
		* Check collision only with the bird  (thats how flappy bird works)
		* @param bird Reference the object of the bird, which the player controls.
		* @return Information on types of collisions
		*/
		unsigned int checkNodeCollision(Bird& bird);

	private:
		/** 
		* Function that allows SFML to draw that object, and all pinned nodes 
		* @param target Canvas on which we draw all objects
		* @param states Any transformations and additional effects (in our case, transformations relative to the scene)
		*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

		/** 
		* Function that prints only elements related to this node 
		* @param target Canvas on which we draw all objects
		* @param states Any transformations and additional effects (in our case, transformations relative to the scene)
		*/
		virtual void drawThisNode(sf::RenderTarget& target, sf::RenderStates states) const;

		/** 
		* Function that updates everything related to this node 
		* @param dt The time elapsed between the previous and the new frame.
		*/
		virtual void updateThis(sf::Time dt);

		/** 
		* Makes sure that all pinned nodes will get updated
		* @param dt The time elapsed between the previous and the new frame.
		*/
		virtual void updatePinnedNodes(sf::Time dt);

		/** 
		* Returns a category of this specific node used for signals and colisions
		* @return Category of this object
		*/
		virtual unsigned int getCategory() const;


	private:
		/** Vector of all pointers that are pinned to this node */
		std::vector<Node> pinned_Nodes;

		/** A node superior to this node */
		NodeScene* _parent;

};


#endif
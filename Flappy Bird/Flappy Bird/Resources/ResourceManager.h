///////////////////////////////////////////
//// This class is based on the design	///
//// of games from the book				///
//// "SFML Game Development".			///
///////////////////////////////////////////


#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <memory>
#include <string>

#include <cassert>
#include <stdexcept>
#include <utility>

/** 
* This class allows us to hold some textures in it, and get them back later.
* I use this function due to the fact that Textures, or sounds are very heavy, 
* and I want to store them once, and them use them multiple times.
* @tparam ResourceType Type of the resource we want to store
* @tparam Identifier The identifiers we want to use when selecting back to our resources.
*/
template<typename ResourceType, typename Identifier>
class ResourceManager
{
	public:
		/** 
		* Loads the resource from the file, and stores it under given identifier name
		* @param group The identifier of the resource under whose name you want to save and read the object.
		* @param file File from which we read a given resource
		*/
		void load_resource(Identifier group, const std::string& file);

		/**
		* Loads the resource from the file, and stores it under given identifier name
		* @tparam Param Additional type that you may want to use when storing the resource.
		* @param group The identifier of the resource under whose name you want to save and read the object.
		* @param file File from which we read a given resource
		* @param param Additional parameter that you may want to use when storing the resource.
		*/
		template <typename Param>
		void load_resource(Identifier group, const std::string& file, const Param& param);

		/**
		* Gives us reference to the resource of given identifier
		* @param id Resource identifier to be read
		* @return Reference to the resource of given identifier
		*/
		ResourceType& get_resource(Identifier id);
			
		/**
		* Gives us reference to the resource of given identifier
		* @param id Resource identifier to be read
		* @return Reference to the resource of given identifier
		*/
		const ResourceType& get_resource(Identifier id) const;

	private:
		/** Identifier coressponds to pointer to given resource*/
		std::map<Identifier, std::unique_ptr<ResourceType>> map_of_resources;
};

#include "ResourceManager.inl"

#endif
template<typename ResourceType, typename Identifier>
void ResourceManager<ResourceType, Identifier>::load_resource(Identifier id, const std::string& file)
{
	// We need to dynamically allocated our resource (for example texture)
	std::unique_ptr<ResourceType> resource(new ResourceType());

	// Now we should check if given file exist
	if (!resource->loadFromFile(file))
		throw std::runtime_error("ResourceManager::load - FAILED TO LOAD the " + file + "\n");

	// Finally enter the record to our map
	// First parameter is the identifier, and the second is a pointer to resource type
	auto inserted = map_of_resources.insert({ id, std::move(resource) });

	// Check if the insertion was okay
	assert(inserted.second);
}

template<typename ResourceType, typename Identifier>
template <typename Param>
void ResourceManager<ResourceType, Identifier>::load_resource(Identifier id, const std::string& file, const Param& param)
{
	// We need to dynamically allocated our resource (for example texture)
	std::unique_ptr<ResourceType> resource(new ResourceType());

	// Now we should check if given file exist
	if (!resource->loadFromFile(file, param))
		throw std::runtime_error("ResourceManager::load - FAILED TO LOAD the " + file + "\n");

	// Finally enter the record to our map
	// First parameter is the identifier, and the second is a pointer to resource type
	auto inserted = map_of_resources.insert({ id, std::move(resource) });

	// Check if the insertion was okay
	assert(inserted.second);
}

template <typename ResourceType, typename Identifier>
ResourceType& ResourceManager<ResourceType, Identifier>::get_resource(Identifier id)
{
	// Try to find the given id
	auto found = map_of_resources.find(id);

	// If it is at the end, then we didn't find it
	assert(found != map_of_resources.end());

	// Return only the value-part (not the key), and derefernce it as
	// we don't want the pointer but the resource
	return *found->second;
}

template <typename ResourceType, typename Identifier>
const ResourceType& ResourceManager<ResourceType, Identifier>::get_resource(Identifier id) const
{
	// Try to find the given id
	auto found = map_of_resources.find(id);

	// If it is at the end, then we didn't find it
	assert(found != map_of_resources.end());

	// Return only the value-part (not the key), and derefernce it as
	// we don't want the pointer but the resource
	return *found->second;
}
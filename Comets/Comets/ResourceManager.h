#pragma once
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	std::vector<Player> _players;
	std::vector<Comet> _comets;
	std::vector<Star> _stars;
};


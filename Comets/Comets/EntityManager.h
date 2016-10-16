#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Comet.h"
#include "Star.h"
class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	std::vector<Player> _players;
	std::vector<Comet> _comets;
	std::vector<Star> _stars;
};


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
	void makeComet();
	void eraseDeadComets();
	void eraseDeadPlayers();
	bool arePlayersAlive();
private:
	template<class SPRITES>
	void eraseDeadSprites(SPRITES &sprites);
	std::vector<std::auto_ptr<Player>> _players;
	std::vector<std::auto_ptr<Comet>> _comets;
	std::vector<std::auto_ptr<Star>> _stars;
};


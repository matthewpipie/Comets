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
	void detectCollision();
private:
	template<class SPRITES>
	void eraseDeadSprites(SPRITES &sprites);
	std::vector<std::unique_ptr<Player>> _players;
	std::vector<std::unique_ptr<Comet>> _comets;
	std::vector<std::unique_ptr<Star>> _stars;
};


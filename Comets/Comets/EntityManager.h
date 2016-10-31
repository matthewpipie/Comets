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
	void clean();
	bool arePlayersAlive();
	void detectCollision();

private:
	void eraseDeadComets();
	void eraseDeadPlayers();

	template<class SPRITES>
	void eraseDeadSprites(SPRITES &sprites);
	void tryToTwinkleStars();
	void moveComets();
	void tryToMakeComet();
	std::vector<Player> _players;
	std::vector<Comet> _comets;
	std::vector<Star> _stars;
};


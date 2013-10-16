#ifndef MANAGERS
#define MANAGERS

#include "Utility.h"
#include "Character.h"

using namespace std;
using namespace sf;

class EnemyManager
{
public:
	EnemyManager() : enemies ( new vector<Enemy>() ) {}

	~EnemyManager()
	{
		delete enemies;
	}

	vector<Enemy>* getEnemies() const
	{
		return enemies;
	}

	unsigned int  enemyCount() const
	{
		return enemies->size();
	}

	void generateEnemies(size_t number = 5)
	{

	}

	void update()
	{
	}

private:
	vector<Enemy>* enemies;
};

#endif
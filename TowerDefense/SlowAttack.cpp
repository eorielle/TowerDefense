#include "SlowAttack.h"
#include "LevelManager.h"


SlowAttack::SlowAttack()
{
}


SlowAttack::~SlowAttack()
{
}

void Attack::resolve()
{
	//TODO:��Ѫ������
	Enemy enemy = getTarget();
	enemy.slow(slowAmount);
}
#include "NormalAttack.h"



NormalAttack::NormalAttack()
{
}


NormalAttack::~NormalAttack()
{
}

void Attack::resolve()
{
	//TODO:��Ѫ������
	Enemy enemy = getTarget();
	enemy.takeDamage(damage);

	//????Timer?????

}
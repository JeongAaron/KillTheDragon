#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>

struct Character
{
	int PlayerHP;
	int PlayerAP;
	int PlayerDP;
};

struct Monster
{
	int MonsterHP;
	int MonsterAP;
	int MonsterDP;
};

void Battle(int* php, int pap, int pdp, int* mhp, int map, int mdp, int x)
{
	int random = rand() % 2;
	if (x == 0 && random == 0)
	{
		if (pdp >= map)
		{
			*php = *php - 1;
		}
		else
		{
			*php = *php - (map - pdp);
		}
		if (mdp >= pap)
		{
			*mhp = *mhp - 1;
		}
		else
		{
			*mhp = *mhp - (pap - mdp);
		}
	}
	else if (x == 0 && random == 1)
	{
		int r = rand() % 2;
		if (r == 0)
		{
			*mhp = *mhp + mdp;
		}
		else
		{
			*mhp = *mhp - (pap + mdp);
		}
	}
	else if (x == 1 && random == 0)
	{
		int d = rand() % 2;
		if (d == 0)
		{
			*php = *php + pdp;
		}
		else
		{
			*php = *php - (map + pdp);
		}
	}
	else
	{
		*php = *php;
		*mhp = *mhp;
	}
}

int main()
{
	int stage = 0;
	int choice = 0;
	srand(time(NULL));
	struct Character character;
	character.PlayerHP = 100;
	character.PlayerAP = 10;
	character.PlayerDP = 5;
	struct Monster monster;
	monster.MonsterHP = 50 + (stage * 10);
	monster.MonsterAP = 10 + (stage * 1);
	monster.MonsterDP = 5 + (stage * 1);
	int php = character.PlayerHP;
	int pap = character.PlayerAP;
	int pdp = character.PlayerDP;
	int mhp = monster.MonsterHP;
	int map = monster.MonsterAP;
	int mdp = monster.MonsterDP;
	printf("%d ", php);
	printf("%d ", pap);
	printf("%d ", pdp);
	printf("%d ", mhp);
	printf("%d ", map);
	printf("%d ", mdp);




}
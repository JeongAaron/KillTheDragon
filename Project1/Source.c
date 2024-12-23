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

void Battle(int * php, int pap, int pdp, int * mhp, int map, int mdp, int x)
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
	while (php > 0 && mhp > 0)
	{
		printf("0 : 공격\n1 : 방어");
		if (GetAsyncKeyState('0') & 0x0001)
		{
			choice = 0;
			Battle(&php, pap, pdp, &mhp, map, mdp, choice);
		}
		else if (GetAsyncKeyState('0') & 0x0001)
		{
			choice = 1;
			Battle(&php, pap, pdp, &mhp, map, mdp, choice);
		}
		else
		{
			printf("공격 혹은 방어를 선택하세요.");
		}
	}
	if (php <= 0)
	{
		printf("플레이어가 패배했습니다.\n");
	}
	else if (mhp <= 0)
	{
		printf("몬스터를 처치했습니다!\n");
	}


	


}
#include <stdio.h>
#include <time.h>
#include <Windows.h>

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

int save(int php,int pap, int pdp, int mhp, int map, int mdp)
{
	FILE* file = fopen("php.txt", "w");
	fputs(php, file);
	fclose(file);
	FILE* file = fopen("pap.txt", "w");
	fputs(pap, file);
	fclose(file);
	FILE* file = fopen("pdp.txt", "w");
	fputs(pdp, file);
	fclose(file);
	FILE* file = fopen("mhp.txt", "w");
	fputs(mhp, file);
	fclose(file);
	FILE* file = fopen("map.txt", "w");
	fputs(pap, file);
	fclose(file);
	FILE* file = fopen("mdp.txt", "w");
	fputs(pdp, file);
	fclose(file);
}

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
		printf("�÷��̾� : ���� VS ���� : ����\n");
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
		printf("�÷��̾� : ���� VS ���� : ���\n");
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
		printf("�÷��̾� : ��� VS ���� : ����\n");
	}
}

int main()
{
	int stage = 1;
	int choice = -1;
	int bonus = -1;
	srand(time(NULL));
	struct Character character;
	character.PlayerHP = 100;
	character.PlayerAP = 10;
	character.PlayerDP = 5;
	int php = character.PlayerHP;
	int pap = character.PlayerAP;
	int pdp = character.PlayerDP;
	while (stage < 11)
	{
		struct Monster monster;
		monster.MonsterHP = 40 + (stage * 10);
		monster.MonsterAP = 9 + (stage * 1);
		monster.MonsterDP = 4 + (stage * 1);
		int mhp = monster.MonsterHP;
		int map = monster.MonsterAP;
		int mdp = monster.MonsterDP;

		while (php > 0 && mhp > 0)
		{
			printf("�÷��̾� ü��: %d, ���� ü��: %d\n", php, mhp);
			printf("1 : ����\n2 : ���\n");
			while (choice == -1)
			{
				if (GetAsyncKeyState('1') & 0x0001)
				{
					choice = 0;
				}
				else if (GetAsyncKeyState('2') & 0x0001)
				{
					choice = 1;
				}
				else if(GetAsyncKeyState('2') & 0x0001)
			}
			Battle(&php, pap, pdp, &mhp, map, mdp, choice);
			printf("���� ��� : �÷��̾� ü��: %d, ���� ü��: %d\n", php, mhp);
			choice = -1;
		}
		if (php > 0)
		{
			printf("������ �����ϼ���.\n1 : ü�� ȸ��(100)\n2 : ���ݷ� ����(5)\n3 : ���� ����(5)\n");
			while (bonus == -1)
			{
				if (GetAsyncKeyState('1') & 0x0001)
				{
					bonus = 1;
					php = php + 100;
				}
				else if (GetAsyncKeyState('2') & 0x0001)
				{
					bonus = 2;
					pap = pap + 5;
				}
				else if (GetAsyncKeyState('3') & 0x0001)
				{
					bonus = 3;
					pdp = pdp + 5;
				}
			}
			bonus = -1;
			stage = stage + 1;
		}
		else if(mhp > 0)
		{
			php = 100;
			pap = 10;
			pdp = 5;
			stage = 1;
		}
	}
	if (stage == 11)
	{
		printf("Victory");
	}
}
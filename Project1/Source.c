#include <stdio.h>
#include <time.h>
#include <Windows.h>

#define PHP 100
#define PAP 10
#define PDP 5
#define MHP 40
#define MAP 9
#define MDP 4
#define STAGE 5

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
void Save(int php,int pap, int pdp, int mhp, int map, int mdp, int stage)
{
	FILE* file;
	file = fopen("php.txt", "w");
	fprintf(file,"%d",php);
	fclose(file);
	file = fopen("pap.txt", "w");
	fprintf(file, "%d", pap);
	fclose(file);
	file = fopen("pdp.txt", "w");
	fprintf(file, "%d", pdp);
	fclose(file);
	file = fopen("mhp.txt", "w");
	fprintf(file, "%d", mhp);
	fclose(file);
	file = fopen("map.txt", "w");
	fprintf(file, "%d", map);
	fclose(file);
	file = fopen("mdp.txt", "w");
	fprintf(file, "%d", mdp);
	fclose(file);
	file = fopen("stage.txt", "w");
	fprintf(file, "%d", stage);
	fclose(file);
}
void Road(int* php, int* pap, int* pdp, int* mhp, int* map, int* mdp, int* stage)
{
	FILE* file;
	file = fopen("php.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%d", php);
		fclose(file);
	}
	else
	{
		printf("Save ");
		*php = PHP;
	}
	file = fopen("pap.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%d", pap);
		fclose(file);
	}
	else
	{
		printf("file ");
		*pap = PAP;
	}
	file = fopen("pdp.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%d", pdp);
		fclose(file);
	}
	else
	{
		printf("does ");
		*pdp = PDP;

	}
	file = fopen("mhp.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%d", mhp);
		fclose(file);
	}
	else
	{
		printf("not \n");
		*mhp = MHP;
	}
	file = fopen("map.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%d", map);
		fclose(file);
	}
	else
	{
		printf("exist. ");
		*map = MAP;
	}
	file = fopen("mdp.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%d", mdp);
		fclose(file);
	}
	else
	{
		printf("Start ");
		*mdp = MDP;
	}
	file = fopen("stage.txt", "r");
	if (file != NULL)
	{
		fscanf(file, "%d", stage);
		fclose(file);
	}
	else
	{
		printf("new game.");
		*stage = 0;
	}
	Sleep(2000);
}
void Battle(int * php, int * pap, int * pdp, int * mhp, int * map, int * mdp, int x)
{
	int random = rand() % 2;
	if (x == 0 && random == 0)
	{
		if (*pdp >= *map)
		{
			*php--;
		}
		else
		{
			*php -= (*map - *pdp);
		}
		if (*mdp >= *pap)
		{
			*mhp--;
		}
		else
		{
			*mhp -= (*pap - *mdp);
		}
		printf("�÷��̾� : ���� VS ���� : ����\n");
	}
	else if (x == 0 && random == 1)
	{
		int r = rand() % 2;
		if (r == 0)
		{
			*mhp += *mdp;
		}
		else
		{
			*mhp -= (*pap + *mdp);
		}
		printf("�÷��̾� : ���� VS ���� : ���\n");
	}
	else if (x == 1 && random == 0)
	{
		int d = rand() % 2;
		if (d == 0)
		{
			*php += *pdp;
		}
		else
		{
			*php -= (*map + *pdp);
		}
		printf("�÷��̾� : ��� VS ���� : ����\n");
	}
}
int main()
{
	printf("N : New Game\nR : Road Game\nL : Leave");
	int stage = 0;
	int choice = -1;
	int bonus = -1;
	int save = -1;
	struct Character character;
	character.PlayerHP = PHP;
	character.PlayerAP = PAP;
	character.PlayerDP = PDP;
	int php = character.PlayerHP;
	int pap = character.PlayerAP;
	int pdp = character.PlayerDP;
	struct Monster monster;
	monster.MonsterHP = MHP;
	monster.MonsterAP = MAP;
	monster.MonsterDP = MDP;
	int mhp = monster.MonsterHP;
	int map = monster.MonsterAP;
	int mdp = monster.MonsterDP;
	srand(time(NULL));
	while (save == -1)
	{
		if (GetAsyncKeyState('N') & 0x0001)
		{
			save = 1;
		}
		else if (GetAsyncKeyState('R') & 0x0001)
		{
			save = 2;
		}
		else if (GetAsyncKeyState('L') & 0x0001)
		{
			exit(0);
		}
	}
	while (stage < STAGE)
	{
		if (save == 2)
		{
			Road(&php, &pap, &pdp, &mhp, &map, &mdp, &stage);
			save = -1;
		}
		else
		{
		mhp += (stage * 10);
		map += (stage * 1);
		mdp += (stage * 1);
		}
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
				else if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
				{
					printf("S : save\nE : Exit");
					if (GetAsyncKeyState('S') & 0x0001)
					{
					Save(php, pap, pdp, mhp, map, mdp, stage);
					}
					else if (GetAsyncKeyState('E') & 0x0001)
					{
						exit(0);
					}
				}
			}
			Battle(&php, &pap, &pdp, &mhp, &map, &mdp, choice);
			printf("���� ��� : �÷��̾� ü��: %d, ���� ü��: %d\n", php, mhp);
			choice = -1;
		}
		if (php > 0 && stage < STAGE)
		{
			printf("1%d Stage Clear\n", stage);
			printf("������ �����ϼ���.\n1 : ü�� ȸ��(50)\n2 : ���ݷ� ����(5)\n3 : ���� ����(5)\n");
			while (bonus == -1)
			{
				if (GetAsyncKeyState('1') & 0x0001)
				{
					bonus = 1;
					php += 50;
				}
				else if (GetAsyncKeyState('2') & 0x0001)
				{
					bonus = 2;
					pap += 5;
				}
				else if (GetAsyncKeyState('3') & 0x0001)
				{
					bonus = 3;
					pdp += 5;
				}
			}
			bonus = -1;
			stage++;
		}
		else if(mhp > 0)
		{
			php = PHP;
			pap = PAP;
			pdp = PDP;
			stage = 0;
		}
	}
	if (stage == STAGE)
	{
		printf("Victory");
	}
}
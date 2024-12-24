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
void Savefile(char * filename, int value)
{
	FILE* file = fopen(filename, "w");
	fprintf(file, "%d\n", value);
	fclose(file);
}
void Save(int php,int pap, int pdp, int mhp, int map, int mdp, int stage)
{
	Savefile("php.txt", php);
	Savefile("pap.txt", pap);
	Savefile("pdp.txt", pdp);
	Savefile("mhp.txt", mhp);
	Savefile("map.txt", map);
	Savefile("mdp.txt", mdp);
	Savefile("stage.txt", stage);
}
void Read(char* filename, int* value, int defaultvalue)
{
	int number = 0;
	FILE* file = fopen(filename, "r");
	if (file != NULL)
	{
		fscanf_s(file, "%d", &number);
		*value = number;
		fclose(file);
	}
	else
	{
		printf("파일을 찾을 수 없어 새로 시작합니다.\n");
		*value = defaultvalue;
	}
}
void Road(int* php, int* pap, int* pdp, int* mhp, int* map, int* mdp, int* stage)
{
	Read("php.txt", php, PHP);
	Read("pap.txt", pap, PAP);
	Read("pdp.txt", pdp, PDP);
	Read("mhp.txt", mhp, MHP);
	Read("map.txt", map, MAP);
	Read("mdp.txt", mdp, MDP);
	Read("stage.txt", stage, 0);
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
		printf("플레이어 : 공격 VS 몬스터 : 공격\n");
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
		printf("플레이어 : 공격 VS 몬스터 : 방어\n");
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
		printf("플레이어 : 방어 VS 몬스터 : 공격\n");
	}
}
int main()
{
	printf("N : New Game\nR : Road Game\nL : Leave\n");
	int stage = 0;
	int choice = -1;
	int bonus = -1;
	int save = -1;
	int savefile = -1;
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
		mhp = MHP + (stage * 10);
		map = MAP + (stage * 1);
		mdp = MDP + (stage * 1);
		}
		while (php > 0 && mhp > 0)
		{
			printf("플레이어 체력: %d, 몬스터 체력: %d\n", php, mhp);
			printf("1 : 공격\n2 : 방어\n");
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
					printf("S : Save\nE : Exit");
					while (savefile == -1)
					{
						if (GetAsyncKeyState('S') & 0x0001)
						{
							Save(php, pap, pdp, mhp, map, mdp, stage);
							savefile = 0;
							exit(0);
						}
						else if (GetAsyncKeyState('E') & 0x0001)
						{
							exit(0);
							savefile = 1;
						}
						savefile = -1;
					}
				}
			}
			Battle(&php, &pap, &pdp, &mhp, &map, &mdp, choice);
			printf("전투 결과 : 플레이어 체력: %d, 몬스터 체력: %d\n", php, mhp);
			choice = -1;
		}
		if (php > 0 && stage < STAGE - 1)
		{
			printf("%d Stage Clear\n", stage + 1);
			printf("보상을 선택하세요.\n1 : 체력 회복(50)\n2 : 공격력 증가(5)\n3 : 방어력 증가(5)\n");
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
			stage += 1;
		}
		else if(mhp > 0)
		{
			php = PHP;
			pap = PAP;
			pdp = PDP;
			stage = 0;
		}
		else if (stage == STAGE - 1)
		{
			printf("Victory\n");
			exit(0);
		}
	}
}
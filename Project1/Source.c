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

int screenIndex;
HANDLE screen[2];

void Initialize()
{
	CONSOLE_CURSOR_INFO cursor;
	//	화면 버퍼를 2개 생성.
	screen[0] = CreateConsoleScreenBuffer
	(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	screen[1] = CreateConsoleScreenBuffer
	(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	cursor.dwSize = 1;
	cursor.bVisible = FALSE;

	SetConsoleCursorInfo(screen[0], &cursor);
	SetConsoleCursorInfo(screen[1], &cursor);
}

void Flip()
{
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	screenIndex = !screenIndex;
}

void Clear()
{
	COORD position = { 0,0 };
	DWORD dword;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &consoleInfo);
	int width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
	FillConsoleOutputCharacter(screen[screenIndex], ' ', width * height, position, &dword);
}

void Release()
{
	CloseHandle(screen[0]);
	CloseHandle(screen[1]);
}

void Render(int x, int y, const char* shape)
{
	DWORD dword;
	//	x축과 y축을 설정
	COORD position = { x, y };
	SetConsoleCursorPosition(screen[screenIndex], position);
	WriteFile(screen[screenIndex], shape, strlen(shape), &dword, NULL);
}
void maximizeConsoleWindow() 
{
	HWND hwndConsole = GetConsoleWindow();
	ShowWindow(hwndConsole, SW_MAXIMIZE);
}
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
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &consoleInfo);
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
		Render((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left - 1) / 2, consoleInfo.srWindow.Bottom, "플레이어 공격 VS 몬스터 공격");
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
		Render((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left - 1) / 2, consoleInfo.srWindow.Bottom, "플레이어 공격 VS 몬스터 방어");
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
		Render((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left - 1) / 2, consoleInfo.srWindow.Bottom, "플레이어 방어 VS 몬스터 공격");
	}
	else
	{
		Render((consoleInfo.srWindow.Right - consoleInfo.srWindow.Left - 1) / 2, consoleInfo.srWindow.Bottom, "플레이어 방어 VS 몬스터 방어");
	}
}
int main()
{
	maximizeConsoleWindow();
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &consoleInfo);
	Initialize();
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
	int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top - 1;
	int width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left - 1;
	char playerhp = php;
	srand(time(NULL));
	while (save == -1)
	{
		Flip();
		Clear();
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
		Render(width/2, 10, "N : New Game");
		Render(width/2, 20, "R : Road Game");
		Render(width/2, 30,"L : Leave");
	}
	Clear();
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
			Render(width/2, 0, "1 : 공격 2 : 방어");
			Flip();
			Clear();
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
					while (savefile == -1)
					{
						Flip();
						Clear();
						Render(width / 2, height / 2, "Game Over");
						Render(width / 2, (height / 2) + 2, "Save");
						Render(width / 2, (height / 2) + 4, "Exit");
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
			choice = -1;
		}
		if (php > 0 && stage < STAGE - 1)
		{
			while (bonus == -1)
			{
				Flip();
				Clear();
				Render(width / 2, consoleInfo.srWindow.Bottom, "Stage Clear");
				Render(width / 2, height / 2, "보상을 선택하세요");
				Render(width / 2, (height / 2) + 2, "1 : 체력회복(50)");
				Render(width / 2, (height / 2) + 4, "2 : 공격력 증가(5)");
				Render(width / 2, (height / 2) +6, "3 : 방어력력 증가(5)");
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
			Clear();
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
			Clear();
			printf("Victory\n");
			exit(0);
		}
	}
	Release();
}
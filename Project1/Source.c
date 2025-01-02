#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define PHP 100
#define PAP 10
#define PDP 5
#define MHP 40
#define MAP 9
#define MDP 4
#define STAGE 5
#define SIZE 10000
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

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
enum Color
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKSKY,
	DARKRED,
	DARKPURPLE,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	SKY,
	RED,
	PURPLE,
	YELLOW,
	WHITE
};
int screenIndex;
HANDLE screen[2];
void Initialize()
{
	CONSOLE_CURSOR_INFO cursor;
	//	ȭ�� ���۸� 2�� ����.
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
	COORD position = { x, y };
	SetConsoleCursorPosition(screen[screenIndex], position);
	for (int i = 0; i < strlen(shape); i++) 
	{
		if (shape[i] == 'O') 
		{
			SetConsoleTextAttribute(screen[screenIndex], BLUE);
		}
		else if (shape[i] == 'Q') 
		{
			SetConsoleTextAttribute(screen[screenIndex], GREEN);
		}
		else if (shape[i] == 'X')
		{
			SetConsoleTextAttribute(screen[screenIndex], RED);
		}
		else if (shape[i] == 'U')
		{
			SetConsoleTextAttribute(screen[screenIndex], DARKGREEN);
		}
		else 
		{
			SetConsoleTextAttribute(screen[screenIndex], WHITE);
		}
		WriteFile(screen[screenIndex], &shape[i], 1, &dword, NULL);
	}
}
void PlayerStatus(int x, int y, int php, int pap, int pdp)
{
	char buffer[50];
	snprintf(buffer, sizeof(buffer), "HP: %d  AP: %d  DP: %d", php, pap, pdp);
	Render(x, y, buffer);
}
void MonsterStatus(int x, int y, int mhp, int map, int mdp)
{
	char buffer[50];
	snprintf(buffer, sizeof(buffer), "HP: %d  AP: %d  DP: %d", mhp, map, mdp);
	Render(x, y, buffer);
}
void AD(int x,int y,char* z)
{
	FILE* file = fopen(z, "r");

	char buffer[SIZE];
	int currentY = y;

	while (fgets(buffer, SIZE, file) != NULL) 
	{
		buffer[strcspn(buffer, "\r\n")] = '\0'; 
		Render(x, currentY, buffer); 
		currentY++;                          
	}

	fclose(file);
}
void Stage(int x, int y, int stage)
{
	char buffer[50];
	snprintf(buffer, sizeof(buffer), "%d Stage",stage + 1);
	Render(x, y, buffer);
}
void Write(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dword;
	COORD position = { x, y };
	SetConsoleCursorPosition(handle, position);
}
void maximizeConsoleWindow() 
{
	HWND hwndConsole = GetConsoleWindow();
	ShowWindow(hwndConsole, SW_MAXIMIZE);
}
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
		printf("������ ã�� �� ���� ���� �����մϴ�.\n");
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
void Battle(int * php, int * pap, int * pdp, int * mhp, int * map, int * mdp, int x,int stage,int *Pr, int* Mr,int*Pd,int*Md)
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
		*Pr = 0;
		*Mr = 0;
	}
	else if (x == 0 && random == 1)
	{
		int r = rand() % 2;
		if (r == 0)
		{
			*mhp += *mdp;
			*Md = 0;
		}
		else
		{
			*mhp -= (*pap + *mdp);
			*Md = 1;
		}
		*Pr = 0;
		*Mr = 1;
	}
	else if (x == 1 && random == 0)
	{
		int d = rand() % 2;
		if (d == 0)
		{
			*php += *pdp;
			*Pd = 0;
		}
		else
		{
			*php -= (*map + *pdp);
			*Pd = 1;
		}
		*Pr = 1;
		*Mr = 0;
	}
	else
	{
		*Pr = 1;
		*Pd = 0;
		*Mr = 1;
		*Md = 0;
	}
}
void SetConsoleFont(int fontSize) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	wcscpy_s(cfi.FaceName, ARRAYSIZE(cfi.FaceName), L"Consolas");
	cfi.dwFontSize.X = fontSize;
	cfi.dwFontSize.Y = fontSize;
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}
int main()
{
	maximizeConsoleWindow();
	SetConsoleFont(16);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(handle, &consoleInfo);
	Initialize();
	int stage = 0;
	int choice = -1;
	int bonus = -1;
	int save = -1;
	int result = -1;
	int Pr = 0;
	int Mr = 0;
	int Pd = 0;
	int Md = 0;
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
	char key = 0;
	int select = 0;
	int select1 = 0;
	const int option = 3;
	const int option1 = 2;

	while (save == -1)
	{
		Flip();
		Clear();
		if (_kbhit())
		{
			key = _getch();
			if (key == -32)
			{
				key = _getch();
			}
			switch (key)
			{
			case LEFT: select = (select - 1 + option) % option;break;
			case RIGHT: select = (select + 1) % option;break;
			default: break;
			}
		}
		switch (select)
		{
			case 0: Render(width * 1 / 3 - 7, consoleInfo.srWindow.Bottom, "��");if (GetAsyncKeyState(VK_SPACE) & 0x0001) save = 1;break;
			case 1: Render(width/2 - 7, consoleInfo.srWindow.Bottom, "��");if (GetAsyncKeyState(VK_SPACE) & 0x0001) save = 2; break;
			case 2: Render(width * 2 / 3 - 7, consoleInfo.srWindow.Bottom, "��");if (GetAsyncKeyState(VK_SPACE) & 0x0001) exit(0); break;
		}
		AD(2, 0, "title.txt");
		Render(width/2 - 30, consoleInfo.srWindow.Bottom - 2, "���� : SpaceBar    ȭ��ǥ �̵� : ��,��,��,��     ������ ���� : Esc");
		Render(width * 1/3, consoleInfo.srWindow.Bottom, "New Game");
		Render(width/2, consoleInfo.srWindow.Bottom, "Road Game");
		Render(width * 2/3, consoleInfo.srWindow.Bottom,"Leave");
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
		mhp = MHP + (stage * 50);
		map = MAP + (stage * 5);
		mdp = MDP + (stage * 5);
		}
		while (php > 0 && mhp > 0)
		{
			Flip();
			Clear();
			int currentPhp = php;
			int currentMhp = mhp;
			while (choice == -1)
			{
				Flip();
				Clear();
				if (_kbhit())
				{
					key = _getch();
					if (key == -32)
					{
						key = _getch();
					}
					switch (key)
					{
					case UP: select1 = (select1 - 1 + option1) % option1; break;
					case DOWN: select1 = (select1 + 1) % option1; break;
					default: break;
					}
				}
				switch (select1)
				{
				case 0: Render(width / 2 - 15, height / 2 - 1, "��"); if (GetAsyncKeyState(VK_SPACE) & 0x0001) choice = 0; break;
				case 1: Render(width / 2 - 15, height / 2 + 1, "��"); if (GetAsyncKeyState(VK_SPACE) & 0x0001) choice = 1; break;
				}
				if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
				{
					while (1)
					{
						Flip();
						Clear();
						if (_kbhit())
						{
							key = _getch();
							if (key == -32)
							{
								key = _getch();
							}
							switch (key)
							{
							case UP: select1 = (select1 - 1 + option1 ) % option1 ; break;
							case DOWN: select1 = (select1 + 1) % option1 ; break;
							default: break;
							}
						}
						switch (select1)
						{
						case 0: Render(width / 2 - 5, height / 2 + 2, "��"); if (GetAsyncKeyState(VK_SPACE) & 0x0001) Save(php, pap, pdp, mhp, map, mdp, stage),exit(0); break;
						case 1: Render(width / 2 - 5, height / 2 + 4, "��"); if (GetAsyncKeyState(VK_SPACE) & 0x0001) exit(0); break;
						}
						Render(width / 2, (height / 2) + 2, "Save");
						Render(width / 2, (height / 2) + 4, "Exit");
					}
				}
				Battle(&php, &pap, &pdp, &mhp, &map, &mdp, choice,stage,&Pr,&Mr,&Pd,&Md);
				Render(width / 2 - 10, height / 2 - 1, "����");
				Render(width / 2 - 10, height / 2 + 1, "���");
				AD(5, height / 2 - 5, "knight.txt");
				switch (stage)
				{
				case 0: AD(width * 4 / 5, 2, "snale.txt"); Render((width * 4 / 5) + 7, (height / 2) - 2, "������"); break;
				case 1: AD(width * 4 / 5, 2, "slime.txt"); Render((width * 4 / 5) + 7, (height / 2) - 2, "������"); break;
				case 2: AD(width * 4 / 5, 2, "goblin.txt"); Render((width * 4 / 5) + 7, (height / 2) - 2, "���"); break;
				case 3: AD(width * 4 / 5, 2, "ogre.txt"); Render((width * 4 / 5) + 7, (height / 2) - 2, "�����"); break;
				case 4: AD(width * 4 / 5, 2, "dragon.txt"); Render((width * 4 / 5) + 7, (height / 2) - 2, "�巡��"); break;
				}
				PlayerStatus(5, height / 2 - 7, php, pap, pdp);
				MonsterStatus((width * 4 / 5) + 7, height / 2, mhp, map, mdp);
				Stage(width / 2 - 5, 2, stage);
			}
			choice = -1;
		}
		if (php > 0 && stage < STAGE - 1)
		{
			while (bonus == -1)
			{
				Flip();
				Clear();
				if (_kbhit())
				{
					key = _getch();
					if (key == -32)
					{
						key = _getch();
					}
					switch (key)
					{
					case UP: select = (select - 1 + option) % option; break;
					case DOWN: select = (select + 1) % option; break;
					default: break;
					}
				}
				switch (select)
				{
				case 0: Render(width /2 - 5, height/2 + 2, "��"); if (GetAsyncKeyState(VK_SPACE) & 0x0001) bonus = 1, php += 50; break;
				case 1: Render(width /2 - 5, height/2 + 4, "��"); if (GetAsyncKeyState(VK_SPACE) & 0x0001) bonus = 2, pap += 5; break;
				case 2: Render(width /2 - 5, height/2 + 6, "��"); if (GetAsyncKeyState(VK_SPACE) & 0x0001) bonus = 3, pdp += 5; break;
				}
				Render(width / 2, consoleInfo.srWindow.Bottom, "Stage Clear");
				Render(width / 2, height / 2, "������ �����ϼ���");
				Render(width / 2, (height / 2) + 2, "ü��ȸ��(50)");
				Render(width / 2, (height / 2) + 4, "���ݷ� ����(5)");
				Render(width / 2, (height / 2) +6, "���·� ����(5)");
			}
			Clear();
			bonus = -1;
			stage += 1;
		}
		else if(mhp > 0)
		{
			while (result == -1)
			{
				Flip();
				Clear();
				if (_kbhit())
				{
					key = _getch();
					if (key == -32)
					{
						key = _getch();
					}
					switch (key)
					{
					case LEFT: select1 = (select1 - 1 + option1) % option1; break;
					case RIGHT: select1 = (select1 + 1) % option1; break;
					default: break;
					}
				}
				switch (select1)
				{
				case 0: Render((width / 2) - 25, height * 2 / 3, "��");
					if (GetAsyncKeyState(VK_SPACE) & 0x0001)
					{
						result = 1;
						php = PHP;
						pap = PAP;
						pdp = PDP;
						stage = 0;
					};
					break;
				case 1: Render((width / 2) + 15, height * 2 / 3, "��"); if(GetAsyncKeyState(VK_SPACE) & 0x0001) exit(0); break;
				}
				AD(20, 2, "defeat.txt");
				Render((width / 2)- 20, (height* 2/3), "Restart");
				Render((width / 2)+20, (height* 2/3), "Exit");
			}
			result = -1;
		}
		else if (stage == STAGE - 1)
		{
			while (result == -1)
			{
				Flip();
				Clear();
				AD(20, 2, "victory.txt");
				if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
				{
					result = 1;
				}
			}
			exit(0);
		}
	}
	Release();
}
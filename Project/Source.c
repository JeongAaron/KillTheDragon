#include <windows.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

HANDLE hConsole;

// Render �Լ�: ������ ��ǥ�� ���ڿ� ���
void maximizeConsoleWindow()
{
    HWND hwndConsole = GetConsoleWindow();
    ShowWindow(hwndConsole, SW_MAXIMIZE);
}
void Render(int x, int y, const char* text)
{
    if (text == NULL) return;

    // �ܼ� ��� �ڵ� ��������
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Failed to get console handle.\n");
        return;
    }

    // ��ǥ ����
    COORD position = { x, y };

    // �ؽ�Ʈ ���
    DWORD written;
    if (!WriteConsoleOutputCharacter(hConsole, text, strlen(text), position, &written)) {
        printf("Failed to write text at position (%d, %d).\n", x, y);
    }
}

// LoadAndRender �Լ�: ���� ������ �о�� ������ ��ǥ�� ���
void LoadAndRender(int x, int y, const char* filePath)
{
    if (filePath == NULL) {
        printf("Invalid file path.\n");
        return;
    }

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File not found: %s\n", filePath);
        return;
    }

    char buffer[BUFFER_SIZE];
    int currentY = y;

    // ���� ������ �� ������ �о� ���
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0'; // ���� ���� ����
        Render(x, currentY++, buffer);         // ���� Y ��ǥ�� ��� �� Y ����
    }

    fclose(file);
}

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &consoleInfo);
    maximizeConsoleWindow();
    // ������ �ؽ�Ʈ ������ ������ (10, 5) ��ǥ�� ���
    printf("%d", consoleInfo.srWindow.Right - consoleInfo.srWindow.Left);
    return 0;
}
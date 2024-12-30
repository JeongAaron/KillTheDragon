#include <windows.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

HANDLE hConsole;

// Render 함수: 지정한 좌표에 문자열 출력
void maximizeConsoleWindow()
{
    HWND hwndConsole = GetConsoleWindow();
    ShowWindow(hwndConsole, SW_MAXIMIZE);
}
void Render(int x, int y, const char* text)
{
    if (text == NULL) return;

    // 콘솔 출력 핸들 가져오기
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        printf("Failed to get console handle.\n");
        return;
    }

    // 좌표 설정
    COORD position = { x, y };

    // 텍스트 출력
    DWORD written;
    if (!WriteConsoleOutputCharacter(hConsole, text, strlen(text), position, &written)) {
        printf("Failed to write text at position (%d, %d).\n", x, y);
    }
}

// LoadAndRender 함수: 파일 내용을 읽어와 지정된 좌표에 출력
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

    // 파일 내용을 줄 단위로 읽어 출력
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0'; // 개행 문자 제거
        Render(x, currentY++, buffer);         // 현재 Y 좌표에 출력 후 Y 증가
    }

    fclose(file);
}

int main()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &consoleInfo);
    maximizeConsoleWindow();
    // 슬라임 텍스트 파일의 내용을 (10, 5) 좌표에 출력
    printf("%d", consoleInfo.srWindow.Right - consoleInfo.srWindow.Left);
    return 0;
}
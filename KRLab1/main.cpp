#include "main.hpp"
#include "dataProcessing.hpp"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTheme();
	int iResult = !DataProcessing();
	system("pause");
	return iResult;
}

void SetConsoleTheme()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csfiex;

	csfiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdOut, &csfiex);
	// Console window size:
	csfiex.dwMaximumWindowSize.X = 920;
	csfiex.dwMaximumWindowSize.Y = 720;
	csfiex.srWindow.Left = 50;
	csfiex.srWindow.Top = 5;
	csfiex.srWindow.Right = 100;
	csfiex.srWindow.Bottom = 55;
	// Console color:
	csfiex.ColorTable[0] = 0x202020;
	csfiex.ColorTable[1] = 0xFF0096;
	SetConsoleScreenBufferInfoEx(hStdOut, &csfiex);
	system("color 01");
}
#include "stdafx.h"
#include "Game.h"
#include <Windows.h>

int main(){
	Game game;

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);

	game.run();

	return 0;
}
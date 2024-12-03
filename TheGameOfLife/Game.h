#pragma once

#include "Grid.h"

class Game
{
	HWND hwnd;
	HANDLE consoleHandle;
	CONSOLE_CURSOR_INFO cursorInfo;
	Grid* grid;
	vector<Coordinate*> coordinatesCellAlive;
	u_int coordinatesCellAliveSize;

public:
	Game();
	~Game();

private:
	bool AddPoint(Coordinate* _coordinate);
	bool AddPoint(const Coordinate& _coordinate);
	void CheckCellAlive();
	void ResetWeightCell();

public:
	void Gameloop();
	bool IsOver();
	void DisplayGrid(const bool _showGrid = false);
	void AddPointToAll();
	void AddPointToNeighbourCell();
};


#include "Game.h"

Game::Game()
{
	hwnd = GetForegroundWindow();
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;
	grid = new Grid();
	coordinatesCellAliveSize = (u_int)coordinatesCellAlive.size();
}

Game::~Game()
{
	delete grid;
}

void Game::Gameloop()
{
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	Coordinate* _coordinateToTest = grid->GetTile(5,5)->GetCoordinate();
	AddPoint(_coordinateToTest);
	AddPoint(_coordinateToTest);
	AddPoint(_coordinateToTest);

	Coordinate* _coordinateToTest2 = grid->GetTile(6, 6)->GetCoordinate();
	AddPoint(_coordinateToTest2);
	AddPoint(_coordinateToTest2);
	AddPoint(_coordinateToTest2);

	Coordinate* _coordinateToTest3 = grid->GetTile(6, 5)->GetCoordinate();
	AddPoint(_coordinateToTest3);
	AddPoint(_coordinateToTest3);
	AddPoint(_coordinateToTest3);

	do
	{
		SetConsoleCursorPosition(consoleHandle, {0, 0});
		DisplayGrid(true);
		AddPointToNeighbourCell();
		CheckCellAlive();
		

	} while (!IsOver());
}

bool Game::IsOver()
{
	return coordinatesCellAlive.size() == 0;
}

void Game::DisplayGrid(const bool _showGrid)
{
	Sleep(1000);
	grid->Display(true);
}

void Game::CheckCellAlive()
{
	for (u_int _index = 0; _index < coordinatesCellAliveSize; _index++)
	{
		Coordinate* _coordinateToCheck = coordinatesCellAlive[_index];
		Tile* _tileToUpdate = grid->GetTile(_coordinateToCheck);
		if (_tileToUpdate->GetWeight() != 3)
		{
			_tileToUpdate->SetAppearance(RESET);
			coordinatesCellAlive.erase(coordinatesCellAlive.begin()+_index);
			coordinatesCellAliveSize = (u_int)coordinatesCellAlive.size();
		}
	}
}

void Game::ResetWeightCell()
{
	for (u_int _index = 0; _index < coordinatesCellAliveSize; _index++)
	{
		Coordinate* _currentCoordinate = coordinatesCellAlive[_index];
		Tile* _tempTile = grid->GetTile(_currentCoordinate);
		_tempTile->SetWeight(0);
	}
}

/// <summary>
/// Fonction qui sert à debug
/// </summary>
void Game::AddPointToAll()
{
	u_int _length = grid->GetLength();
	u_int _width = grid->GetWidth();
	for (u_int _indexX = 0;  _indexX < _length;  _indexX++)
	{
		for (u_int _indexY = 0; _indexY < _width; _indexY++)
		{
			grid->GetTile( _indexX , _indexY)->UpdateWeight(1);
		}
	}
}

void Game::AddPointToNeighbourCell()
{
	Coordinate _directions[]
	{
		Coordinate(0,1),
		Coordinate(1,1),
		Coordinate(1,0),
		Coordinate(1,-1),
		Coordinate(0,-1),
		Coordinate(-1,-1),
		Coordinate(-1,0),
		Coordinate(-1,1),
	};

	for (u_int _index = 0; _index < coordinatesCellAliveSize; _index++)
	{
		Coordinate* _currentCoordinate = coordinatesCellAlive[_index];
		for (Coordinate _direction : _directions)
		{
			const int _newX = (_currentCoordinate->x + _direction.x) < 0 ? 0 : (_currentCoordinate->x + _direction.x) != grid->GetLength() ? _currentCoordinate->x + _direction.x : grid->GetLength() - 1;
			const int _newY = (_currentCoordinate->y + _direction.y) < 0 ? 0 : (_currentCoordinate->y + _direction.y) != grid->GetWidth() ? _currentCoordinate->y + _direction.y : grid->GetLength() - 1;
			Coordinate _coordinateToChange = { _newX, _newY };
			if (AddPoint(_coordinateToChange))
			{
				AddPointToNeighbourCell();
			};
		}

	}

}


bool Game::AddPoint(Coordinate* _coordinate)
{
	Tile* _tileToUpdate = grid->GetTile(_coordinate);
	if (Coordinate* _coordinateToPush = _tileToUpdate->UpdateWeight(1))
	{
		coordinatesCellAlive.push_back(_coordinateToPush);
		coordinatesCellAliveSize = (u_int)coordinatesCellAlive.size();
		return true;
	}
	return false;
}

bool Game::AddPoint(const Coordinate& _coordinate)
{
	Tile* _tileToUpdate = grid->GetTile(_coordinate.x, _coordinate.y);
	Coordinate* _coordinateToPush = _tileToUpdate->UpdateWeight(1);
	if (_coordinateToPush)
	{
		for (u_int _index = 0;  _index < coordinatesCellAliveSize;  _index++)
		{
			if (coordinatesCellAlive[_index] == _coordinateToPush) return false;
		}

		coordinatesCellAlive.push_back(_coordinateToPush);
		coordinatesCellAliveSize = (u_int)coordinatesCellAlive.size();
		return true;
	}
	return false;

}

#include "Tile.h"

Tile::Tile(Coordinate* _coordinate)
{
	coordinate = _coordinate;
	appearance = RESET;
	weight = 0;
}

Tile::Tile(const string& _appearance, const u_int& _weight)
{
	appearance = _appearance;
	weight = _weight;
}

Tile::~Tile()
{
	delete coordinate;
}

/// <summary>
/// Permet de changer le poids de la cell,
/// Si le poid est de 3 alors la méthode renvoie
/// sa coordonée
/// Sinon elle renvoie nullptr
/// </summary>
/// <param name="_point"></param>
/// <returns></returns>
Coordinate* Tile::UpdateWeight(const int _point)
{
	weight += _point;
	weight %= 4;
	if (weight != 3 && appearance == RESET) return nullptr;
	else if (weight == 3 && appearance == RESET)
	{
		appearance = WHITE_BG;
		weight = 0;
		return coordinate;
	}
	else
	{
		appearance = RESET;
		return nullptr;
	}
}

void Tile::UpdateCell(const string& _appearance, const u_int& _weight)
{
	weight = _weight;
	appearance = _appearance;
	// TODO UPDATE LIST IN GAME
}

void Tile::Display() const
{
	DISPLAY(appearance + "  " + RESET, false);
}

string Tile::ToString()
{
	return appearance + "  " + RESET;
}

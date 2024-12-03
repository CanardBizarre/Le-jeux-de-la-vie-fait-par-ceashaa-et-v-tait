#pragma once

#include "Coordinate.h"

class Tile
{
	Coordinate* coordinate;
	string appearance;
	u_int weight;
public:
	inline void SetTile(Coordinate* _coordinate)
	{
		coordinate = _coordinate;
	}

	inline void SetAppearance(const string& _color)
	{
		appearance = _color;
	}


	inline void SetWeight(const u_int _value)
	{
		weight = _value;
	}

	inline Coordinate* GetCoordinate()const
	{
		return coordinate;
	}

	inline u_int GetWeight()const
	{
		return weight;
	}


public:
	Tile(Coordinate* _coordinate);
	
	Tile(const string& _appearance, const u_int& _weight);

	~Tile();
	
public:
	void UpdateCell(const string& _appearance, const u_int& _weight);
	Coordinate* UpdateWeight(const int _point);
	
	void Display() const;
	string ToString();
};


#pragma once
#include<Siv3D.hpp>


class Clock
{

public:

	Clock()
	{
		FontAsset::Register(U"clockDate", 13);
		FontAsset::Register(U"clockTime", 20);
	}


	void draw(const Point& _pos)const
	{
		const auto datetime = DateTime::Now();

		const auto dateStr = datetime.format(U"MM/dd");
		const auto timeStr = datetime.format(U"HH:mm");

		FontAsset(U"clockDate")(dateStr).draw(_pos.movedBy(0, 0));
		FontAsset(U"clockTime")(timeStr).draw(_pos.movedBy(0, 25));
	}

	void draw(int _x, int _y)const
	{
		draw(Point(_x, _y));
	}
};

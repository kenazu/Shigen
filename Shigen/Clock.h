#pragma once
#include<Siv3D.hpp>


class Clock
{

public:

	Clock()
	{
		FontAsset::Register(U"clockDate", 20);
		FontAsset::Register(U"clockTime", 30);
	}


	void draw(const Point& _pos,double _scale = 1)const
	{
		const Mat3x2 mat = Mat3x2::Scale(_scale, _pos);

		const auto datetime = DateTime::Now();

		const auto dateStr = datetime.format(U"MM/dd");
		const auto timeStr = datetime.format(U"HH:mm");

		const Transformer2D t(mat);

		FontAsset(U"clockDate")(dateStr).draw(_pos.movedBy(0, 0));
		FontAsset(U"clockTime")(timeStr).draw(_pos.movedBy(0, 25));
	}

	void draw(int _x, int _y,double _scale=1)const
	{
		draw(Point(_x, _y), _scale);
	}
};

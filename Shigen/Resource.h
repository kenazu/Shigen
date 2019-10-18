#pragma once
#pragma once
# include <Siv3D.hpp>
# include <chrono>
# include"Utility.h"

namespace knz
{

	class Resource
	{
		int m_a;
		int m_b;
		int m_c;
		int m_d;

		DateTime m_timeStamp;

		FilePath m_path;

		const Minutes m_interval_min = Minutes(1);



	public:

		Resource() :m_a(0), m_b(0), m_c(0), m_d(0), m_timeStamp(NowDateTimeUntilMin()) {}

		Resource(const FilePath& _path) :m_path(_path)
		{
			loadIni(_path);
			update();
		}

		~Resource()
		{
			saveIni(m_path);
		}

		DateTime getTimeStamp()const { return m_timeStamp; }

		bool loadIni(const FilePath& _path)
		{
			INIData ini(_path);

			if (!ini) { return false; }

			m_a = ini.getOr<int>(U"Resource.a", 0);
			m_b = ini.getOr<int>(U"Resource.b", 0);
			m_c = ini.getOr<int>(U"Resource.c", 0);
			m_d = ini.getOr<int>(U"Resource.d", 0);
			m_timeStamp = StringToDateTime(ini.getOr<String>(U"Resource.timeStamp", NowDateTimeUntilMin().format()));
			//ini.close();
			return true;
		}

		bool saveIni(const FilePath& _path)
		{
			INIData ini(_path);

			ini.write(U"Resource", U"a", m_a);
			ini.write(U"Resource", U"b", m_b);
			ini.write(U"Resource", U"c", m_c);
			ini.write(U"Resource", U"d", m_d);
			ini.write(U"Resource", U"timeStamp", m_timeStamp.format());

			//ini.close();
			return ini.save(_path);
		}


		int getA()const { return m_a; }
		int getB()const { return m_b; }
		int getC()const { return m_c; }
		int getD()const { return m_d; }


		void update()
		{
			const auto duration_min = DurationCast<Minutes, Microseconds>(getDuration_ms());

			if (isOverInterval(duration_min))
			{
				const int increaseCount = duration_min / m_interval_min;

				m_a += 3 * increaseCount;
				m_b += 3 * increaseCount;
				m_c += 3 * increaseCount;
				m_d += 1 * increaseCount;
				m_timeStamp = NowDateTimeUntilMin();
			}
		}

		Milliseconds getDuration_ms()const
		{
			return DurationCast<Milliseconds>(NowDateTimeUntilMin() - m_timeStamp);
		}

		bool isOverInterval(const Minutes& _min)
		{
			return _min >= m_interval_min;
		}

		String toString()const
		{
			return Format(U"(", getA(), U",", getB(), U",", getC(), U",", getD(), U")");
		}
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Resource& r)
	{
		return os << CharType('(') << r.getA() << CharType(',') << r.getB() << CharType(',') << r.getC() << CharType(',') << r.getD() << CharType(',') << r.getTimeStamp().format() << CharType(')');
	}

}
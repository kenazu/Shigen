#pragma once
# include <Siv3D.hpp>

DateTime StringToDateTime(const String& _dateStr)
{
	const auto splitDateTime = _dateStr.split(U' ');

	if (splitDateTime.size() != 2) { return DateTime(); }

	const auto splitDate = splitDateTime[0].split(U'/');
	const auto splitTime = splitDateTime[1].split(U':');

	if (splitDate.size() != 3 || splitTime.size() != 3) { return DateTime(); }

	const int32 year = Parse<int32>(splitDate[0]);
	const int32 month = Parse<int32>(splitDate[1]);
	const int32 date = Parse<int32>(splitDate[2]);

	const int32 hour = Parse<int32>(splitTime[0]);
	const int32 min = Parse<int32>(splitTime[1]);
	const int32 sec = Parse<int32>(splitTime[2]);

	const DateTime datetime(year, month, date, hour, min, sec);

	return datetime;
}

const DateTime NowDateTimeUntilMin()
{
	DateTime datetime = DateTime::Now();
	datetime.second = 0;
	datetime.milliseconds = 0;
	return datetime;
}


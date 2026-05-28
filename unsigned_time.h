#ifndef UNSIGNEDTIME_H
#define UNSIGNEDTIME_H

#include "time.h"

// Set UNSIGNEDTIME to 0 to revert to standard time library
#define UNSIGNEDTIME 1 
#if UNSIGNEDTIME

typedef unsigned long us_time_t;

#define time_t us_time_t
#define time(t) us_time(t)
#define gmtime(t) us_gmtime(t)
#define localtime(t) us_localtime(t)
#define mktime(tm) us_mktime(tm)
#define _mkgmtime(tm) us_mkgmtime(tm)
#define ctime(t) us_ctime(t)
#define difftime(t1,t2) us_difftime((t1),(t2))
#define gmtime_s(tm,t) us_gmtime_s((tm),(t))
#define localtime_s(tm,t) us_localtime_s((tm),(t))
#define ctime_s(str,len,t) us_ctime_s((str),(len),(t))


static us_time_t
us_time(us_time_t* timer)
{
	us_time_t t;
	__time64_t t64;
	_time64(&t64);
	t = (us_time_t)t64;
	if (timer) *timer = t;
	return t;
}

static struct tm*
_us_gettm(const us_time_t* timer, int local)
{
	us_time_t t;
	__time64_t t64;
	static struct tm tm;

	memset(&tm, 0, sizeof(tm));

	if (timer) {
		t = *timer;
	}
	else {
		t = us_time(NULL);
	}
	t64 = t;

	if (local) {
		_localtime64_s(&tm, &t64);
	}
	else {
		_gmtime64_s(&tm, &t64);
	}
	return &tm;
}

static struct tm*
us_localtime(const us_time_t* timer)
{
	return _us_gettm(timer, 1);
}

static struct tm*
us_gmtime(const us_time_t* timer)
{
	return _us_gettm(timer, 0);
}

static us_time_t
us_mktime(struct tm* time)
{
	__time64_t t64 = _mktime64(time);
	return (us_time_t)t64;
}

static us_time_t
us_mkgmtime(struct tm* timeptr)
{
	__time64_t t64 = _mkgmtime64(timeptr);
	return (us_time_t)t64;
}

static char*
us_ctime(const us_time_t* time)
{
	__time64_t t64 = _time64(NULL);
	if (time) t64 = *time;
#ifdef _CRT_SECURE_NO_WARNINGS
#pragma warning(suppress : 4996)
	return _ctime64(&t64);
#else // _CRT_SECURE_NO_WARNINGS
	{
		static char rval[256];
		_ctime64_s(rval, sizeof(rval), &t64);
		return rval;
	}
#endif // _CRT_SECURE_NO_WARNINGS
}

static double
us_difftime(us_time_t end, us_time_t beginning)
{
	__time64_t t64_end = end, t64_beg = beginning;
	return _difftime64(t64_end, t64_beg);
}

static int
us_gmtime_s(struct tm* const _Tm, const us_time_t* const timer)
{
	__time64_t t64 = _time64(NULL);
	if (timer) t64 = *timer;
	return _gmtime64_s(_Tm, &t64);
}

static int
us_localtime_s(struct tm* const _Tm, const us_time_t* const timer)
{
	__time64_t t64 = _time64(NULL);
	if (timer) t64 = *timer;
	return _localtime64_s(_Tm, &t64);
}

static int
us_ctime_s(char* const _Buffer, size_t const _SizeInBytes, us_time_t const* const _Time)
{
	__time64_t t64 = _time64(NULL);
	if (_Time) t64 = *_Time;
	return _ctime64_s(_Buffer, _SizeInBytes, &t64);
}

#endif // UNSIGNEDTIME
#endif // UNSIGNEDTIME_H


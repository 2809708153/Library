#pragma once
#include <ctime>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define TM_YEAR_BASE 1900
#define ALT_E     0x01
#define ALT_O     0x02
#define LEGAL_ALT(x)    { if (alt_format & ~(x)) return (0); }

static  int conv_num(const char **, int *, int, int);
static const char *day[7] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday"
};
static const char *abday[7] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};
static const char *mon[12] = {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};
static const char *abmon[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static const char *am_pm[2] = {
    "AM", "PM"
};
//window上自己实现strptime函数，linux已经提供strptime
//strptime函数windows平台上实现
char *strptime(const char *buf, const char *fmt, struct tm *tm);
static int conv_num(const char **buf, int *dest, int llim, int ulim)
{
    int result = 0;

    int rulim = ulim;

    if (**buf < '0' || **buf > '9')
        return (0);

    do {
        result *= 10;
        result += *(*buf)++ - '0';
        rulim /= 10;
    } while ((result * 10 <= ulim) && rulim && **buf >= '0' && **buf <= '9');

    if (result < llim || result > ulim)
        return (0);

    *dest = result;
    return (1);
}

#define ARDRONE_DATE_MAXSIZE    32
#define ARDRONE_FILE_DATE_FORMAT    "%Y%m%d_%H%M%S"
#define ARDRONE_DEFAULT_DATE        "19700101_000000"
void yunshouhu_time2date(time_t time, const char *format, char *date);
void yunshouhu_date2time(char *date, const char *format, time_t *time);
char *format_date_time(time_t datetime, char *format);


#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <ctime>

#ifdef __cplusplus
extern "C" {
#endif

int timeOffset = -5;

static String tmToTimeString(const tm &timeStruct) {
    // Format hours and minutes into a string
    char timeString[6]; // Enough to hold "HH:MM\0"
    sprintf(timeString, "%02d:%02d", timeStruct.tm_hour, timeStruct.tm_min);

    // Convert char array to String
    return String(timeString);
}

  static bool isLeapYear(int year)
  {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
  }

  // Function to calculate the total seconds since epoch (January 1, 1970)
  static time_t totalSecondsSinceEpoch(const tm &timeinfo)
  {
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    time_t totalSeconds = 0;

     // Add seconds from years
    for (int year = 1970; year < timeinfo.tm_year; ++year)
    {
      totalSeconds += isLeapYear(year) ? 366 * 24 * 60 * 60 : 365 * 24 * 60 * 60;
    }

    // Add seconds from months
    for (int month = 1; month < timeinfo.tm_mon + 1; ++month)
    {
      totalSeconds += daysInMonth[month] * 24 * 60 * 60;
      if (month == 2 && isLeapYear(timeinfo.tm_year))
        totalSeconds += 24 * 60 * 60; // Add one day for leap year February
    }

    // Add seconds from days, hours, minutes, and seconds
    totalSeconds += (timeinfo.tm_mday - 1) * 24 * 60 * 60;
    totalSeconds += timeinfo.tm_hour * 60 * 60;
    totalSeconds += timeinfo.tm_min * 60;
    totalSeconds += timeinfo.tm_sec;

    return totalSeconds;
  }

  static tm secondsToTm(time_t totalSeconds)
  {
    tm timeinfo;
    timeinfo = *gmtime(&totalSeconds);
    timeinfo.tm_year = timeinfo.tm_year + 1900;
    return timeinfo;
  }

  static tm utcToTimeWithOffset(const tm &date)
  {
    const int SECONDS_PER_HOUR = 3600;
    const int SECONDS_PER_DAY = 24 * SECONDS_PER_HOUR;

    // Calculate total seconds from the given tm structure
    long totalSeconds = totalSecondsSinceEpoch(date);

    // Add hours to total seconds
    totalSeconds += timeOffset * SECONDS_PER_HOUR;

    // Calculate new time components
    tm convertedTimeinfo = secondsToTm(totalSeconds);

    return convertedTimeinfo;
  }

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Entities/Date.h"

// Class generated with the help of the ChatGPT
int is_leap_year(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int is_date_valid(Date date) {
  int is_day_valid = date.day >= 1 && date.day <= 31;
  int is_month_valid = date.month >= 1 && date.month <= 12;
  int is_year_valid = date.year >= 1900 && date.year <= 2100;

  if (!is_day_valid || !is_month_valid || !is_year_valid) {
    return 0;
  }

  // date specific validations
  int is_day_valid_for_month = 1;

  switch (date.month) {
  case 2:
    if (is_leap_year(date.year)) {
      is_day_valid_for_month = date.day <= 29;
    } else {
      is_day_valid_for_month = date.day <= 28;
    }
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    is_day_valid_for_month = date.day <= 30;
    break;
  default:
    is_day_valid_for_month = date.day <= 31;
    break;
  }

  return is_day_valid_for_month;
}

void parse_date(const char *date_str, Date *date) {
  sscanf(date_str, "%2d/%2d/%4d", &date->day, &date->month, &date->year);
}

char *date_to_string(Date date) {
  char *buffer = malloc(11);

  if (buffer == NULL) {
    perror("ERROR: Failed to allocate memory for date string");
    exit(EXIT_FAILURE);
  }

  snprintf(buffer, 11, "%02d/%02d/%04d", date.day, date.month, date.year);
  return buffer;
}
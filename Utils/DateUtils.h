#pragma once

#include "../Entities/Date.h"

int is_date_valid(Date date);

void parse_date(const char *date_str, Date *date);
char *date_to_string(Date date);
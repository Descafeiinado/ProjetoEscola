#pragma once

#include <stdbool.h>

#include "../Entities/Date.h"

bool is_date_valid(Date date);

void parse_date(const char *date_str, Date *date);
char *date_to_string(Date date);
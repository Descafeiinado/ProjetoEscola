#pragma once

#include "../../../Entities/Course.h"

void handle_fetch_specific_course(void (*then)(Course), void (*back)(char *));
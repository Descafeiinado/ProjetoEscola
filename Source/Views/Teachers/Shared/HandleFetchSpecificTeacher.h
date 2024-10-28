#pragma once

#include "../../../Entities/Person.h"

void handle_fetch_specific_teacher(void (*then)(Person), void (*back)(char *));
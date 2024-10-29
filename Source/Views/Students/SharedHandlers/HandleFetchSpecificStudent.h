#pragma once

#include "../../../Entities/Person.h"

void handle_fetch_specific_student(void (*then)(Person), void (*back)(char *));
#pragma once

#include "../Entities/Course.h"

void course_from_persistence(Course *course, char *content);
void course_to_persistence(char *buffer, Course course);
#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "../Entities/Course.h"

bool course_exists(char *id);

int persist_course(Course course);
int update_course(char *id, Course course);
int remove_course(char *id);

int get_all_courses_of_student(char *student_registration);

Course get_course(char *id);

int get_all_courses(Course courses[]);
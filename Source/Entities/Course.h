#pragma once

#include "Person.h"

#define MAX_COURSE_ID_SIZE 9
#define MAX_COURSE_NAME_SIZE 128

#define MAX_COURSE_STUDENTS 80

typedef struct course_struct {
  char id[MAX_COURSE_ID_SIZE];
  char name[MAX_COURSE_NAME_SIZE];

  int period;

  char teacher_registration[MAX_PERSON_REGISTRATION_SIZE];

  Person students[MAX_COURSE_STUDENTS];
  int students_amount;
} Course;

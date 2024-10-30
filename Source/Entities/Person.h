#pragma once
#include "../Utils/DateUtils.h"

#define MAX_PERSON_REGISTRATION_SIZE 32
#define MAX_PERSON_NAME_SIZE 128
#define MAX_PERSON_IDENTIFICATION_SIZE 14

typedef struct person_struct {
  char registration[MAX_PERSON_REGISTRATION_SIZE];
  char name[MAX_PERSON_NAME_SIZE];

  char identification[MAX_PERSON_IDENTIFICATION_SIZE]; // CPF (Identification)

  char gender[1];
  Date birthday;
} Person;

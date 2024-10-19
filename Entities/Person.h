#pragma once
#include "../Utils/DateUtils.h"

#define MAX_REGISTRATION_SIZE 32
#define MAX_NAME_SIZE 128
#define MAX_IDENTIFICATION_SIZE 14

typedef struct person_struct {
  char registration[MAX_REGISTRATION_SIZE];
  char name[MAX_NAME_SIZE];

  char identification[MAX_IDENTIFICATION_SIZE]; // CPF (Identification)

  char gender[1];
  Date birthday;
} Person;

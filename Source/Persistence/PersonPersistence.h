#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "../Entities/Person.h"

bool person_exists0(const char *file, char *registration);
bool person_exists(const char *file, Person person);

int persist_person(const char *file, Person person);
int update_person(const char *file, char *registration, Person person);
int remove_person(const char *file, char *registration);

Person get_person(const char *file, char *registration);

int get_all_persons(const char *file, Person persons[]);
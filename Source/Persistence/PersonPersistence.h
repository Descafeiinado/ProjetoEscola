#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "../Entities/Person.h"

int persist_person(const char *file, Person person);
int update_person(const char *file, Person original, Person updated);
int remove_person(const char *file, char *registration);

bool person_exists0(const char *file, char *registration);
bool person_exists(const char *file, Person person);

Person get_person(const char *file, char *registration);

int get_all_persons(const char *file, Person persons[]);
#pragma once

#include "../Entities/Person.h"

void person_from_persistence(Person *person, char *content);
void person_to_persistence(char *buffer, Person person);
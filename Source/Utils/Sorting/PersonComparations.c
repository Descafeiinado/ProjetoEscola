#include <string.h>

#include "../../Persistence/PersonPersistence.h"

int compare_persons_by_name(const void *a, const void *b) {
  Person *person_a = (Person *)a;
  Person *person_b = (Person *)b;

  return strcmp(person_a->name, person_b->name);
}

int compare_persons_by_birthday(const void *a, const void *b) {
  Person *person_a = (Person *)a;
  Person *person_b = (Person *)b;

  Date *a_birthday = &person_a->birthday;
  Date *b_birthday = &person_b->birthday;

  if (a_birthday->year != b_birthday->year) 
    return a_birthday->year - b_birthday->year;

  if (a_birthday->month != b_birthday->month) 
    return a_birthday->month - b_birthday->month;
    
  return a_birthday->day - b_birthday->day;
}

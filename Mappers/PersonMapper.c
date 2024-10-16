#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Entities/Person.h"

#define ATTRIBUTE_SEPARATOR 31

// Class generated with the help of the ChatGPT

// Receive a Person and a serialized Person and reconstructs the Person
void person_from_persistence(Person *person, char *content) {
  char attribute_separator_character[] = {ATTRIBUTE_SEPARATOR};

  int index = 0;
  char *token;

  token = strtok(content, attribute_separator_character);

  while (token != NULL) {
    switch (index) {
    case 0:
      strcpy(person->registration, token);
      break;
    case 1:
      strcpy(person->name, token);
      break;
    case 2:
      strcpy(person->identification, token);
      break;
    case 3:
      if (strlen(token) > 0) {
        person->gender[0] = token[0];
      }
      break;
    case 4:
      parse_date(token, &person->birthday);
      break;
    default:
      break;
    }

    token = strtok(NULL, attribute_separator_character);
    index++;
  }
}

void person_to_persistence(char *buffer, Person person) {
  char attribute_separator_character[1] = {ATTRIBUTE_SEPARATOR};

  int size = MAX_REGISTRATION_SIZE + 1 + MAX_NAME_SIZE + 1 +
             MAX_IDENTIFICATION_SIZE + 1 + 2 + 10;

  char *content = malloc(size);

  if (content == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  sprintf(content, "%s%s%s%s%s%s%c%s%s", person.registration,
          attribute_separator_character, person.name,
          attribute_separator_character, person.identification,
          attribute_separator_character, person.gender[0],
          attribute_separator_character, date_to_string(person.birthday));

  strcat(content, "\0");
  strcpy(buffer, content);

  free(content);
}
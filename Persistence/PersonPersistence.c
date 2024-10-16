#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../Mappers/PersonMapper.h"

#define MAX_PERSON_LINE_LENGTH 550

#define ENTITY_SEPARATOR 10
#define ENTITY_INDEXER_SEPARATOR 29

char *get_database_prefix() { return getcwd(NULL, 0); }
char *concat_database_file_name(const char *file) {
  char *database_prefix = get_database_prefix();

  char *database_file = malloc(strlen(database_prefix) + strlen(file) + 1);

  if (!database_file) {
    perror("ERROR: Failed to allocate memory for database file");
    exit(EXIT_FAILURE);
  }

  sprintf(database_file, "%s%s", database_prefix, file);

  return database_file;
}

char *generate_person_indexer0(char *registration) {
  char *buffer = malloc(MAX_REGISTRATION_SIZE + 1);

  if (!buffer) {
    perror("ERROR: Failed to allocate memory for indexer");
    exit(EXIT_FAILURE);
  }

  char entity_indexer_separator_character[1] = {ENTITY_INDEXER_SEPARATOR};

  sprintf(buffer, "%s%c", registration, ENTITY_INDEXER_SEPARATOR);

  return buffer;
}

char *generate_person_indexer(Person person) {
  return generate_person_indexer0(person.registration);
}

int persist_person(const char *file, Person person) {
  char serialized_person_buffer[512];

  person_to_persistence(serialized_person_buffer, person);

  char *final_file_name = concat_database_file_name(file);
  FILE *file_pointer = fopen(final_file_name, "a+");

  char *entity_indexer = generate_person_indexer(person);
  char *entity_persistence_buffer =
      malloc(strlen(serialized_person_buffer) + strlen(entity_indexer) + 1);

  if (!entity_persistence_buffer) {
    printf("ERROR: Failed to allocate memory for entity persistence buffer");
    return 1;
  }

  sprintf(entity_persistence_buffer, "%s%s", entity_indexer,
          serialized_person_buffer);

  if (file_pointer)
    fputs(entity_persistence_buffer, file_pointer);
  else {
    printf("ERROR: Failed to open file %s", final_file_name);
    return 2;
  }

  return 0;
}

int get_all_persons(const char *file, Person persons[]) {
  char *final_file_name = concat_database_file_name(file);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 0;

  int amount;
  char *content;

  fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);

  do {
    Person person;

    person_from_persistence(&person, content);
    persons[amount] = person;

    amount++;
  } while (!feof(file_pointer));

  return amount;
}
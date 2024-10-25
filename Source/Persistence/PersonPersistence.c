#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../Mappers/PersonMapper.h"

#define MAX_PERSON_LINE_LENGTH 256

#define ENTITY_SEPARATOR 10
#define ENTITY_INDEXER_SEPARATOR 62
// 155
char *get_database_prefix() { return getcwd(NULL, 0); }
char *concat_database_file_name(const char *file) {
  char *database_prefix = get_database_prefix();
  int size = strlen(database_prefix) + strlen(file) + 1;
  
  char *database_file = calloc(1, size);

  sprintf(database_file, "%s%s", database_prefix, file);

  return database_file;
}

bool person_exists0(const char *file, char *registration) {
  char *final_file_name = concat_database_file_name(file);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return false;

  char *content = calloc(1, MAX_PERSON_LINE_LENGTH);

  fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);

  do {
    Person person;

    person_from_persistence(&person, content);

    if (strcmp(person.registration, registration) == 0) {
      fclose(file_pointer);
      return true;
    }

    fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);
  } while (!feof(file_pointer));

  fclose(file_pointer);

  return false;
}

bool person_exists(const char *file, Person person) {
  return person_exists0(file, person.registration);
}

int persist_person(const char *file, Person person) {
  char *serialized_person_buffer = calloc(1, MAX_PERSON_LINE_LENGTH);

  person_to_persistence(serialized_person_buffer, person);

  char *final_file_name = concat_database_file_name(file);
  FILE *file_pointer = fopen(final_file_name, "a+");

  int entity_persistence_buffer_size =
   (strlen(serialized_person_buffer) * sizeof(char)) +
   sizeof(char);
  char *entity_persistence_buffer = calloc(1, entity_persistence_buffer_size);

  int result = 0;

  sprintf(entity_persistence_buffer, "%s%c",
          serialized_person_buffer, ENTITY_SEPARATOR);

  if (file_pointer) {
    if (person_exists0(file, person.registration)) 
      result = 3;
    else fputs(entity_persistence_buffer, file_pointer);

  } else {
    printf("ERROR: Failed to open file %s", final_file_name);
    result = 2;
  }

  fclose(file_pointer);

  free(entity_persistence_buffer);
  free(serialized_person_buffer);

  return 0;
}

int update_person(const char *file, char *registration, Person person) {
  char *final_file_name = concat_database_file_name(file);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 1;

  char *content = calloc(1, MAX_PERSON_LINE_LENGTH);

  fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);

  int line_number = 0;
  char *line_to_update = NULL;

  do {
    Person person;

    person_from_persistence(&person, content);

    if (strcmp(person.registration, registration) == 0) {
      line_to_update = calloc(1, MAX_PERSON_LINE_LENGTH);
      strcpy(line_to_update, content);
      break;
    }

    fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);
    line_number++;
  } while (!feof(file_pointer));

  fclose(file_pointer);

  if (line_to_update) {
    file_pointer = fopen(final_file_name, "r");

    FILE *temp_file = fopen("temp.txt", "w");

    int current_line = 0;

    while (fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer)) {
      if (current_line != line_number)
        fputs(content, temp_file);
      else {
        char *serialized_person_buffer = calloc(1, MAX_PERSON_LINE_LENGTH);

        person_to_persistence(serialized_person_buffer, person);

        char *entity_persistence_buffer = calloc(1, MAX_PERSON_LINE_LENGTH);

        sprintf(entity_persistence_buffer, "%s%c",
                serialized_person_buffer, ENTITY_SEPARATOR);

        fputs(entity_persistence_buffer, temp_file);

        free(serialized_person_buffer);
        free(entity_persistence_buffer);
      }

      current_line++;
    }

    fclose(file_pointer);
    fclose(temp_file);

    remove(final_file_name);
    rename("temp.txt", final_file_name);

    free(line_to_update);
  }

  free(content);

  return 0;
}

int remove_person(const char *file, char *registration) {
  char *final_file_name = concat_database_file_name(file);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 1;

  char *content = calloc(1, MAX_PERSON_LINE_LENGTH);

  fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);

  int line_number = 0;
  char *line_to_delete = NULL;

  do {
    Person person;

    person_from_persistence(&person, content);

    if (strcmp(person.registration, registration) == 0) {
      line_to_delete = calloc(1, MAX_PERSON_LINE_LENGTH);
      strcpy(line_to_delete, content);
      break;
    }

    fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);
    line_number++;
  } while (!feof(file_pointer));

  fclose(file_pointer);

  if (line_to_delete) {
    file_pointer = fopen(final_file_name, "r");

    FILE *temp_file = fopen("temp.txt", "w");

    int current_line = 0;

    while (fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer)) {
      if (current_line != line_number)
        fputs(content, temp_file);

      current_line++;
    }

    fclose(file_pointer);
    fclose(temp_file);

    remove(final_file_name);
    rename("temp.txt", final_file_name);

    free(line_to_delete);
  }

  free(content);

  return 0;
}

Person get_person(const char *file, char *registration) {
  char *final_file_name = concat_database_file_name(file);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return (Person){};

  char *content = calloc(1, MAX_PERSON_LINE_LENGTH);

  fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);

  do {
    Person person;

    person_from_persistence(&person, content);

    if (strcmp(person.registration, registration) == 0) {
      fclose(file_pointer);
      return person;
    }

    fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);
  } while (!feof(file_pointer));

  fclose(file_pointer);

  return (Person){};
}

int get_all_persons(const char *file, Person persons[]) {
  char entity_indexer_separator_character = ENTITY_INDEXER_SEPARATOR;

  char *final_file_name = concat_database_file_name(file);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 0;

  int amount = 0;
  char *content = calloc(1, MAX_PERSON_LINE_LENGTH);

  fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);

  do {
    Person person;

    person_from_persistence(&person, content);

    persons[amount] = person;
    amount++;
      
    fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);
  } while (!feof(file_pointer));

  fclose(file_pointer);

  return amount;
}
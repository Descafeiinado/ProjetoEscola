#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../Mappers/PersonMapper.h"

#define MAX_PERSON_LINE_LENGTH 550

#define ENTITY_SEPARATOR 10
#define ENTITY_INDEXER_SEPARATOR 62
// 155
char *get_database_prefix() { return getcwd(NULL, 0); }
char *concat_database_file_name(const char *file) {
  char *database_prefix = get_database_prefix();
  int size = strlen(database_prefix) + strlen(file) + 1;
  
  char database_file[size];

  sprintf(database_file, "%s%s", database_prefix, file);

  return *database_file;
}

char *generate_person_indexer0(char *registration) {
  int size = MAX_REGISTRATION_SIZE + 1;
  char buffer[size];

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

  int entity_persistence_buffer_size =
   (strlen(serialized_person_buffer) * sizeof(char)) +
   (strlen(entity_indexer) * sizeof(char)) +
   sizeof(char);
  char entity_persistence_buffer[entity_persistence_buffer_size];

  int result = 0;

  sprintf(entity_persistence_buffer, "%s%s%c", entity_indexer,
          serialized_person_buffer, ENTITY_SEPARATOR);

  if (file_pointer)
    fputs(entity_persistence_buffer, file_pointer);
  else {
    printf("ERROR: Failed to open file %s", final_file_name);
    result = 2;
  }

  fclose(file_pointer);

  return 0;
}

int get_all_persons(const char *file, Person persons[]) {
  char entity_indexer_separator_character[1] = {ENTITY_INDEXER_SEPARATOR};

  char *final_file_name = concat_database_file_name(file);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 0;

  int amount;
  char *content;

  fgets(content, MAX_PERSON_LINE_LENGTH, file_pointer);

  do {
    Person person;

    int part_index;
    char* effective_content;

    char* token = strtok(content, entity_indexer_separator_character);

    while (token != NULL) {
      if (part_index == 1) {
        puts(token);
        person_from_persistence(&person, token);
        persons[amount] = person;

        amount++;
      }

      part_index++;
      token = strtok(NULL, entity_indexer_separator_character);
    }
    
  } while (!feof(file_pointer));

  fclose(file_pointer);

  return amount;
}
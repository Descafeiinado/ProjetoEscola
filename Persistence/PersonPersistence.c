#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../Mappers/PersonMapper.h"

#define MAX_PERSON_LINE_LENGTH 550

#define ENTITY_SEPARATOR 10
#define ENTITY_INDEXER_SEPARATOR 62
char *get_database_prefix() { return getcwd(NULL, 0); }
char *concat_database_file_name(const char *file) {
  char *database_prefix = get_database_prefix();
  int size = strlen(database_prefix) + strlen(file) + 1;
  
  printf("Size: %d", size);

  char database_file[size];

  sprintf(database_file, "%s%s", database_prefix, file);

  printf("DatabaseFile: %s", database_file);

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
  int serialized_person_buffer_size = MAX_REGISTRATION_SIZE + 1 + MAX_NAME_SIZE + 1 + MAX_IDENTIFICATION_SIZE + 1 + 2 + 10;
  char serialized_person_buffer[serialized_person_buffer_size];

  printf("Serialized Buffer Size: %d", serialized_person_buffer_size);

  person_to_persistence(serialized_person_buffer, person);

  printf("Serialized Buffer: %s", serialized_person_buffer);

  char *final_file_name = concat_database_file_name(file);
  FILE *file_pointer = fopen(final_file_name, "a+");

  printf("Final File Name: %s", final_file_name);

  char *entity_indexer = generate_person_indexer(person);

  printf("Entity Indexer: %s", entity_indexer);

  int entity_persistence_buffer_size =
   strlen(serialized_person_buffer) + strlen(entity_indexer) + 1;
  char entity_persistence_buffer[entity_persistence_buffer_size];

  printf("Entity Persistence Buffer Size: %d", entity_persistence_buffer_size);

  int result = 0;

  sprintf(entity_persistence_buffer, "%s%s%c", entity_indexer,
          serialized_person_buffer, ENTITY_SEPARATOR);

  printf("Entity Persistence Buffer: %s", entity_persistence_buffer);

  if (file_pointer)
    fputs(entity_persistence_buffer, file_pointer);
  else {
    printf("ERROR: Failed to open file %s", final_file_name);
    result = 2;
  }

  puts("Wrote");

  fclose(file_pointer);

  puts("Flushed");

  return 0;
}

int get_all_persons(const char *file, Person persons[]) {
  printf("oi");
  char entity_indexer_separator_character = ENTITY_INDEXER_SEPARATOR;

  char *final_file_name = concat_database_file_name(file);

  printf("Final File Name: %s", final_file_name);

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
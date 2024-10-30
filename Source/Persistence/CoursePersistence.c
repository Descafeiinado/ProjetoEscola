#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../Constants/CourseConstants.h"
#include "../Mappers/CourseMapper.h"

#define MAX_COURSE_LINE_LENGTH 2048

#define ENTITY_SEPARATOR 10

char *get_courses_database_prefix() { return getcwd(NULL, 0); }
char *concat_courses_database_file_name() {
  char *database_prefix = get_courses_database_prefix();
  int size = strlen(database_prefix) + strlen(COURSES_DATABASE_FILE) + 1;
  
  char *database_file = calloc(1, size);

  sprintf(database_file, "%s%s", database_prefix, COURSES_DATABASE_FILE);

  return database_file;
}

bool course_exists(char *id) {
  char *final_file_name = concat_courses_database_file_name(COURSES_DATABASE_FILE);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return false;

  char *content = calloc(1, MAX_COURSE_LINE_LENGTH);

  fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);

  do {
    Course course;

    course_from_persistence(&course, content);

    if (strcmp(course.id, id) == 0) {
      fclose(file_pointer);
      return true;
    }

    fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);
  } while (!feof(file_pointer));

  fclose(file_pointer);

  return false;
}

int persist_course(Course course) {
  char *serialized_course_buffer = calloc(1, MAX_COURSE_LINE_LENGTH);

  course_to_persistence(serialized_course_buffer, course);

  char *final_file_name = concat_courses_database_file_name(COURSES_DATABASE_FILE);
  FILE *file_pointer = fopen(final_file_name, "a+");

  int entity_persistence_buffer_size =
   (strlen(serialized_course_buffer) * sizeof(char)) +
   sizeof(char);
  char *entity_persistence_buffer = calloc(1, entity_persistence_buffer_size);

  int result = 0;

  sprintf(entity_persistence_buffer, "%s%c",
          serialized_course_buffer, ENTITY_SEPARATOR);

  if (file_pointer) {
    if (course_exists(course.id)) 
      result = 3;
    else fputs(entity_persistence_buffer, file_pointer);

  } else {
    printf("ERROR: Failed to open file %s", final_file_name);
    result = 2;
  }

  fclose(file_pointer);

  free(entity_persistence_buffer);
  free(final_file_name);
  free(serialized_course_buffer);

  return 0;
}

int update_course(char *id, Course course) {
  char *final_file_name = concat_courses_database_file_name(COURSES_DATABASE_FILE);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 1;

  char *content = calloc(1, MAX_COURSE_LINE_LENGTH);

  fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);

  int line_number = 0;
  char *line_to_update = NULL;

  do {
    Course course;

    course_from_persistence(&course, content);

    if (strcmp(course.id, id) == 0) {
      line_to_update = calloc(1, MAX_COURSE_LINE_LENGTH);
      strcpy(line_to_update, content);
      break;
    }

    fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);
    line_number++;
  } while (!feof(file_pointer));

  fclose(file_pointer);

  if (line_to_update) {
    file_pointer = fopen(final_file_name, "r");

    FILE *temp_file = fopen("temp.txt", "w");

    int current_line = 0;

    while (fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer)) {
      if (current_line != line_number)
        fputs(content, temp_file);
      else {
        char *serialized_course_buffer = calloc(1, MAX_COURSE_LINE_LENGTH);

        course_to_persistence(serialized_course_buffer, course);

        char *entity_persistence_buffer = calloc(1, MAX_COURSE_LINE_LENGTH);

        sprintf(entity_persistence_buffer, "%s%c",
                serialized_course_buffer, ENTITY_SEPARATOR);

        fputs(entity_persistence_buffer, temp_file);

        free(serialized_course_buffer);
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
  free(final_file_name);
  
  return 0;
}

int remove_course(char *id) {
  char *final_file_name = concat_courses_database_file_name(COURSES_DATABASE_FILE);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 1;

  char *content = calloc(1, MAX_COURSE_LINE_LENGTH);

  fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);

  int line_number = 0;
  char *line_to_delete = NULL;

  do {
    Course course;

    course_from_persistence(&course, content);

    if (strcmp(course.id, id) == 0) {
      line_to_delete = calloc(1, MAX_COURSE_LINE_LENGTH);
      strcpy(line_to_delete, content);
      break;
    }

    fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);
    line_number++;
  } while (!feof(file_pointer));

  fclose(file_pointer);

  if (line_to_delete) {
    file_pointer = fopen(final_file_name, "r");

    FILE *temp_file = fopen("temp.txt", "w");

    int current_line = 0;

    while (fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer)) {
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
  free(final_file_name);

  return 0;
}

Course get_course(char *id) {
  char *final_file_name = concat_courses_database_file_name(COURSES_DATABASE_FILE);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return (Course){};

  char *content = calloc(1, MAX_COURSE_LINE_LENGTH);

  fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);

  do {
    Course course;

    course_from_persistence(&course, content);

    if (strcmp(course.id, id) == 0) {
      fclose(file_pointer);
      return course;
    }

    fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);
  } while (!feof(file_pointer));

  fclose(file_pointer);

  free(content);
  free(final_file_name);

  return (Course){};
}

int get_all_courses(Course courses[]) {
  char *final_file_name = concat_courses_database_file_name(COURSES_DATABASE_FILE);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 0;

  int amount = 0;
  char *content = calloc(1, MAX_COURSE_LINE_LENGTH);

  fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);

  do {
    Course *course = calloc(1, sizeof(Course));

    course->students_amount = 0;
    
    course_from_persistence(course, content);

    courses[amount] = *course;
    amount++;
      
    fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);
  } while (!feof(file_pointer));

  fclose(file_pointer);

  free(content);
  free(final_file_name);

  return amount;
}

int get_all_courses_of_student(char *student_registration) {
  char *final_file_name = concat_courses_database_file_name(COURSES_DATABASE_FILE);

  FILE *file_pointer = fopen(final_file_name, "r");

  if (!file_pointer)
    return 0;

  char *content = calloc(1, MAX_COURSE_LINE_LENGTH);
  char *courses = calloc(1, MAX_COURSE_LINE_LENGTH);

  fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);

  int amount = 0;

  do {
    Course course;

    course_from_persistence(&course, content);

    for (int i = 0; i < course.students_amount; i++) {
      Person student = course.students[i];

      if (strcmp(student.registration, student_registration) == 0) {
        amount++;
      }
    }

    fgets(content, MAX_COURSE_LINE_LENGTH, file_pointer);
  } while (!feof(file_pointer));

  fclose(file_pointer);

  free(content);
  free(final_file_name);

  return amount;
}
#define ATTRIBUTE_SEPARATOR 59
#define STUDENT_SEPARATOR 44

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Constants/PersonConstants.h"
#include "../Entities/Course.h"
#include "../Persistence/PersonPersistence.h"

#include "../Utils/StringUtils.h"

char *replace_new_line(char *string) {
  char *new_string = calloc(1, strlen(string) + 1);

  if (new_string == NULL) {
    perror("[School]~ Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  strcpy(new_string, string);

  remove_new_line(new_string);

  return new_string;
}

// Receive a Course and a serialized Course and reconstructs the Course
void course_from_persistence(Course *course, char *content) {
  memcpy(course->students, (Person[MAX_COURSE_STUDENTS]){{0}}, MAX_COURSE_STUDENTS * sizeof(Person));

  char attribute_separator_character[2] = {ATTRIBUTE_SEPARATOR, 0};
  char student_separator_character[2] = {STUDENT_SEPARATOR, 0};

  int field_index = 0;
  
  char *course_pointer;
  char *course_token = strtok(content, attribute_separator_character);

  while (course_token != NULL) {
    switch (field_index) {
    case 0:
      strcpy(course->id, course_token);
      break;
    case 1:
      strcpy(course->name, course_token);
      break;
    case 2:
      course->period = atoi(course_token);
      break;
    case 3:
      strcpy(course->teacher_registration, course_token);
      break;
    case 4:      
      int token_length = strlen(course_token);

      if (token_length <= 1) {
        course->students_amount = 0;
        break;
      }
      
      char string_copy[MAX_PERSON_REGISTRATION_SIZE];
      
      strcpy(string_copy, course_token);

      char *string_without_new_line = replace_new_line(string_copy);
      int token_effective_length = strlen(string_without_new_line);
      
      if (token_effective_length == 0) {
        course->students_amount = 0;
        break;
      }
      
      if (!strstr(string_without_new_line, "")) {
        if (person_exists0(STUDENTS_DATABASE_FILE, string_without_new_line)) {
          course->students[0] = get_person(STUDENTS_DATABASE_FILE, string_without_new_line);
          course->students_amount = 1;
        }
      } else {
        char *student_pointer;
        char *student_token = strtok_r(string_without_new_line, student_separator_character, &student_pointer);

        int student_index = 0;

        while (student_token != NULL) {  
          if (person_exists0(STUDENTS_DATABASE_FILE, student_token)) 
            course->students[student_index] = get_person(STUDENTS_DATABASE_FILE, student_token);

            student_token = strtok_r(NULL, student_separator_character, &student_pointer);
            student_index++;
        }

        course->students_amount = student_index;
      }

      break;
    default:
      break;
    }

    course_token = strtok(NULL, attribute_separator_character);
    field_index++;
  }
}

// Receive a Course and a buffer and serialize the Course into the buffer
void course_to_persistence(char *buffer, Course course) {
  char attribute_separator_character[2] = {ATTRIBUTE_SEPARATOR, 0};
  char student_separator_character[2] = {STUDENT_SEPARATOR, 0};
  
  int size = MAX_COURSE_ID_SIZE + 1 + MAX_COURSE_NAME_SIZE + 1 + 2
   + MAX_PERSON_REGISTRATION_SIZE + 1 + MAX_COURSE_STUDENTS * MAX_PERSON_REGISTRATION_SIZE + MAX_COURSE_STUDENTS;
  
  char *content = calloc(1, size);
  char *students = calloc(1, (course.students_amount + 1) * MAX_PERSON_REGISTRATION_SIZE + course.students_amount);

  if (content == NULL || students == NULL) {
    perror("[School]~ Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  if (course.students_amount > 0 && course.students != NULL) {
    for (int i = 0; i < course.students_amount; i++) {
      strcat(students, course.students[i].registration);

      if (i < course.students_amount - 1) strcat(students, student_separator_character);
    }
  } else strcpy(students, "");

  sprintf(content, "%s%s%s%s%d%s%s%s%s",
   course.id, attribute_separator_character,
   course.name, attribute_separator_character,
   course.period, attribute_separator_character,
   course.teacher_registration, attribute_separator_character,
   students);

  strcpy(buffer, content);

  free(content);
  free(students);
}
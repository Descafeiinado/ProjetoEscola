#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../Persistence/CoursePersistence.h"
#include "../../Utils/ClearScreen.h"

void handle_fetch_specific_course(void (*then)(Course), void (*back)(char *)) {
  fflush(stdin);
  clear_screen();
 
  Course course;
  bool is_course_found = false;

  char registration[MAX_PERSON_REGISTRATION_SIZE];

  while (!is_course_found) {
    printf("Insira o codigo da disciplina, ou digite 'cancelar' para voltar: ");
    scanf(" %14[^\n]", &registration);

    if (strcmp(registration, "cancelar") == 0) 
      return back(0);

    if (course_exists(registration)) {
      course = get_course(registration);
      is_course_found = true;
    } else printf("Disciplina nao encontrada.\n");
  }

  then(course);
}
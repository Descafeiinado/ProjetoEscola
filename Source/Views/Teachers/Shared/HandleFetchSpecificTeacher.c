#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../Utils/ClearScreen.h"

void handle_fetch_specific_teacher(void (*then)(Person), void (*back)(char *)) {
  fflush(stdin);
  clear_screen();
 
  Person teacher;
  bool is_teacher_found = false;

  char registration[MAX_PERSON_REGISTRATION_SIZE];

  while (!is_teacher_found) {
    printf("Insira a matricula do professor, ou digite 'cancelar' para voltar: ");
    scanf(" %14[^\n]", &registration);

    if (strcmp(registration, "cancelar") == 0) 
      return back(0);

    if (person_exists0(TEACHERS_DATABASE_FILE, registration)) {
      teacher = get_person(TEACHERS_DATABASE_FILE, registration);
      is_teacher_found = true;
    } else {
      printf("Professor nao encontrado.\n");
    }
  }

  then(teacher);
}
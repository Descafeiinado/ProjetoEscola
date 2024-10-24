#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../Utils/ClearScreen.h"

void handle_fetch_specific_student(void (*then)(Person)) {
  fflush(stdin);
  clear_screen();
 
  Person student;
  bool is_student_found = false;

  char registration[MAX_REGISTRATION_SIZE];

  while (!is_student_found) {
    printf("Insira a matricula do aluno: ");
    scanf(" %14[^\n]", &registration);

    if (person_exists0(STUDENTS_DATABASE_FILE, registration)) {
      student = get_person(STUDENTS_DATABASE_FILE, registration);
      is_student_found = true;
    } else {
      printf("Aluno nao encontrado.\n");
    }
  }

  then(student);
}
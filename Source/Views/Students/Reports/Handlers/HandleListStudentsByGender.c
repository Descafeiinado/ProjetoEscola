#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../StudentReportsView.h"
#include "Pages/StudentPageableHandler.h"

int index_of(char *array, char value) {
  for (int i = 0; i < sizeof(array); i++) {
    if (array[i] == value)
      return i;
  }

  return -1;
}

void handle_list_students_by_gender(char *message) {
  fflush(stdin);
  clear_screen();

  Person *students = malloc(100 * sizeof(Person));
  char *gender = malloc(10 * sizeof(char));

  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o genero do aluno (M/F/O), ou digite 'cancelar' para voltar: ");

    scanf(" %15[^\n]", gender);

    if (strcmp(gender, "cancelar") == 0)
      return render_student_reports_view(NULL);

    for (int i = 0; i < 3 && !is_gender_valid; i++) {
      if (gender[0] == valid_genders[i])
        is_gender_valid = 1;
    }

    if (!is_gender_valid)
      printf("O genero fornecido e invalido.\n");
  }

  int amount = get_all_persons(STUDENTS_DATABASE_FILE, students);

  printf("B uscando alunos por genero...\n");

  Person *students_by_gender = malloc(amount * sizeof(Person));
  int students_by_gender_position = 0;

  if (amount > 0) 
    for (int i = 0; i < amount; i++) {
      Person student = students[i];

      if (student.gender[0] == gender[0]) {
        students_by_gender[students_by_gender_position] = student;
        students_by_gender_position++;
    }
  }

  free(gender);
  free(students);

  handle_generate_student_pageable(1, students_by_gender_position, students_by_gender, &handle_list_students_by_gender);
}

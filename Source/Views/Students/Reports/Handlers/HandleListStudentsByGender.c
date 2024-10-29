#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../StudentReportsView.h"

void handle_list_students_by_gender(char *message) {
  fflush(stdin);
  clear_screen();

  Person *students = malloc(100 * sizeof(Person));
  
  char *gender = malloc(10 * sizeof(char));
  
  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o genero do aluno (M/F/O), ou digite 'cancelar' para voltar: ");

    scanf(" %10[^\n]", gender);

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

  Person *students_by_gender = malloc(amount * sizeof(Person));
  int students_by_gender_position = 0;

  if (amount > 0) 
    for (int i = 0; i < amount; i++) {
      Person student = students[i];

      if (strcmp(student.gender, gender) == 0) {
        students_by_gender[students_by_gender_position] = student;
        students_by_gender_position++;
      }
  }

  free(gender);
  free(students);

  fflush(stdin);
  clear_screen();

  printf("Listagem de alunos do sexo '%s':\n\n", gender);

  if (students_by_gender_position > 0) {
    for (int i = 0; i < students_by_gender_position; i++) {
      Person student = students_by_gender[i];

      printf("%s. %s\n", student.registration, student.name);
    }

    printf("\n");
    printf("Total de alunos: %d\n", students_by_gender_position);
  } else
    printf("Nao existem estudantes cadastrados.\n");

  printf("\n");
  printf("0 - Voltar\n");

  int view_option = -1;
  int is_awaiting_input = 1;

  while (view_option != 0 && is_awaiting_input == 1) {
    scanf("%d", &view_option);

    if (view_option < 0 || view_option > 4) {
      printf("Opcao invalida.\n");
      continue;
    }

    is_awaiting_input = 0;

    switch (view_option) {
    case 0:
      handle_list_students_by_gender(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

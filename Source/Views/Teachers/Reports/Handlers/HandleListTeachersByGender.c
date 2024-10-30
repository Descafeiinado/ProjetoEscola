#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../TeacherReportsView.h"

void handle_list_teachers_by_gender(char *message) {
  fflush(stdin);
  clear_screen();

  Person *teachers = calloc(1, 100 * sizeof(Person));
  char *gender = calloc(1, 10 * sizeof(char));

  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o genero do professor (M/F/O), ou digite 'cancelar' para voltar: ");

    scanf(" %15[^\n]", gender);

    if (strcmp(gender, "cancelar") == 0)
      return render_teacher_reports_view(NULL);

    for (int i = 0; i < 3 && !is_gender_valid; i++) {
      if (gender[0] == valid_genders[i])
        is_gender_valid = 1;
    }

    if (!is_gender_valid)
      printf("O genero fornecido e invalido.\n");
  }

  int amount = get_all_persons(TEACHERS_DATABASE_FILE, teachers);

  Person *teachers_by_gender = calloc(1, amount * sizeof(Person));
  int teachers_by_gender_position = 0;

  if (amount > 0) 
    for (int i = 0; i < amount; i++) {
      Person teacher = teachers[i];

      if (strcmp(teacher.gender, gender) == 0) {
        teachers_by_gender[teachers_by_gender_position] = teacher;
        teachers_by_gender_position++;
      }
  }

  free(gender);
  free(teachers);

  fflush(stdin);
  clear_screen();

  printf("Listagem de professores do sexo '%s':\n\n", gender);

  if (teachers_by_gender_position > 0) {
    for (int i = 0; i < teachers_by_gender_position; i++) {
      Person teacher = teachers_by_gender[i];

      printf("%s. %s\n", teacher.registration, teacher.name);
    }

    printf("\n");
    printf("Total de professores: %d\n", teachers_by_gender_position);
  } else
    printf("Nao existem professores cadastrados.\n");

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
      handle_list_teachers_by_gender(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

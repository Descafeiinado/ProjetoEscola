#define MAX_LISTING_SIZE 100

#include <stdio.h>
#include <stdlib.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../StudentReportsView.h"

void handle_list_students_sorted_by_creation_order() {
  fflush(stdin);
  clear_screen();

  Person *students = calloc(1, MAX_LISTING_SIZE * sizeof(Person));

  printf("Listagem de Alunos\n");
  printf("\n");

  int amount = get_all_persons(STUDENTS_DATABASE_FILE, students);

  if (amount > 0) {
    for (int i = 0; i < amount; i++) {
      Person student = students[i];

      printf("%s. %s\n", student.registration, student.name);
    }

    printf("\n");
    printf("Total de alunos: %d\n", amount);
  } else
    printf("Nao existem estudantes cadastrados.\n");

  printf("\n");
  printf("0 - Voltar\n");

  free(students);

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
      render_student_reports_view(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

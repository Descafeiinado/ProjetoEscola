#include <stdio.h>
#include <stdlib.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../TeacherReportsView.h"

void handle_list_teachers_sorted_by_creation_order() {
  fflush(stdin);
  clear_screen();

  Person *teachers;

  printf("Listagem de Professores\n");
  printf("\n");

  int amount = get_all_persons(TEACHERS_DATABASE_FILE, teachers);

  if (amount > 0) {
    for (int i = 0; i < amount; i++) {
      Person teacher = teachers[i];

      printf("%s. %s\n", teacher.registration, teacher.name);
    }

    printf("\n");
    printf("Total de professores: %d\n", amount);
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
      render_teacher_reports_view(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

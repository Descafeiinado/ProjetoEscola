#include <stdio.h>
#include <stdlib.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../TeacherManagementView.h"

void handle_delete_teacher(Person teacher) {
  fflush(stdin);
  clear_screen();

  Person *teachers;

  printf("Prestes a excluir o professor '%s - %s', digite:\n", teacher.registration, teacher.name);
  printf("\n");

  printf("1 - Para confirmar\n");
  printf("0 - Para cancelar\n");

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
      render_teacher_management_view("Operacao cancelada.");
      break;

    case 1:
      remove_person(TEACHERS_DATABASE_FILE, teacher.registration);
      render_teacher_management_view("Estudante excluido com sucesso.");
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

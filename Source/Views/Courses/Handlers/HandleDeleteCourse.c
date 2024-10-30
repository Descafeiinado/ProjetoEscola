#include <stdio.h>
#include <stdlib.h>

#include "../../../Persistence/CoursePersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../CourseManagementView.h"

void handle_delete_course(Course course) {
  fflush(stdin);
  clear_screen();

  Person *students;

  printf("Prestes a excluir a disciplina '%s - %s', digite:\n", course.id, course.name);
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
      render_course_management_view("Operacao cancelada.");
      break;

    case 1:
      remove_course(course.id);
      render_course_management_view("Disciplina excluida com sucesso.");
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

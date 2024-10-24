#include <stdio.h>
#include <stdlib.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../StudentManagementView.h"

void handle_delete_student(Person student) {
  fflush(stdin);
  clear_screen();

  Person *students;

  printf("Prestes a excluir o aluno '%s - %s', digite:\n", student.registration, student.name);
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
      render_student_management_view("Operacao cancelada.");
      break;

    case 1:
      remove_person(STUDENTS_DATABASE_FILE, student.registration);
      render_student_management_view("Estudante excluido com sucesso.");
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

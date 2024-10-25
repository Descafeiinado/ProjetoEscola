#include <stdio.h>
#include <stdlib.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../StudentReportsView.h"

void handle_detail_student(Person student) {
  fflush(stdin);
  clear_screen();

  printf("Detalhamento de estudante:\n");
  printf("\n");
  printf("Nome: %s (%s)\n", student.name, student.gender);
  printf("Matricula: %s\n", student.registration);
  printf("CPF: %s\n", student.identification);
  printf("Data de Nascimento: %02d/%02d/%04d\n", student.birthday.day,
         student.birthday.month, student.birthday.year);

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
      render_student_reports_view(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

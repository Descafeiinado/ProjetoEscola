#include <stdio.h>

#include "Handlers/HandleDetailStudent.h"
#include "Handlers/HandleListStudents.h"

#include "../Shared/HandleFetchSpecificStudent.h"

#include "../StudentManagementView.h"
#include "../../Utils/ClearScreen.h"

void render_student_reports_view(char *message) {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Relatorio de Alunos\n");
  printf("\n");
  printf("1 - Listar alunos\n");
  printf("2 - Detalhar aluno\n");
  printf("\n");
  
  if (message != NULL)
    printf("%s\n\n", message);

  printf("0 - Voltar\n");

  int view_option = -1;
  int is_awaiting_input = 1;

  while (view_option != 0 && is_awaiting_input == 1) {
    scanf("%d", &view_option);

    if (view_option < 0 || view_option > 2) {
      printf("Opcao invalida.\n");
      continue;
    }

    is_awaiting_input = 0;

    switch (view_option) {
    case 0:
      render_student_management_view(NULL);
      break;

    case 1:
      handle_list_students();
      break;

    case 2:
      handle_fetch_specific_student(&handle_detail_student, &render_student_reports_view);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
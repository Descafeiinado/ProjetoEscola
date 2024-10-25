#include <stdio.h>

#include "Handlers/HandleCreateStudent.h"
#include "Handlers/HandleDeleteStudent.h"
#include "Handlers/HandleUpdateStudent.h"

#include "Reports/StudentReportsView.h"

#include "Shared/HandleFetchSpecificStudent.h"

#include "../DefaultView.h"
#include "../Utils/ClearScreen.h"

void render_student_management_view(char *message) {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Alunos\n");
  printf("\n");
  printf("1 - Relatorios\n");
  printf("2 - Cadastrar Aluno\n");
  printf("3 - Atualizar Aluno\n");
  printf("4 - Excluir Aluno\n");
  printf("\n");

  if (message != NULL)
    printf("%s\n\n", message);

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
      render_default_view();
      break;

    case 1:
      render_student_reports_view(NULL);
      break;

    case 2:
      handle_create_student();
      break;

    case 3:
      handle_fetch_specific_student(&handle_update_student, &render_student_management_view);
      break;

    case 4:
      handle_fetch_specific_student(&handle_delete_student, &render_student_management_view);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
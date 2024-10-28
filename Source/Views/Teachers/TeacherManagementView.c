#include <stdio.h>

#include "Handlers/HandleCreateTeacher.h"
#include "Handlers/HandleDeleteTeacher.h"
#include "Handlers/HandleUpdateTeacher.h"

#include "Reports/TeacherReportsView.h"

#include "Shared/HandleFetchSpecificTeacher.h"

#include "../DefaultView.h"
#include "../Utils/ClearScreen.h"

void render_teacher_management_view(char *message) {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Professores\n");
  printf("\n");
  printf("1 - Relatorios\n");
  printf("2 - Cadastrar Professor\n");
  printf("3 - Atualizar Professor\n");
  printf("4 - Excluir Professor\n");
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
      render_teacher_reports_view(NULL);
      break;

    case 2:
      handle_create_teacher();
      break;

    case 3:
      handle_fetch_specific_teacher(&handle_update_teacher, &render_teacher_management_view);
      break;

    case 4:
      handle_fetch_specific_teacher(&handle_delete_teacher, &render_teacher_management_view);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
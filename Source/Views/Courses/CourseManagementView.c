#include <stdbool.h>
#include <stdio.h>

#include "Handlers/HandleCreateCourse.h"
#include "Handlers/HandleDeleteCourse.h"
#include "Handlers/HandleUpdateCourse.h"
#include "Reports/CourseReportsView.h"
#include "SharedHandlers/HandleFetchSpecificCourse.h"

#include "../DefaultView.h"
#include "../Utils/ClearScreen.h"

void render_course_management_view(char *message) {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Disciplinas\n");
  printf("\n");
  printf("1 - Relatorios\n");
  printf("2 - Cadastrar Disciplina\n");
  printf("3 - Atualizar Disciplina\n");
  printf("4 - Excluir Disciplina\n");
  printf("\n");

  if (message != NULL)
    printf("%s\n\n", message);

  printf("0 - Voltar\n");

  int view_option = -1;
  bool is_awaiting_input = true;

  while (view_option != 0 && is_awaiting_input) {
    scanf("%d", &view_option);

    if (view_option < 0 || view_option > 4) {
      printf("Opcao invalida.\n");
      continue;
    }

    is_awaiting_input = false;

    switch (view_option) {
    case 0:
      render_default_view();
      break;

    case 1:
      render_course_reports_view(NULL);
      break;

    case 2:
      handle_create_course();
      break;
    
    case 3:
      handle_fetch_specific_course(&handle_update_course, &render_course_management_view);
      break;

    case 4:
      handle_fetch_specific_course(&handle_delete_course, &render_course_management_view);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = true;
    }
  }
}
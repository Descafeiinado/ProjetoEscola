#include <stdio.h>

#include "../CourseManagementView.h"
#include "../SharedHandlers/HandleFetchSpecificCourse.h"
#include "../../Utils/ClearScreen.h"

#include "Handlers/HandleDetailCourse.h"
#include "Handlers/HandleListCoursesSortedByCreationOrder.h"
#include "Handlers/HandleListExceedingCourses.h"

void render_course_reports_view(char *message) {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Relatorio de Disciplinas\n");
  printf("\n");
  printf("1 - Detalhar disciplina\n");
  printf("2 - Listar disciplinas\n");
  printf("3 - Listar disciplinas excedentes\n");
  printf("\n");
  
  if (message != NULL)
    printf("%s\n\n", message);

  printf("0 - Voltar\n");

  int view_option = -1;
  int is_awaiting_input = 1;

  while (view_option != 0 && is_awaiting_input == 1) {
    scanf("%d", &view_option);

    if (view_option < 0 || view_option > 5) {
      printf("Opcao invalida.\n");
      continue;
    }

    is_awaiting_input = 0;

    switch (view_option) {
    case 0:
      render_course_management_view(NULL);
      break;

    case 1:
      handle_fetch_specific_course(&handle_detail_course, &render_course_reports_view);
      break;

    case 2:
      handle_list_courses_sorted_by_creation_order();
      break;

    case 3:
      handle_list_exceeding_courses();
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
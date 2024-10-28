#include <stdio.h>

#include "Handlers/HandleDetailTeacher.h"
#include "Handlers/HandleListTeachersSortedByCreationOrder.h"
#include "Handlers/HandleListTeachersSortedByBirthday.h"
#include "Handlers/HandleListTeachersSortedByName.h"
#include "Handlers/HandleListTeachersByGender.h"

#include "../Shared/HandleFetchSpecificTeacher.h"

#include "../TeacherManagementView.h"
#include "../../Utils/ClearScreen.h"

void render_teacher_reports_view(char *message) {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Relatorio de Professores\n");
  printf("\n");
  printf("1 - Detalhar professor\n");
  printf("2 - Listar professores\n");
  printf("3 - Listar professores por genero\n");
  printf("4 - Listar professores por ordem alfabetica\n");
  printf("5 - Listar professores por data de nascimento\n");
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
      render_teacher_management_view(NULL);
      break;

    case 1:
      handle_fetch_specific_teacher(&handle_detail_teacher, &render_teacher_reports_view);
      break;

    case 2:
      handle_list_teachers_sorted_by_creation_order();
      break;

    case 3:
      handle_list_teachers_by_gender(NULL);
      break;
    
    case 4:
      handle_list_teachers_sorted_by_name(NULL);
      break;

    case 5:
      handle_list_teachers_sorted_by_birthday(NULL);
      break;    

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
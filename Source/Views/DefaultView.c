#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Reports/GeneralReportsView.h"
#include "SharedHandlers/HandleSearchPersons.h"
#include "Students/StudentManagementView.h"
#include "Teachers/TeacherManagementView.h"
#include "Utils/ClearScreen.h"

void render_default_view() {
  clear_screen();

  char *current_work_dir = getcwd(NULL, 0);

  printf("Instituto Federal da Bahia\n");
  printf("\n");
  printf("Current Work Directory: %s\n", current_work_dir);
  printf("\n");
  printf("1 - Buscar Pessoas\n");
  printf("2 - Exibir Relatorios\n");
  printf("3 - Gerenciamento de Alunos\n");
  printf("4 - Gerenciamento de Professores\n");
  printf("5 - Gerenciamento de Disciplinas\n");
  printf("\n");
  printf("0 - Sair do Programa\n");

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
      printf("Saindo do programa...\n");
      exit(0);

    case 1:
      handle_search_persons();
      break;

    case 2:
      render_general_reports_view();
      break;

    case 3:
      render_student_management_view(NULL);
      break;

    case 4:
      render_teacher_management_view(NULL);
      break;

    case 5:
      printf("Gerenciamento de Disciplinas\n");
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
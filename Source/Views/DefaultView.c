#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Students/StudentManagementView.h"
#include "Utils/ClearScreen.h"

void render_default_view() {
  clear_screen();

  char *current_work_dir = getcwd(NULL, 0);

  printf("Instituto Federal da Bahia\n");
  printf("\n");
  printf("Current Work Directory: %s\n", current_work_dir);
  printf("\n");
  printf("1 - Gerenciamento de Alunos\n");
  printf("2 - Gerenciamento de Professores\n");
  printf("3 - Gerenciamento de Disciplinas\n");
  printf("4 - Exibir Relatorios\n");
  printf("\n");
  printf("0 - Sair do Programa\n");

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
      printf("Saindo do programa...\n");
      exit(25565);
    case 1:
      render_student_management_view(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
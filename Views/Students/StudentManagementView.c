#include <stdio.h>

#include "Handlers/HandleCreateStudent.h"
#include "Handlers/HandleListStudents.h"

#include "../DefaultView.h"
#include "../Utils/ClearScreen.h"

void render_student_management_view(char *message) {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Alunos\n");
  printf("\n");
  printf("1 - Listagem de Alunos\n");
  printf("2 - Atualizar Aluno\n");
  printf("3 - Cadastrar Aluno\n");
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
      printf("Opção inválida.\n");
      continue;
    }

    is_awaiting_input = 0;

    switch (view_option) {
    case 0:
      render_default_view();
      break;

    case 1:
      handle_list_students();
      break;

    case 3:
      handle_create_student();
      break;

    default:
      printf("Opção inválida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
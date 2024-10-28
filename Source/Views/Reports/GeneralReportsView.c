#include <stdio.h>

#include "../DefaultView.h"
#include "../Utils/ClearScreen.h"

#include "Handlers/HandleFetchMonthlyBirthdays.h"

void render_general_reports_view() {
  fflush(stdin);
  clear_screen();

  printf("Instituto Federal da Bahia - Relatorios gerais\n");
  printf("\n");
  printf("1 - Exibir aniversariantes do mes\n");
  printf("\n");

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
      render_default_view();
      break;

    case 1:
      handle_fetch_monthly_birthdays();
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
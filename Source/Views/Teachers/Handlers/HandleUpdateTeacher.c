#include <stdio.h>
#include <stdlib.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../TeacherManagementView.h"

void handle_update_teacher(Person teacher);

void handle_display_update_teacher_header(Person teacher, char *field) {
  fflush(stdin);
  clear_screen();

  printf("Voce esta atualizando %s do(a) professor '%s - %s'.\n", field, teacher.registration, teacher.name);
  printf("\n");
}

void handle_display_update_teacher_subtitle(char* value) {
  printf("Valor atual: %s\n", value);
  printf("\n");
}

void handle_input_update_teacher_identification(Person *teacher) {
  handle_display_update_teacher_header(*teacher, "o CPF");
  handle_display_update_teacher_subtitle(teacher->identification);

  printf("Insira o novo CPF do professor: ");
  scanf(" %14[^\n]", teacher->identification);

  handle_update_teacher(*teacher);
}

void handle_input_update_teacher_name(Person *teacher) {
  handle_display_update_teacher_header(*teacher, "o nome");
  handle_display_update_teacher_subtitle(teacher->name);

  printf("Insira o novo nome do professor: ");
  scanf(" %49[^\n]", teacher->name);

  handle_update_teacher(*teacher);
}

void handle_input_update_teacher_gender(Person *teacher) {
  handle_display_update_teacher_header(*teacher, "o genero");
  handle_display_update_teacher_subtitle(teacher->gender);

  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o novo genero do professor (M/F/O): ");

    scanf(" %1[^\n]", teacher->gender);

    for (int i = 0; i < 3 && !is_gender_valid; i++) {
      if (teacher->gender[0] == valid_genders[i])
        is_gender_valid = 1;
    }

    if (!is_gender_valid)
      printf("O genero fornecido e invalido.\n");
  }

  handle_update_teacher(*teacher);
}

void handle_input_update_teacher_birthday(Person *teacher) {
  handle_display_update_teacher_header(*teacher, "a data de nascimento");
  printf("Valor atual: %02d/%02d/%04d\n", teacher->birthday.day,
         teacher->birthday.month, teacher->birthday.year);
  printf("\n"); // Subtitle

  int is_birthday_valid = 0;

  while (!is_birthday_valid) {
    printf("Insira a nova data de nascimento do professor (DD/MM/AAAA): ");

    scanf("%d/%d/%d", &teacher->birthday.day, &teacher->birthday.month,
          &teacher->birthday.year);

    if (is_date_valid(teacher->birthday))
      is_birthday_valid = 1;
    else
      printf("A data de nascimento fornecida e invalida.\n");
  }

  handle_update_teacher(*teacher);
}

void handle_update_teacher(Person teacher) {
  fflush(stdin);
  clear_screen();

  Person *teachers;

  printf("Escolha o dado para atualizar do professor '%s - %s', digite:\n", teacher.registration, teacher.name);
  printf("\n");
  printf("1 - Nome\n");
  printf("2 - CPF\n");
  printf("3 - Genero\n");
  printf("4 - Data de Nascimento\n");
  printf("\n");
  printf("9 - Salvar alteracoes\n");
  printf("0 - Voltar\n");

  int view_option = -1;
  int is_awaiting_input = 1;

  while (view_option != 0 && is_awaiting_input == 1) {
    scanf("%d", &view_option);

    if (view_option < 0 || (view_option > 4 && view_option != 9)) {
      printf("Opcao invalida.\n");
      continue;
    }

    is_awaiting_input = 0;

    switch (view_option) {
    case 0:
      render_teacher_management_view("Alteracoes descartadas.");
      break;
    
    case 1:
      handle_input_update_teacher_name(&teacher);
      break;
    
    case 2:
      handle_input_update_teacher_identification(&teacher);
      break;
    
    case 3:
      handle_input_update_teacher_gender(&teacher);
      break;
    
    case 4:
      handle_input_update_teacher_birthday(&teacher);
      break;
    
    case 9:
      update_person(TEACHERS_DATABASE_FILE, teacher.registration, teacher);
      render_teacher_management_view("Professor atualizado com sucesso.");
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }

}

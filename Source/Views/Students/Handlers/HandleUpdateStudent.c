#include <stdio.h>
#include <stdlib.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../StudentManagementView.h"

void handle_update_student(Person student);

void handle_display_update_student_header(Person student, char *field) {
  fflush(stdin);
  clear_screen();

  printf("Voce esta atualizando %s do(a) aluno '%s - %s'.\n", field, student.registration, student.name);
  printf("\n");
}

void handle_display_update_student_subtitle(char* value) {
  printf("Valor atual: %s\n", value);
  printf("\n");
}

void handle_input_update_student_identification(Person *student) {
  handle_display_update_student_header(*student, "o CPF");
  handle_display_update_student_subtitle(student->identification);

  printf("Insira o novo CPF do aluno: ");
  scanf(" %14[^\n]", student->identification);

  handle_update_student(*student);
}

void handle_input_update_student_name(Person *student) {
  handle_display_update_student_header(*student, "o nome");
  handle_display_update_student_subtitle(student->name);

  printf("Insira o novo nome do aluno: ");
  scanf(" %49[^\n]", student->name);

  handle_update_student(*student);
}

void handle_input_update_student_gender(Person *student) {
  handle_display_update_student_header(*student, "o genero");
  handle_display_update_student_subtitle(student->gender);

  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o novo genero do aluno (M/F/O): ");

    scanf(" %1[^\n]", student->gender);

    for (int i = 0; i < 3 && !is_gender_valid; i++) {
      if (student->gender[0] == valid_genders[i])
        is_gender_valid = 1;
    }

    if (!is_gender_valid)
      printf("O genero fornecido e invalido.\n");
  }

  handle_update_student(*student);
}

void handle_input_update_student_birthday(Person *student) {
  handle_display_update_student_header(*student, "a data de nascimento");
  printf("Valor atual: %02d/%02d/%04d\n", student->birthday.day,
         student->birthday.month, student->birthday.year);
  printf("\n"); // Subtitle

  int is_birthday_valid = 0;

  while (!is_birthday_valid) {
    printf("Insira a nova data de nascimento do aluno (DD/MM/AAAA): ");

    scanf("%d/%d/%d", &student->birthday.day, &student->birthday.month,
          &student->birthday.year);

    if (is_date_valid(student->birthday))
      is_birthday_valid = 1;
    else
      printf("A data de nascimento fornecida e invalida.\n");
  }

  handle_update_student(*student);
}

void handle_update_student(Person student) {
  fflush(stdin);
  clear_screen();

  Person *students;

  printf("Escolha o dado para atualizar do aluno '%s - %s', digite:\n", student.registration, student.name);
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
      render_student_management_view("Alteracoes descartadas.");
      break;
    
    case 1:
      handle_input_update_student_name(&student);
      break;
    
    case 2:
      handle_input_update_student_identification(&student);
      break;
    
    case 3:
      handle_input_update_student_gender(&student);
      break;
    
    case 4:
      handle_input_update_student_birthday(&student);
      break;
    
    case 9:
      update_person(STUDENTS_DATABASE_FILE, student.registration, student);
      render_student_management_view("Aluno atualizado com sucesso.");
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }

}

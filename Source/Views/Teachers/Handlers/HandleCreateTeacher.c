#include <stdio.h>
#include <stdlib.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Mappers/PersonMapper.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../TeacherManagementView.h"

void handle_input_teacher_registration(Person *teacher) {
  printf("Insira a matricula do professor: ");
  scanf(" %32[^\n]", teacher->registration);
}

void handle_input_teacher_identification(Person *teacher) {
  // regex_t cpf_regex;
  // int regex_result =
  //     regcomp(&cpf_regex,
  //             "([0-9]{2}[\.]?[0-9]{3}[\.]?[0-9]{3}[\/]?[0-9]{4}[-]?[0-9]{2})|(["
  //             "0-9]{3}[\.]?[0-9]{3}[\.]?[0-9]{3}[-]?[0-9]{2})",
  //             REG_EXTENDED);

  // if (regex_result)
  //   fprintf(stderr,
  //           "AVISO: Nao foi possivel compilar a expressao regular. Validacao "
  //           "de CPF desativada.\n");

  // int is_cpf_valid = 0;

  // while (!is_cpf_valid) {
  //   printf("Insira o CPF do professor: ");
  //   scanf(" %14[^\n]", teacher->identification);

  //   if (!regex_result) {
  //     regex_result = regexec(&cpf_regex, teacher->identification, 0, NULL, 0);

  //     if (!regex_result) {
  //       is_cpf_valid = 1;
  //     } else if (regex_result == REG_NOMATCH) {
  //       printf("O CPF fornecido e invalido.\n");
  //     } else {
  //       char cpf_regex_error_buffer[100];

  //       regerror(regex_result, &cpf_regex, cpf_regex_error_buffer,
  //                sizeof(cpf_regex_error_buffer));
  //       fprintf(stderr, "Regex match failed: %s\n", cpf_regex_error_buffer);
  //     }
  //   } else
  //     is_cpf_valid = 1;
  // }
  printf("Insira o CPF do professor: ");
  scanf(" %14[^\n]", teacher->identification);
}

void handle_input_teacher_name(Person *teacher) {
  printf("Insira o nome do professor: ");
  scanf(" %49[^\n]", teacher->name);
}

void handle_input_teacher_gender(Person *teacher) {
  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o genero do professor (M/F/O): ");

    scanf(" %1[^\n]", teacher->gender);

    for (int i = 0; i < 3 && !is_gender_valid; i++) {
      if (teacher->gender[0] == valid_genders[i])
        is_gender_valid = 1;
    }

    if (!is_gender_valid)
      printf("O genero fornecido e invalido.\n");
  }
}

void handle_input_teacher_birthday(Person *teacher) {
  int is_birthday_valid = 0;

  while (!is_birthday_valid) {
    printf("Insira a data de nascimento do professor (DD/MM/AAAA): ");

    scanf("%d/%d/%d", &teacher->birthday.day, &teacher->birthday.month,
          &teacher->birthday.year);

    if (is_date_valid(teacher->birthday))
      is_birthday_valid = 1;
    else
      printf("A data de nascimento fornecida e invalida.\n");
  }
}

void handle_create_teacher() {
  fflush(stdin);
  clear_screen();

  Person teacher;

  printf("Formulario de Cadastro de Professor\n");
  printf("\n");

  handle_input_teacher_registration(&teacher);
  handle_input_teacher_identification(&teacher);
  handle_input_teacher_name(&teacher);
  handle_input_teacher_gender(&teacher);
  handle_input_teacher_birthday(&teacher);

  int persistence_result = persist_person(TEACHERS_DATABASE_FILE, teacher);

  if (persistence_result) {
    switch (persistence_result) {
    case 1:
      return render_teacher_management_view(
          "Erro ao criar professor: Nao foi possivel alocar o espaco de "
          "memoria para escrever o conteúdo da entidade.");
    case 2:
      return render_teacher_management_view(
          "Erro ao criar professor: Nao foi "
          "possivel abrir o arquivo de dados. O usuario nao foi salvo no Banco "
          "de Dados.");
    case 3:
      return render_teacher_management_view(
          "Erro ao criar professor: Ja existe um professor cadastrado com a matricula fornecida.");
    }
  }

  render_teacher_management_view("Professor cadastrado com sucesso!");
}

#include <stdio.h>
#include <stdlib.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Mappers/PersonMapper.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../StudentManagementView.h"

void handle_input_student_registration(Person *student) {
  printf("Insira a matricula do aluno: ");
  scanf(" %32[^\n]", student->registration);
}

void handle_input_student_identification(Person *student) {
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
  //   printf("Insira o CPF do aluno: ");
  //   scanf(" %14[^\n]", student->identification);

  //   if (!regex_result) {
  //     regex_result = regexec(&cpf_regex, student->identification, 0, NULL, 0);

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
  printf("Insira o CPF do aluno: ");
  scanf(" %14[^\n]", student->identification);
}

void handle_input_student_name(Person *student) {
  printf("Insira o nome do aluno: ");
  scanf(" %49[^\n]", student->name);
}

void handle_input_student_gender(Person *student) {
  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o genero do aluno (M/F/O): ");

    scanf(" %1[^\n]", student->gender);

    for (int i = 0; i < 3 && !is_gender_valid; i++) {
      if (student->gender[0] == valid_genders[i])
        is_gender_valid = 1;
    }

    if (!is_gender_valid)
      printf("O genero fornecido e invalido.\n");
  }
}

void handle_input_student_birthday(Person *student) {
  int is_birthday_valid = 0;

  while (!is_birthday_valid) {
    printf("Insira a data de nascimento do aluno (DD/MM/AAAA): ");

    scanf("%d/%d/%d", &student->birthday.day, &student->birthday.month,
          &student->birthday.year);

    if (is_date_valid(student->birthday))
      is_birthday_valid = 1;
    else
      printf("A data de nascimento fornecida e invalida.\n");
  }
}

void handle_create_student() {
  fflush(stdin);
  clear_screen();

  Person student;

  printf("Formulario de Cadastro de Aluno\n");
  printf("\n");

  handle_input_student_registration(&student);
  handle_input_student_identification(&student);
  handle_input_student_name(&student);
  handle_input_student_gender(&student);
  handle_input_student_birthday(&student);

  int persistence_result = persist_person(STUDENTS_DATABASE_FILE, student);

  if (persistence_result) {
    switch (persistence_result) {
    case 1:
      return render_student_management_view(
          "Erro ao criar aluno: Nao foi possivel alocar o espaco de "
          "memoria para escrever o conteúdo da entidade.");
    case 2:
      return render_student_management_view(
          "Erro ao criar aluno: Nao foi "
          "possivel abrir o arquivo de dados. O usuario nao foi salvo no Banco "
          "de Dados.");
    case 3:
      return render_student_management_view(
          "Erro ao criar aluno: Ja existe um aluno cadastrado com a matricula fornecida.");
    }
  }

  render_student_management_view("Aluno cadastrado com sucesso!");
}

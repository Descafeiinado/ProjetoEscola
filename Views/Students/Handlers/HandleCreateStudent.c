#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Mappers/PersonMapper.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../StudentManagementView.h"

extern const char *students_database_file;

void handle_input_student_registration(Person *student) {
  printf("Insira a matrícula do aluno: ");
  scanf(" %32[^\n]", student->registration);
}

void handle_input_student_identification(Person *student) {
  regex_t cpf_regex;
  int regex_result =
      regcomp(&cpf_regex,
              "([0-9]{2}[\.]?[0-9]{3}[\.]?[0-9]{3}[\/]?[0-9]{4}[-]?[0-9]{2})|(["
              "0-9]{3}[\.]?[0-9]{3}[\.]?[0-9]{3}[-]?[0-9]{2})",
              REG_EXTENDED);

  if (regex_result)
    fprintf(stderr,
            "AVISO: Não foi possível compilar a expressão regular. Validação "
            "de CPF desativada.\n");

  int is_cpf_valid = 0;

  while (!is_cpf_valid) {
    printf("Insira o CPF do aluno: ");
    scanf(" %14[^\n]", student->identification);

    if (!regex_result) {
      regex_result = regexec(&cpf_regex, student->identification, 0, NULL, 0);

      if (!regex_result) {
        is_cpf_valid = 1;
      } else if (regex_result == REG_NOMATCH) {
        printf("O CPF fornecido é inválido.\n");
      } else {
        char cpf_regex_error_buffer[100];

        regerror(regex_result, &cpf_regex, cpf_regex_error_buffer,
                 sizeof(cpf_regex_error_buffer));
        fprintf(stderr, "Regex match failed: %s\n", cpf_regex_error_buffer);
      }
    } else
      is_cpf_valid = 1;
  }
}

void handle_input_student_name(Person *student) {
  printf("Insira o nome do aluno: ");
  scanf(" %49[^\n]", student->name);
}

void handle_input_student_gender(Person *student) {
  int is_gender_valid = 0;
  char valid_genders[3] = {'M', 'F', 'O'};

  while (!is_gender_valid) {
    printf("Insira o gênero do aluno (M/F/O): ");

    scanf(" %1[^\n]", student->gender);

    for (int i = 0; i < 3 && !is_gender_valid; i++) {
      if (student->gender[0] == valid_genders[i])
        is_gender_valid = 1;
    }

    if (!is_gender_valid)
      printf("O gênero fornecido é inválido.\n");
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
      printf("A data de nascimento fornecida é inválida.\n");
  }
}

void handle_create_student() {
  fflush(stdin);
  clear_screen();

  Person student;

  printf("Formulário de Cadastro de Aluno\n");
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
          "Erro ao criar estudante: Não foi possível alocar o espaço de "
          "memória para escrever o conteúdo da entidade.");
    case 2:
      return render_student_management_view(
          "Erro ao criar estudante: Não foi "
          "possível abrir o arquivo de dados. O usuário não foi salvo no Banco "
          "de Dados.");
    }
  }

  render_student_management_view("Estudante cadastrado com sucesso!");
}

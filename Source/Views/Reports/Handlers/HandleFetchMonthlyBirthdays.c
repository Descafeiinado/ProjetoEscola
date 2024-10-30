#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Entities/Person.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../Utils/ClearScreen.h"
#include "../GeneralReportsView.h"

void handle_fetch_monthly_birthdays() {
  fflush(stdin);
  clear_screen();

  Person *students = calloc(1, 100 * sizeof(Person));
  Person *teachers = calloc(1, 100 * sizeof(Person));

  int month = 0;
  bool is_month_valid = false;

  while (!is_month_valid) {
    printf("Insira o mes desejado, ou digite '0' para voltar: ");

    scanf("%d", &month);

    if (month == 0) 
      return render_general_reports_view();

    if (month >= 1 && month <= 12)
      is_month_valid = true;

    if (!is_month_valid)
      printf("O mes fornecido e invalido.\n");
  }

  int students_amount = get_all_persons(STUDENTS_DATABASE_FILE, students);
  int teachers_amount = get_all_persons(TEACHERS_DATABASE_FILE, teachers);

  Person *valid_students = calloc(1, students_amount * sizeof(Person));
  Person *valid_teachers = calloc(1, teachers_amount * sizeof(Person));

  int valid_students_position = 0;
  int valid_teachers_position = 0;

  if (students_amount > 0) 
    for (int i = 0; i < students_amount; i++) {
      Person student = students[i];

      if (student.birthday.month == month) {
        valid_students[valid_students_position] = student;
        valid_students_position++;
      }
  }

  if (teachers_amount > 0) 
    for (int i = 0; i < teachers_amount; i++) {
      Person teacher = teachers[i];

      if (teacher.birthday.month == month) {
        valid_teachers[valid_teachers_position] = teacher;
        valid_teachers_position++;
      }
    }

  free(students);
  free(teachers);

  fflush(stdin);
  clear_screen();

  printf("Listagem de aniversariantes do mes %d:\n\n", month);

  if (valid_students_position > 0) {
    for (int i = 0; i < valid_students_position; i++) {
      Person student = valid_students[i];

      printf("Aluno | %s. %s\n", student.registration, student.name);
    }
  }

  if (valid_teachers_position > 0) {
    for (int i = 0; i < valid_teachers_position; i++) {
      Person teacher = valid_teachers[i];

      printf("Professor | %s. %s\n", teacher.registration, teacher.name);
    }
  }
  
  int total = valid_students_position + valid_teachers_position;

  if (total > 0) {
    printf("\n");
    printf("Total de aniversariantes: %d | ", total);

    if (valid_teachers_position > 0) {
      printf("%d", valid_teachers_position);

      printf(" professor");

      if (valid_teachers_position > 1) printf("es");
      if (valid_students_position > 0) printf(" e ");
    }

    if (valid_students_position > 0) {
      printf("%d", valid_students_position);

      printf(" aluno");

      if (valid_students_position > 1) printf("s");
    }

    printf("\n");
  } else
    printf("Nao foram encontrados aniversariantes para esse mes.\n");

  printf("\n");
  printf("0 - Voltar\n");

  free(valid_students);
  free(valid_teachers);

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
      render_general_reports_view(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

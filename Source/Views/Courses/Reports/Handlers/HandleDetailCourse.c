#include <stdio.h>
#include <stdlib.h>

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/PersonPersistence.h"
#include "../../../../Persistence/CoursePersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../CourseReportsView.h"

void handle_detail_course(Course course) {
  fflush(stdin);
  clear_screen();

  printf("Detalhamento de Disciplina:\n");
  printf("\n");
  printf("Nome: %s (%s)\n", course.name, course.id);
  printf("Semestre: %d\n", course.period);
  printf("\n");
  printf("Informacoes do Professor:\n");

  if (person_exists0(TEACHERS_DATABASE_FILE, course.teacher_registration)) {
    Person teacher = get_person(TEACHERS_DATABASE_FILE, course.teacher_registration);

    printf(" - Matricula: %s\n", teacher.registration);
    printf(" - Nome: %s (%s)\n", teacher.name, teacher.gender);
    printf(" - CPF: %s\n", teacher.identification);
    printf(" - Data de Nascimento: %02d/%02d/%d\n", teacher.birthday.day, teacher.birthday.month, teacher.birthday.year);

  } else printf(" - Nao ha professor vinculado a esta disciplina.\n");

  printf("\n");

  int students_amount = course.students_amount;

  printf("Alunos Matriculados (%d):\n", students_amount);  

  if (students_amount > 0) {
    for (int i = 0; i < students_amount; i++) {
      char *registration = course.students[i].registration;

      if (person_exists0(STUDENTS_DATABASE_FILE, registration)) {
        Person student = get_person(STUDENTS_DATABASE_FILE, registration);

        printf(" - %s (%s)\n", student.name, student.registration);
      }
    }
  } else printf(" - Nao ha alunos matriculados nesta disciplina.\n");

  printf("\n");
  printf("0 - Voltar\n");

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
      render_course_reports_view(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

#define MAX_LISTING_SIZE 100
#define STUDENTS_AMOUNT_TO_BE_CONSIDERED_EXCEEDING 40
#include <stdio.h>
#include <stdlib.h>

#include "../../../../Constants/CourseConstants.h"
#include "../../../../Persistence/CoursePersistence.h"
#include "../../../Utils/ClearScreen.h"
#include "../CourseReportsView.h"

void handle_list_exceeding_courses() {
  fflush(stdin);
  clear_screen();

  Course *courses = calloc(1, MAX_LISTING_SIZE * sizeof(Course));

  printf("Listagem de Disciplinas Excedentes\n");
  printf("\n");

  int amount = get_all_courses(courses);

  if (amount > 0) {
    for (int i = 0; i < amount; i++) {
      Course course = courses[i];

      if (course.students_amount > STUDENTS_AMOUNT_TO_BE_CONSIDERED_EXCEEDING) {
        char *s = course.students_amount == 1 ? "" : "s";

        printf("%s. %s (%d aluno%s)\n", course.id, course.name, course.students_amount, s);
      }
    }

    printf("\n");
    printf("Total de disciplinas excedentes: %d\n", amount);
  } else printf("Nao existem disciplinas excedentes.\n");

  printf("\n");
  printf("0 - Voltar\n");

  free(courses);

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

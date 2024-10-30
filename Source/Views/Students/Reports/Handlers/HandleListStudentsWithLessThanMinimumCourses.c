#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HandleListStudentsWithLessThanMinimumCourses.h"

#include "../../../../Constants/PersonConstants.h"
#include "../../../../Persistence/CoursePersistence.h"
#include "../../../../Persistence/PersonPersistence.h"

#include "../../../Utils/ClearScreen.h"
#include "../StudentReportsView.h"

void handle_list_students_with_less_than_minimum_courses() {
  fflush(stdin);
  clear_screen();

  Person *students = calloc(1, 100 * sizeof(Person));
  
  int amount = get_all_persons(STUDENTS_DATABASE_FILE, students);

  Person *filtered_students = calloc(1, amount * sizeof(Person));
  int filtered_students_position = 0;

  if (amount > 0) 
    for (int i = 0; i < amount; i++) {
      Person student = students[i];

      if (get_all_courses_of_student(student.registration) < MINIMUM_COURSES) {
        filtered_students[filtered_students_position] = student;
        filtered_students_position++;
      }
  }

  free(students);

  fflush(stdin);
  clear_screen();

  printf("Listagem de alunos matriculados em menos de %d disciplinas:\n\n", MINIMUM_COURSES);

  if (filtered_students_position > 0) {
    for (int i = 0; i < filtered_students_position; i++) {
      Person student = filtered_students[i];

      printf("%s. %s\n", student.registration, student.name);
    }

    printf("\n");
    printf("Total de alunos: %d\n", filtered_students_position);
  } else
    printf("Nao existem resultados.\n");

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
      render_student_reports_view(NULL);
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}

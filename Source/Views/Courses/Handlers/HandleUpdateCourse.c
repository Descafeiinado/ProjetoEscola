#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Persistence/CoursePersistence.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../CourseManagementView.h"

void handle_update_course(Course course);

void handle_display_update_course_header(Course course, char *field) {
  fflush(stdin);
  clear_screen();

  printf("Voce esta atualizando %s da disciplina '%s - %s'.\n", field, course.id, course.name);
  printf("\n");
}

void handle_display_update_course_subtitle(char* value) {
  printf("Valor atual: %s\n", value);
  printf("\n");
}

void handle_input_update_course_name(Course *course) {
  handle_display_update_course_header(*course, "o nome");
  handle_display_update_course_subtitle(course->name);

  printf("Insira o novo nome da disciplina: ");
  scanf(" %49[^\n]", course->name);

  handle_update_course(*course);
}

void handle_input_update_course_teacher(Course *course) {
  Person teacher;
  bool is_teacher_found = false;

  char registration[MAX_PERSON_REGISTRATION_SIZE];

  while (!is_teacher_found) {
    printf("Insira a matricula do novo professor, ou digite 'cancelar' para voltar: ");
    scanf(" %14[^\n]", &registration);

    if (strcmp(registration, "cancelar") == 0) 
      return handle_update_course(*course);

    if (person_exists0(TEACHERS_DATABASE_FILE, registration)) {
      teacher = get_person(TEACHERS_DATABASE_FILE, registration);
      is_teacher_found = true;
    } else printf("Professor nao encontrado.\n");
  }

  strcpy(course->teacher_registration, teacher.registration);
}

void handle_input_update_course_period(Course *course) {
  handle_display_update_course_header(*course, "o semestre");
  printf("Valor atual: %d\n", course->period);
  printf("\n");

  printf("Insira o novo semestre da disciplina: ");
  scanf(" %d", &course->period);

  handle_update_course(*course);
}

void handle_input_update_course_students(Course *course) {
  handle_display_update_course_header(*course, "os alunos");
  
  printf("Alunos matriculados:\n");

  for (int i = 0; i < course->students_amount; i++) {
    Person student = course->students[i];
    printf(" - %s (%s)\n", student.name, student.registration);
  }

  printf("\n");

  printf("Insira '+' para adicionar um aluno, '-' para remover um aluno, ou 'cancelar' para voltar: ");

  char operation[8];

  scanf(" %8[^\n]", &operation);

  if (strcmp(operation, "cancelar") == 0) 
    return handle_update_course(*course);

  if (strcmp(operation, "+") == 0) {
    Person student;
    bool is_student_found = false;

    char *registration = calloc(1, MAX_PERSON_REGISTRATION_SIZE * sizeof(char));

    while (!is_student_found) {
      printf("Insira a matricula do aluno, ou digite 'cancelar' para voltar: ");
      scanf(" %14[^\n]", registration);

      if (strcmp(registration, "cancelar") == 0) 
        return handle_update_course(*course);
      
      if (person_exists0(STUDENTS_DATABASE_FILE, registration)) {
        student = get_person(STUDENTS_DATABASE_FILE, registration);
        is_student_found = true;
      } else printf("Aluno nao encontrado.\n");
    }

    course->students[course->students_amount] = student;
    course->students_amount++;
  } else if (strcmp(operation, "-") == 0) {
    printf("Insira a matricula do aluno a ser removido: ");

    char *registration = calloc(1, MAX_PERSON_REGISTRATION_SIZE * sizeof(char));

    scanf(" %14[^\n]", registration);

    int students_amount = course->students_amount;

    for (int i = 0; i < students_amount; i++) {
      Person student = course->students[i];

      if (strcmp(student.registration, registration) != 0) {
        course->students[i] = student;
      } else {
        for (int j = i; j < students_amount - 1; j++) {
          course->students[j] = course->students[j + 1];
        }

        course->students_amount--;
      }
    }
  } else {
    printf("Operacao invalida.\n");
  }

  handle_update_course(*course);
}

void handle_update_course(Course course) {
  fflush(stdin);
  clear_screen();

  printf("Escolha o dado para atualizar da disciplina '%s - %s', digite:\n", course.id, course.name);
  printf("\n");
  printf("1 - Nome\n");
  printf("2 - Semestre\n");
  printf("3 - Professor\n");
  printf("4 - Alunos\n");
  printf("\n");
  printf("9 - Salvar alteracoes\n");
  printf("0 - Voltar\n");

  int view_option = -1;
  bool is_awaiting_input = true;

  while (view_option != 0 && is_awaiting_input) {
    scanf("%d", &view_option);

    if (view_option < 0 || (view_option > 4 && view_option != 9)) {
      printf("Opcao invalida.\n");
      continue;
    }

    is_awaiting_input = false;

    switch (view_option) {
    case 0:
      render_course_management_view("Alteracoes descartadas.");
      break;
    
    case 1:
      handle_input_update_course_name(&course);
      break;
    
    case 2:
      handle_input_update_course_period(&course);
      break;
    
    case 3:
      handle_input_update_course_teacher(&course);
      break;
    
    case 4:
      handle_input_update_course_students(&course);
      break;
    
    case 9:
      update_course(course.id, course);
      render_course_management_view("Disciplina atualizado com sucesso.");
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = true;
    }
  }
}

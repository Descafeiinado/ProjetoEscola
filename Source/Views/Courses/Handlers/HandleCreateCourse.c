#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Mappers/CourseMapper.h"
#include "../../../Persistence/CoursePersistence.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../CourseManagementView.h"

void handle_input_course_id(Course *course) {
  printf("Insira o codigo da disciplina: ");
  scanf(" %32[^\n]", course->id);
}

void handle_input_course_name(Course *course) {
  printf("Insira o nome da disciplina: ");
  scanf(" %49[^\n]", course->name);
}

void handle_input_course_period(Course *course) {
  printf("Insira o periodo da disciplina: ");
  scanf("%d", &course->period);
}

void handle_input_course_teacher(Course *course) {
  Person teacher;
  bool is_teacher_found = false;

  char *registration = calloc(1, MAX_PERSON_REGISTRATION_SIZE * sizeof(char));

  while (!is_teacher_found) {
    printf("Insira a matricula do professor, ou digite 'cancelar' para voltar: ");
    scanf(" %32[^\n]", registration);

    if (strcmp(registration, "cancelar") == 0) 
      return render_course_management_view(0);

    if (person_exists0(TEACHERS_DATABASE_FILE, registration)) {
      teacher = get_person(TEACHERS_DATABASE_FILE, registration);
      is_teacher_found = true;
    } else printf("Professor nao encontrado.\n");
  }

  strcpy(course->teacher_registration, teacher.registration);
}

void handle_create_course() {
  fflush(stdin);
  clear_screen();

  Course *course = calloc(1, sizeof(Course));

  printf("Formulario de Cadastro de Disciplina\n");
  printf("\n");

  handle_input_course_id(course);
  handle_input_course_name(course);
  handle_input_course_period(course);
  handle_input_course_teacher(course);

  course->students_amount = 0;

  int persistence_result = persist_course(*course);

  if (persistence_result) {
    switch (persistence_result) {
    case 1:
      return render_course_management_view(
          "Erro ao criar disciplina: Nao foi possivel alocar o espaco de "
          "memoria para escrever o conteúdo da entidade.");
    case 2:
      return render_course_management_view(
          "Erro ao criar disciplina: Nao foi "
          "possivel abrir o arquivo de dados. A disciplina nao foi salva no Banco "
          "de Dados.");
    case 3:
      return render_course_management_view(
          "Erro ao criar disciplina: Ja existe uma disciplina cadastrada com o codigo fornecido.");
    }
  }

  render_course_management_view("Disciplina cadastrada com sucesso!");
}

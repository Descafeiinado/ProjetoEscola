#define MAX_SEARCH_SIZE 24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Constants/PersonConstants.h"
#include "../../Persistence/PersonPersistence.h"
#include "../Utils/ClearScreen.h"
#include "../DefaultView.h"

void handle_search_persons() {
  fflush(stdin);
  clear_screen();

  Person *students = calloc(1, 100 * sizeof(Person));
  Person *teachers = calloc(1, 100 * sizeof(Person));
  
  char *search = calloc(1, MAX_SEARCH_SIZE * sizeof(char));

  int is_search_valid = 0;
  int invalidity_reason = 0;

  while (!is_search_valid) {
    printf("Insira o conteudo que voce deseja buscar, ou digite 'cancelar' para voltar: ");

    scanf(" %15[^\n]", search);

    if (strcmp(search, "cancelar") == 0)
      return render_default_view(NULL);
    
    int search_length = strlen(search);

    is_search_valid = 1;

    if (search_length < 3) {
      is_search_valid = 0;
      invalidity_reason = 1;
    }
    
    if (!is_search_valid)
      switch (invalidity_reason) {
      case 1:
        printf("A busca deve conter no minimo 3 caracteres.\n");
        break;
      
      default:
        break;
      }
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

      if (strstr(student.name, search) != NULL) {
        valid_students[valid_students_position] = student;
        valid_students_position++;
      }
  }

  if (teachers_amount > 0) 
    for (int i = 0; i < teachers_amount; i++) {
      Person teacher = teachers[i];

      if (strstr(teacher.name, search) != NULL) {
        valid_teachers[valid_teachers_position] = teacher;
        valid_teachers_position++;
      }
    }

  free(students);
  free(teachers);

  fflush(stdin);
  clear_screen();

  printf("Listagem de pessoas contendo '%s' no nome:\n\n", search);

  free(search);

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
    printf("Total de resultados: %d | ", total);

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
    printf("Nao foram encontradas pessoas que atendam as buscas.\n");

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
      render_default_view();
      break;

    default:
      printf("Opcao invalida: %d\n", view_option);
      is_awaiting_input = 1;
    }
  }
}
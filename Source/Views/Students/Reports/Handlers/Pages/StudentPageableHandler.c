#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../Utils/ClearScreen.h"
#include "../../../../../Entities/Person.h"

void handle_generate_student_pageable(int page, int amount, Person students[], void (*back)(char *)) {
  fflush(stdin);
  clear_screen();
  printf("Listagem de alunos\n\n");

  Person *page_content = malloc(5 * sizeof(Person));
  int page_position = 0;

  if (amount > 0) {
    for (int i = 0; i < amount; i++) {
      Person student = students[i];

      if (student.registration[0] == '\0')
        continue;

      if (i >= (page - 1) * 5 && i < page * 5) {
        page_content[page_position] = student;
        page_position++;
      }
    }

    for (int i = 0; i < 5; i++) {
      Person student = page_content[i];

      if (student.registration[0] == '\0')
        continue;

      printf("%s. %s\n", student.registration, student.name);
    }

    printf("\n");
    printf("Total de alunos: %d\n", amount);
  } else
    printf("Nao existem estudantes cadastrados.\n");

  printf("\n");

  if (page != 1) {
    if (page >= 2) 
      printf("← Anterior | ");

    printf("Página %d de %d | ", page, (amount / 5) + 1);

    if (page < (amount / 5) + 1) 
      printf("Proximo →");

    printf("\n");
  }
  
  printf("Pressione qualquer tecla para voltar.\n");

  int view_option = -1;
  int is_awaiting_input = 1;

  while (view_option != 0 && is_awaiting_input == 1) {
    view_option = getch() - '0';

    if (kbhit()) {
      is_awaiting_input = 0;

      switch (view_option) {
      case 27: // arrow left
        if (page > 1) {
          handle_generate_student_pageable(page - 1, amount, students, back);
        } else {
          handle_generate_student_pageable(page, amount, students, back);
        }
        break; 
      
      case 29: // arrow right
        if (page < (amount / 5) + 1) {
          handle_generate_student_pageable(page + 1, amount, students, back);
        } else {
          handle_generate_student_pageable(page, amount, students, back);
        }
        break;
      case 176:
        break;
      default:
        view_option = 0;
        return back(NULL);
      }
    }
  }
} 
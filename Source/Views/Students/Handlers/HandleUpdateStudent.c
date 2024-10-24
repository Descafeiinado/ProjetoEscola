#include <stdio.h>
#include <stdlib.h>

#include "../../../Constants/PersonConstants.h"
#include "../../../Persistence/PersonPersistence.h"
#include "../../DefaultView.h"
#include "../../Utils/ClearScreen.h"
#include "../StudentManagementView.h"

void handle_update_student(Person student) {
  fflush(stdin);
  clear_screen();

  Person *students;

  printf("Prestes a excluir o aluno '%s - %s', digite:\n", student.registration, student.name);
  printf("\n");
}

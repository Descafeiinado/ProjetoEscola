#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "Persistence/PersonPersistence.h"
#include "Views/DefaultView.h"

int main(){
  setlocale(LC_ALL, "Portuguese");
  render_default_view();

  return 0;
}
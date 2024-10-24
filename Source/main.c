#include "Persistence/PersonPersistence.h"
#include "Views/DefaultView.h"
#include <locale.h>
#include <stdio.h>
#include <string.h>

int main(){
  setlocale(LC_ALL, "en_US.UTF-8");
  render_default_view();

  return 0;
}
#include <stdio.h>

int main() {
  printf("Ola, esse projeto nao foi projetado para utilizar Github Codespaces.\n");
  printf("Por favor, utilize a imagem do Docker para rodar o projeto:\n");
  printf(" - Comando: docker run -it -v ./Data:/school/Data descafeiinado/school:1.1\n");
  printf("Ou, se preferir, utilize os binarios ja compilados presentes no diretorio:\n");
  printf(" - Binaries");

  int pause = -1;
  scanf("%d", &pause);

  return 0;
}
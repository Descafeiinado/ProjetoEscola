# Projeto Escola

Desenvolvido para trabalho na disciplina de Laboratório de Programação (INF029) do curso de Análise e Desenvolvimento de Sistemas do Instituto Federal da Bahia.

### Docente
> Renato Novais

### Discentes
> Filipe Lordêlo Fiuza; e
> Júlio dos Reis Sousa

### Problemas conhecidos
- A maioria das variáveis booleanas se encontra como int ao invés do bool do <stdbool.h>;
- Nenhuma acentuação foi colocada nos menus, não consegui mudar a codificação;
- Validação de CPF não implementada; favor ler [isto](https://github.com/Descafeiinado/ProjetoEscola/blob/main/Source/Views/Students/Handlers/HandleCreateStudent.c#L14).

# Para compilar o projeto:
## No Windows

Você precisará ter instalado os seguintes softwares:
- Chocolatey (disponível [aqui](https://chocolatey.org/install))
- MSYS2 MinGW (disponível [aqui](https://www.msys2.org))

Passos para instalar as dependências:

1. Após verificar que os Softwares necessários estão instalados, abra o Bash do MinGW64;
2. Instale a dependência do GCC utilizando o comando `pacman -S mingw-w64-x86_64-gcc`.

Passos gerais:

1. No diretório do projeto, renomeie o arquivo `Makefile-win` para `Makefile`;
2. Execute o comando `make`.

## No Linux

Você precisará ter instalado os seguintes softwares:
- GCC;
- Dependências de Projeto (Lib GCC)

Passos para instalar as dependências:

1. Após verificar que os Softwares e Dependências necessários estão instalados, abra o Terminal do seu Linux.

Passos gerais:

1. No diretório do projeto, renomeie o arquivo `Makefile-unix` para `Makefile`;
2. Execute o comando `make`.

# Para rodar o projeto:
## No Windows
Basta executar o arquivo `main.exe` gerado, utilizando `./main.exe` no seu terminal habitual. (Certifique-se de estar no diretório em que se encontra o executável. Por padrão é o diretório Binaries na pasta raíz do repositório.)

## No Linux (Com docker)
Você precisará ter instalado os seguintes softwares:

- Docker (disponível aqui)
- (Opcional) Docker Compose

Preferencialmente, utilize a imagem do Docker disponível neste repositório. Particularmente, o método de utilização via Docker Compose é meio _Hacky_, por que não tem outro método efetivo de anexar o shell do Container, já que o Compose pode receber múltiplos containers. 

### Via Docker

1. Utilize o comando `docker run -it -v ./Data:/school/Data descafeiinado/school:1.0`.

### Via Docker Compose

1. Execute o comando `docker-compose up -d`;
2. Execute o comando `docker logs NOME_DO_CONTAINER`, onde você deve substituir NOME_DO_CONTAINER pelo nome do container criado pelo Docker Compose;
3. Execute o comando `docker attach NOME_DO_CONTAINER`, onde você deve substituir NOME_DO_CONTAINER pelo nome do container criado pelo Docker Compose.

## No Linux (Sem docker)
Basta rodar o executável disponível na pasta `Binaries` utilizando o comando `./Binaries/main`.

Caso apresente um problema de permissões, basta utilizar `sudo chmod u+x ./Binaries/main` e refazer o passo acima.

# Contribuidores

- [@Descafeiinado](https://github.com/Descafeiinado)
- [@trincv](https://github.com/trincv)

## Nota
Nós dois desenvolvemos versões diferentes, mas estavamos colaborando nas dúvidas e resolução de problemas.
Este repositório foi desenvolvido por [@Descafeiinado](https://github.com/Descafeiinado), com a ajuda de [@trincv](https://github.com/trincv).
O repositório da versão desenvolvida por [@trincv](https://github.com/trincv) e com ajuda de [@Descafeiinado](https://github.com/Descafeiinado), pode ser encontrado
[aqui](https://github.com/trincv/INF029-FilipeFiuza)!
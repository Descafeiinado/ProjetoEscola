# Projeto Escola

Desenvolvido para trabalho na disciplina de Laboratório de Programação (INF029) do curso de Análise e Desenvolvimento de Sistemas do Instituto Federal da Bahia.

### Docente
> Renato Novais

### Discentes

> Filipe Lordêlo Fiuza
> Júlio dos Reis Sousa

# Para compilar o projeto:
## No Windows

Você precisará ter instalado os seguintes softwares:
- Chocolatey (disponível [aqui](https://chocolatey.org/install))
- MSYS2 MinGW (disponível [aqui](https://www.msys2.org))

Passos para instalar as dependências:

1. Após verificar que os Softwares necessários estão instalados, abra o Bash do MinGW64;
2. Instale a dependência do GCC utilizando o comando `pacman -S mingw-w64-x86_64-gcc`;

Passos gerais:

1. No diretório do projeto, renomeie o arquivo `Makefile-win` para `Makefile`.
2. Execute o comando `make`.

## No Linux

Você precisará ter instalado os seguintes softwares:
- Clang (tutorial para instalação disponível [aqui](https://www.edivaldobrito.com.br/como-instalar-a-ultima-versao-do-clang-no-ubuntu-e-derivados/))

Passos para instalar as dependências:

1. Após verificar que os Softwares necessários estão instalados, abra o Terminal do seu Linux.

Passos gerais:

1. No diretório do projeto, renomeie o arquivo `Makefile-unix` para `Makefile`.
2. Execute o comando `make`.

# Para rodar o projeto:
## No Windows
Basta executar o arquivo `main.exe` gerado, utilizando `./main.exe` no seu terminal habitual. (Certifique-se de estar no diretório em que se encontra o executável. Por padrão é o diretório Binaries na pasta raíz do repositório.)

## No Linux (Com docker)
Você precisará ter instalado os seguintes softwares:

- Docker (disponível aqui)
- (Opcional) Docker Compose

Preferencialmente, utilize a imagem do Docker disponível neste repositório. Particularmente, o método de utilização via Docker Compose é meio _Hacky_, por que não tem outro método efetivo de anexar o shell do Container, já que o Compose pode receber múltiplos containers. 

### Via Docker Puro

1. Utilize o comando `docker run -it -v ${PWD}/Data:/school/Data descafeiinado/school:1.0`.

### Via Docker Compose

1. Execute o comando `docker-compose up -d`.
2. Execute o comando `docker logs NOME_DO_CONTAINER`, onde você deve substituir NOME_DO_CONTAINER pelo nome do container criado pelo Docker Compose.
3. Execute o comando `docker attach NOME_DO_CONTAINER`, onde você deve substituir NOME_DO_CONTAINER pelo nome do container criado pelo Docker Compose.

## No Linux (Sem docker)
Basta rodar o executável disponível na pasta `Binaries` utilizando o comando `./Binaries/main`.

Caso apresente um problema de permissões, basta utilizar `sudo chmod u+x ./Binaries/main` e refazer o passo acima.
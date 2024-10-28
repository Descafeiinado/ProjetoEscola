FROM ubuntu:22.04

RUN mkdir -p /school
COPY ./Binaries/main /school
WORKDIR /school

CMD ["/school/main"]
@echo off

:start
cls
echo Compilando...

cd src

echo Compilando gerais.c
gcc gerais.c -o ../obj/gerais.o -Wall -c

echo Compilando incluir.c
gcc incluir.c -o ../obj/incluir.o -Wall -c

echo Compilando excluir.c
gcc excluir.c -o ../obj/excluir.o -Wall -c

echo Compilando alterar.c
gcc alterar.c -o ../obj/alterar.o -Wall -c

echo Compilando listar.c
gcc listar.c -o ../obj/listar.o -Wall -c

echo Compilando localizar.c
gcc localizar.c -o ../obj/localizar.o -Wall -c

echo Compilando main.c
gcc ../main.c -o ../obj/main.o -Wall -c

cd ../obj
echo Criando agenda.exe
gcc -o ../agenda.exe main.o gerais.o incluir.o excluir.o alterar.o listar.o localizar.o

echo Arquivo criado.
pause
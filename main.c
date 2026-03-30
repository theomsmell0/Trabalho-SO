#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
extern void ler_mostrar(char *arquivo, char *vazio, int tamanho);
int main(){
char *nome_arquivo = "texto.txt";
char buffer[1024];

ler_mostrar(nome_arquivo, buffer, 1024);

return 0;
}

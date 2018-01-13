#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){
    
    int i = 0, qnt = 0;
    char nome[50];
    
    printf("digite um nome: ");
    scanf("\n%[^\n]", nome);
    while(nome[i] != '\0'){
          qnt++;
          i++;                     
    }
    system("cls");
    printf("a quantidade de letras e: %d\n\n", qnt);
    
    system("pause");
    return 0;    
}

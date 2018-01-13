#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    
    char nome[50];
    int n = 0, vogais = 0;
    
    printf("digite a quantidade de nomes: ");
    scanf("%d", &n);
    system("cls");
    while(n > 0){
          printf("digite o nome: ");
          scanf("\n%[^\n]", nome);
          if(nome[1] == 'a' || nome[1] == 'A'){
                  vogais++;  
          }
          else if(nome[1] == 'e' || nome[1] == 'E'){
                  vogais++;
          }
          else if(nome[1] == 'i' || nome[1] == 'I'){
                  vogais++;
          }
          else if(nome[1] == 'o' || nome[1] == 'O'){
                  vogais++;
          }
          else if(nome[1] == 'u' || nome[1] == 'U'){
                  vogais++;
          }   
          n--;                  
    }
    system("CLS");
    printf("A quantidade de nomes que comessam com vogais e: %d\n\n", vogais);
    
    system("pause");
    return 0;   
}

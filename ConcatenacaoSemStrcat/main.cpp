#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    char str1[50];
    char str2[50];
    int c1 = 0;
    int c2 = 0;
    
    
    printf("digite uma string: ");
    scanf("\n%[^\n]", str1);
    printf("\ndigite outra string: ");
    scanf("\n%[^\n]", str2);
    
    c1 = strlen(str1);
    c2 = strlen(str2);
    if (c1 + c2 < 50) {
       str1[c1] = ' ', c1++;
       for(int i = 0; i < c2; i++, c1++){
           str1[c1] = str2[i];  
    } 
    system("CLS");
    printf("\nas strings juntas formam %s\n", str1);
    }
    else {
         system("CLS");
         printf("Estorou o limite de caracteres da variavel\n");
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

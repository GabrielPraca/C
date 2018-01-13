#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	char string[20];
	char letra;
	int cont = 0;
	
	printf("Digite uma palavra: ");
	scanf("\n%[^\n]", string);
	printf("\nDigite a letra para contar na palavra: ");
	scanf("\n%c", &letra);
	
	for(int i = 0; i < 20; i++){
		if(string[i] == letra){
			cont++;
		}
	}
	
	system("CLS");
	printf("Tem %d letras %c na palavra %s\n", cont, letra, string);
	system("PAUSE");
	return 0;
}

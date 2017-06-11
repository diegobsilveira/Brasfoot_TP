#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#define MAX 16

typedef struct time{
	char nome[40];
}Time;

int main(){
	
	//printf("FUTIBRAS DA INTERFACE CAGADA");
	system("COLOR 2E");
	FILE *fMenu;
	fMenu = fopen("data/menu.txt","r");
	char buf[100];
	
	while(!feof(fMenu)){
		fgets(buf,100,fMenu);
		printf("\n\t\t %s",buf);
	}
	
	
	printf("\n\n\t\t\t A P E R T E  U M A  T E C L A  P A R A  C O N T I N U A R\n\t\t\t ");
	getch();   
	
	
	
	
	
	Time times[MAX];
	
	FILE *fTimes;
	fTimes = fopen("data/times.txt","r");
	
	if(fTimes == NULL){
		printf("ERR - Arquivos estão faltando para a execução do programa.");	
		exit(1);
	}
	
	int qtd_times = 0;
	
	while(!feof(fTimes) || qtd_times>=MAX){
		fgets(buf,40,fTimes);
		printf("\n %s",buf);
		strcpy(buf, times[qtd_times].nome);		
		qtd_times++;	
	}
	
	
	
	return 0;
}

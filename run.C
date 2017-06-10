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
	
	Time times[MAX];
	
	FILE *fTimes;
	fTimes = fopen("data/times.txt","r");
	char buf[40];
	
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

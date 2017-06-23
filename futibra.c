#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 16

typedef struct time{
	char nome[40];
	int pontos;
}Time;

void tela_inicial(){
	system("COLOR 2E");
	FILE *fMenu;
	fMenu = fopen("menu.txt","r");
	char buf[100];
	
	if(fMenu!=NULL){		
		while(!feof(fMenu)){
			fgets(buf,100,fMenu);
			printf("\n\t\t %s",buf);
		}	
	}
	
	printf("\n\n\t\t\t A P E R T E  U M A  T E C L A  P A R A  C O N T I N U A R\n\t\t\t ");
	getch(); 
}

void embaralha_times(Time *times){    
    int i;
    Time t;
    for (i = 0; i < MAX-1 ; i++){
      int j = i + rand() / (RAND_MAX / (MAX - i) + 1);
      t = times[j];
      times[j] = times[i];
      times[i] = t;
    }
}

int set_times(Time *times, int opcao){
	FILE *fTimes;
	char buf[40];
	int i;
	
	if(opcao == 1){	
		fTimes = fopen("times.txt","w");
		if(fTimes == NULL){		
			return 1;
		}else{
			int uo;
			for(i=0; i<MAX; i++){				
				scanf("%s",buf);
				fprintf(fTimes,"%s\n",buf);
				strcpy(times[i].nome, buf);	
				times[i].pontos=0;
			}
			fclose(fTimes);
		}
	}else{
		fTimes = fopen("times.txt","r");
		if(fTimes == NULL){			
			return 1;
		}else{		
			for(i=0; i<MAX; i++){
				fscanf(fTimes,"%s",buf);
				strcpy(times[i].nome,buf);	
				times[i].pontos=0;				
			}
		}
		fclose(fTimes);
	}
	
	return 0;
}

int mostra_times(Time *times){
	int i;
	for(i=0; i<MAX; i++){		
		printf("\n\t\t%s",times[i].nome);				
	}
}

int get_rodada(){
	FILE *fRodada = fopen("rodadas.txt","r");
	int rodada=0;
	if(fRodada==NULL){
		return -1;
	}else{
		fscanf(fRodada,"%d",&rodada);		
		fclose(fRodada);
	}
	return rodada;	
}

void mostra_tabela(Time *times){
	int i;
	printf("\n\tPONTUACAO DA RODADA %d",get_rodada());
	for(i=0;i<MAX;i++){
		printf("\n\t\t%s - %d pontos",times[i].nome,times[i].pontos);
	}
}

int jogar_rodada(Time *times){	

	embaralha_times(times);
	
	int i;
	int gols_t1,gols_t2;
	
	srand(time(NULL));
	for(i=0;i<MAX;i++){				
		gols_t1 = rand()%7;
		gols_t2 = rand()%7;
		
		if(i%2==0){						
			if(gols_t1>gols_t2){
				times[i].pontos+=3;
			}else
			if(gols_t1<gols_t2){
				times[i+1].pontos+=3;
			}else			
			if(gols_t1=gols_t2){
				times[i].pontos+=1;
				times[i+1].pontos+=1;
			}	
			printf("\n\t\t%s (%d) x (%d) %s %d %d",times[i],gols_t1,gols_t2,times[i+1],times[i].pontos,times[i+1].pontos);		  
		}
		
	}
	
	int nrodada = get_rodada();
	FILE *fRodada = fopen("rodadas.txt","w");
	if(fRodada==NULL){
		return -1;
	}else{
		fprintf(fRodada,"%d",nrodada+1);		
		fclose(fRodada);
	}
	
	return 0;
}

int comeca_campeonato(){	
	FILE *fRodada = fopen("rodadas.txt","w");
	
	if(fRodada==NULL){
		return -1;
	}else{
		fprintf(fRodada,"0\n");
		fclose(fRodada);
	}
}

int main(){
	
	Time times[MAX];
		
	tela_inicial();	
		
	int opcao;	
	do{
		printf("Digite\n\t\t\t 1 para cadastrar os 16 times\n\t\t\t 2 para usar os times salvos/default\n\t\t\t ");
		scanf("%d",&opcao);
	}while(opcao!=1 && opcao!=2);
	
	set_times(times,opcao);	
	
	system("cls");	
	printf("\n\tOs %d times sao: ",MAX);
	
	mostra_times(times);
	comeca_campeonato();
	
	while(opcao!=3){		
		do{		
			printf("\n\tDigite 1 para comecar a %d Rodada",get_rodada()+1);
			printf("\n\tDigite 2 para ver a pontuacao dos times");
			printf("\n\tDigite 3 para fechar",get_rodada()+1);
			scanf("%d",&opcao);
		}while(opcao!=1 && opcao!=2 && opcao!=3);
			
		if(opcao==1){
			system("cls");	
			jogar_rodada(times);
		}else
		if(opcao==2){
			system("cls");	
			mostra_tabela(times);
		}		
	}		

	return 0;
}

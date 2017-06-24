#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 16	
//MAX é referente ao valor de times do campeonato

typedef struct time{ // Representa um time
	char nome[40];	
	int pontos;
}Time;

void tela_inicial(){	// Imprime a tela de apresentação
	system("COLOR 2E");	// Muda a cor do prompt para verde e amarelo
	FILE *fMenu;
	fMenu = fopen("menu.txt","r");
	char buf[100];
	
	if(fMenu!=NULL){		// Lê o ASCII ART DE MENU.TXT E IMPRIME
		while(!feof(fMenu)){
			fgets(buf,100,fMenu);
			printf("\n\t\t %s",buf);
		}	
	}
	
	printf("\n\n\t\t\t A P E R T E  U M A  T E C L A  P A R A  C O N T I N U A R\n\t\t\t ");
	getch(); 
}

void embaralha_times(Time *times){    // Embaralha o vetor de times para variar as partidas nas rodadas
    int i;
    Time t;
    for (i = 0; i < MAX-1 ; i++){	// Usa da aleatoriedade de RAND() para trocar as posições dos times no vetor
      int j = i + rand() / (RAND_MAX / (MAX - i) + 1);
      t = times[j];
      times[j] = times[i];
      times[i] = t;
    }
}

void set_times(Time *times, int opcao){    // Define os times participantes
	FILE *fTimes;
	char buf[40];
	int i;
	
	if(opcao == 1){	 // Opção 1 representa que o usuario desejou cadastrar os times
		fTimes = fopen("times.txt","w");
		if(fTimes != NULL){	
			for(i=0; i<MAX; i++){	// Escreve cada time no arquivo e atribui valores às instancias da struct
				scanf("%s",buf);	// Recebe via teclado o nome do time
				fprintf(fTimes,"%s\n",buf); // Grava o nome em arquivo
				strcpy(times[i].nome, buf);	
				times[i].pontos=0;
			}
			fclose(fTimes);
		}
	}else{	 // Opção 2 representa que o usuario desejou carregar os times do arquivo times.txt
		fTimes = fopen("times.txt","r");
		if(fTimes != NULL){		
			for(i=0; i<MAX; i++){	// Lê cada time do arquivo e atribui valores às instancias da struct
				fscanf(fTimes,"%s",buf); 
				strcpy(times[i].nome,buf);	
				times[i].pontos=0;				
			}
		}
		fclose(fTimes);
	}
}

void mostra_times(Time *times){  // Imprime todos os times participantes
	int i;
	for(i=0; i<MAX; i++){		
		printf("\n\t\t%s",times[i].nome);				
	}
}

int get_rodada(){ // Retorna o valor da rodada atual
	FILE *fRodada = fopen("rodadas.txt","r"); // Lê rodadas.txt
	int rodada=0; 
	if(fRodada==NULL){
		return -1;
	}else{
		fscanf(fRodada,"%d",&rodada);		
		fclose(fRodada);
	}
	return rodada;	// Devolve o valor obtido
}

void mostra_tabela(Time *times){	// Apresenta a pontuação dos times 
	int i;
	printf("\n\tPONTUACAO DA RODADA %d",get_rodada()); // Mostra à qual rodada a pontuação corresponde 
	for(i=0;i<MAX;i++){
		printf("\n\t\t%s - %d pontos",times[i].nome,times[i].pontos);   // Imprime cada time e seus pontos
	}
}

void jogar_rodada(Time *times){		// Realiza as partidas e apresenta

	embaralha_times(times);		// Embaralha a posição dos times para variar as partidas
	
	int i;
	int gols_t1,gols_t2; // Guardam os gols do time 1 e do time 2, respectivamente
	
	srand(time(NULL));
	for(i=0;i<MAX;i++){				
		gols_t1 = rand()%7;	  // Os valores de gol são gerados aleatoriamente, indo até 7 gols
		gols_t2 = rand()%7;
		
		if(i%2==0){		// i%2==0 representa que com times[i] e times[i+1] pode ser obtido um par de times
			if(gols_t1>gols_t2){  // Em caso de Vitoria +3 pontos para o vencedor
				times[i].pontos+=3;  
			}else
			if(gols_t1<gols_t2){	// Em caso de Vitoria +3 pontos para o vencedor
				times[i+1].pontos+=3;
			}else			
			if(gols_t1=gols_t2){	// Em caso de Empate +1 ponto para ambos
				times[i].pontos+=1;
				times[i+1].pontos+=1;
			}	
			printf("\n\t\t%s (%d) x (%d) %s %d %d",times[i],gols_t1,gols_t2,times[i+1],times[i].pontos,times[i+1].pontos);	// Dá a saida dos jogos da rodada	  
		}
		
	}
	
	int nrodada = get_rodada();
	FILE *fRodada = fopen("rodadas.txt","w"); // Abre o arquivo das rodadas para atualizar o número da rodada atual
	if(fRodada!=NULL){	
		fprintf(fRodada,"%d",nrodada+1);		
		fclose(fRodada);
	}
	
}

void comeca_campeonato(){	// Inicia o campeonato em rodada 0 (Logo antes da primeira rodada)
	FILE *fRodada = fopen("rodadas.txt","w"); 
	
	if(fRodada!=NULL){
		fprintf(fRodada,"0\n"); // Grava rodada 0 em rodadas.txt
		fclose(fRodada);
	}
}

int main(){
	
	Time times[MAX]; // Instancia o vetor com os 16 times (MAX)
		
	tela_inicial();	// Chama a tela de apresentação
		
	int opcao; // Representará escolhas do menu
	do{
		printf("Digite\n\t\t\t 1 para cadastrar os 16 times\n\t\t\t 2 para usar os times salvos/default\n\t\t\t ");
		scanf("%d",&opcao);
	}while(opcao!=1 && opcao!=2);  // Não deixa prosseguir se não for válida a opção
	
	set_times(times,opcao);	 // Define os times de acordo com a opção escolhida acima (1 = cadastrar | 2 = carregar do arquivo)
	
	system("cls");	// Limpa a tela para não haver scroll
	printf("\n\tOs %d times sao: ",MAX);
	
	mostra_times(times);  // Imprime a lista de times
	comeca_campeonato();  // Inicia o campeonato em rodada 0 (Logo antes da primeira rodada)
	
	while(opcao!=3){ 	// Escolhas entre jogar rodada (1), ver pontuações (2) e sair (3)		
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_LINHA 1000	
#define MAX_ARGS 100

void prompt();
void pegaComandoArgs(char* linha, char** comando, char** args);
void executaComando(char* comando, char** args);
void protegePraCaramba(char* caminho_arquivo);
void liberaGeral(char* caminho_arquivo);
void rodeVeja(char** args);
void rode(char** args);

int main()
{
	while(1)
	{
		char* comando;
		char* args[MAX_ARGS];
		char linha[MAX_LINHA];
		comando = NULL;

		prompt();
		fgets(linha, sizeof(linha), stdin); 	/*pega uma linha de entrada*/
		if(feof(stdin)) break;					/*verifica se EOF aconteceu*/
		
		pegaComandoArgs(linha, &comando, args); /*divide a linha em comando e argumentos, e retorna nas respectivas variaveis*/
		if(comando != NULL)						/*verifica se foi dado um comando*/
			executaComando(comando, args);
	}
	return 0;
}
/*printa um prompt*/
void prompt(){printf("$ ");}

/*pega a linha passada e a retorna dividida em comando e args*/
void pegaComandoArgs(char* linha, char** comando, char** args)
{
	int i = -1;
	char* aux;
	aux = *comando = strtok(linha, " \n");
	
	while(aux != NULL)
		args[++i] = aux =  strtok(NULL, " \n");
	
}

/*executa o comando passado de acordo com qual ele for*/
void executaComando(char* comando, char** args)
{
	if(strcmp(comando, "protegepracaramba") == 0)
		protegePraCaramba(args[0]);
	else if(strcmp(comando, "liberageral") == 0)
		liberaGeral(args[0]);
	else if(strcmp(comando, "rodeveja") == 0)
		rodeVeja(args);
	else if(strcmp(comando, "rode") == 0)
		rode(args);
	else
		printf("'%s' nao e um comando valido\n", comando);
	
}
/*altera a proteção de um arquivo para 000*/
void protegePraCaramba(char* caminho_arquivo){chmod(caminho_arquivo, 0000);}

/*altera a proteção de um arquivo para 777*/
void liberaGeral(char* caminho_arquivo){chmod(caminho_arquivo, 0777);}

/*roda o programa passado (passando seus respectivos argumetos) e espera pelo seu termino, além de avisar qual foi status de retorno*/
void rodeVeja(char** args)
{
	int ret;
	int pid = fork();
	if(pid != 0)
		waitpid(pid, &ret,0);
	else
		execve(args[0], args, 0);

	printf("O programa '%s' retornou com codigo %d\n", args[0], ret);
}

/*roda o programa passado (passando seus respectivos argumentos) em background*/
void rode(char** args)
{
	if(fork() == 0)
		execve(args[0], args, 0);
}

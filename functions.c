//Roda a Roda- Arquivo auxiliar 1
//Escrito por: Pâmela Martins Nunes
//Projeto do curso de Logica de Programação do IFSP

#include "rodaarodah.h"

void	jogo(t_bdr *star)
{

	star->countPercorrer = 0;
	star->indexAcertosPremio = 0;
	printf( "\tA palavra está associada com: %s\n\n\n", star->pista);
	while ((star->countPercorrer <= star->countResposta) && (star->verifyRepeat == 0))
	{
		if (star->resposta[star->countPercorrer] == star->entrada)
		{
			star->respostaAux[2 * star->countPercorrer] = star->entrada;
			star->indexAcertos++;
			star->indexAcertosPremio++;
		}
		star->countPercorrer++;
	}
	star->indexLetras = star->countResposta - star->indexAcertos;
	if (star->acertou == 1)
		star->premioPote = star->indexAcertosPremio * star->premio;
	if (star->indexjog == 1)
		star->player1 = star->player1 + star->premioPote;
	else if (star->indexjog == 2)
		star->player2 = star->player2 + star->premioPote;
	else if (star->indexjog == 3)
		star->player3 = star->player3 + star->premioPote;
	star->premioPote = 0.0;
	printf("\t\t%s\n\n", star->respostaAux);
	printf("\n%s\t\t\t\t%s\t\t\t%s\n"
		"=========\t\t\t=========\t\t\t=========\n"
		"R$ %.f\t\t\t\t R$%.f\t\t\t\t R$%.f\t\t\n", star->jogador1, star->jogador2, star->jogador3, star->player1, star->player2, star->player3);
}

void	play(t_bdr *star)
{
	//sortear premio
	int resposta = 1;

	if (star->indexLetras <= 3)
	{
		star->respostainput = malloc(star->countResposta +1);
		star->premio = star->premio * star->indexLetras;
		int rodadasFinais = 0;
		while ((star->indexjog <= 3) && rodadasFinais < 3)
		{
			printf("\tA palavra está associada com: %s\n\n\n", star->pista);
			printf("\t\t%s\n\n", star->respostaAux);
			printf("\n%s\t\t\t\t%s\t\t\t%s\n"
					"=========\t\t\t=========\t\t\t=========\n"
					"R$%3.f\t\t\t\t R$%3.f\t\t\t\t R$%3.f\t\t\n", star->jogador1, star->jogador2, star->jogador3, star->player1,
					star->player2, star->player3);
			printf("Jogador %i: Faltam %i letras para completar a palavra\n"
					"Você tem 5 segundos para pensar e depois digitar a palavra...5...4...3...2...1...\n", star->indexjog, star->indexLetras);
			sleep(3);
			printf("Valendo R$ %.2f a palavra é:_", star->premio);
			scanf(" %[^\n]%*c", &*star->respostainput);
			for (int i = 0; i <= star->countResposta ; i++)
			{
				star->respostainput[i] = toupper(star->respostainput[i]);
			}
			resposta = strcmp(star->respostainput, star->resposta); //checkResposta(&*star);
			if (resposta == 0)
			{
				endGame(&*star);
				free(star->respostainput);
				free(star->respostaAux);
				exit(0);
			}
			star->indexjog++;
			if (star->indexjog > 3)
						star->indexjog = 1;
			rodadasFinais++;
			if (rodadasFinais >= 3)
			{
				printf("\033[1;31mNINGUÉM GANHOU!!!\n\033[0m");
				star->Winner = "NINGUÉM GANHOU!";
				star->premioPote = 0;
				saveData(&*star);
				exit(0);
			}
		}

	}
	printf("Jogador %i :Roda a roda!\n", star->indexjog);
	sorteiaPremio(&*star);
	printf("Uma letra por R$ %.2f: _ \n", star->premio);
	scanf(" %c", &star->entrada);
	star->entrada = (char)star->entrada;
	star->entrada = toupper(star->entrada);
}

void checkLetra(t_bdr *star)
{
	int i = 2 * star->countResposta;
	int j = 0;
	star->verifyRepeat = 0;
	int verifyOcurrency = 0;
	star->countPercorrer = 0;
	while ((star->countPercorrer <= star->countResposta) && star->verifyRepeat == 0)
	{
		if (star->respostaAux[star->countPercorrer] == star->entrada)
		{
			star->acertou = 0;
			star->verifyRepeat = 1;
			star->entrada = (char)star->entrada;
			printf("A letra:%c já foi dita anteriormente\n", star->entrada);
			break;
		}
		star->countPercorrer++;
	}
	while ((j <= i) && star->verifyRepeat == 0)
	{
		if (star->resposta[j] == star->entrada)
		{
			verifyOcurrency = 1;
			star->acertou = 1;
		}
		j++;
	}
	if ((verifyOcurrency == 0) && (star->verifyRepeat == 0))
	{
		star->acertou = 0;
		star->entrada = (char)star->entrada;
		printf("Não existe a letra: %c na palavra \n", star->entrada);
	}
}

void	definePlayer(t_bdr *star)
{
	if (star->acertou == 0)
	{
		star->indexjog++;
		if ((star->indexjog > 3) && (star->indexLetras > 3))
			star->indexjog = 1;
		star->acertou = 1;
		printf("A vez será passada para o jogador %i.\n", star->indexjog);
		sleep(3);
	}
}

void	endGame(t_bdr *star)
{
		if (star->indexjog == 1)
			star->player1 = star->player1 + star->premio;
		else if (star->indexjog == 2)
			star->player2 = star->player2 + star->premio;
		else if (star->indexjog == 3)
			star->player3 = star->player3 + star->premio;
		printf("\t\tA palavra está associada com: %s\n"
				"\t\t\t %s\n"
				"\n%s\t\t\t\t%s\t\t\t%s\n"
				"=========\t\t\t=========\t\t\t=========\n"
				"R$ %.f\t\t\t\t R$%.f\t\t\t\t R$%.f\t\t\n", star->pista, star->respostainput, star->jogador1, star->jogador2, star->jogador3, star->player1, star->player2, star->player3);
		if (star->indexjog == 1)
		{
			printf("\033[1;3mVENCEDOR\n\033[0m");
			star->Winner = star->jogador1;
			star->premioPote = star->player1;
			saveData(&*star);
		}
		else if (star->indexjog == 2)
		{
			printf("\033[1;3m\t\t\t\t VENCEDOR\n\033[0m");
			star->Winner = star->jogador2;
			star->premioPote = star->player2;
			saveData(&*star);
		}
		else if (star->indexjog == 3)
		{
			printf("\033[1;3m\t\t\t\t\t\t\t\t VENCEDOR\n\033[0m");
			star->Winner = star->jogador3;
			star->premioPote = star->player3;
			saveData(&*star);
		}
		printf( "\n\nFIM DO JOGO!!!\n OBRIGADA POR JOGAR!!!\n");

		sleep(3);
}

int genRandoms(int upper)
{
	time_t t;
	int num = 0;
	srand((unsigned) time(&t));
	num = rand() % (upper + 1);
	return (num);
}

void sorteio(t_bdr *star)
{
	FILE *palavras = fopen("PALAVRAS.dat", "r");
	if (! palavras ) // equivalent to saying if ( in_file == NULL )
	{
		printf("oops, file can't be read\n");
		exit(-1);
	}
	char buffer[300];
	int 	i = 0;
	char	aux[2];
	while ( i <= star->test)
	{
		fgets(buffer, 300, palavras);
		i++;
	}
	i = 0;
	while (buffer[i] != '\t')
	{
		star->pista[i] = buffer[i]; //place a primeira palavra da linha
		i++;
	}
	star->pista[i] = '\0';
	i++;
	aux[0] = buffer[i];
	i++;
	star->numerodPalvras =(int)aux[0] -48;

	printf("BEFORE %i\n", star->numerodPalvras);

	star->numerodPalvras = genRandoms(star->numerodPalvras);

	star->indexPalavras = star->numerodPalvras;

	printf("AFTER %i\n", star->indexPalavras);
	printf("I Before %i\n", i);
	int j = 0;
	while(j < star->indexPalavras)
	{
		if(buffer[i]== '\t')
		{
			j++;
			
		}
		i++;
	}
	printf("I after %i\n", i);
	int y = 0;
	while (buffer[i] != '\t')
	{
		star->resposta[y] = buffer[i]; //atribui a palavra sorteada
		i++;
		y++;
	}
	star->resposta[y] ='\0';
	fclose(palavras);
}

void	sorteiaPremio(t_bdr *star)
{
	star->upper = 0;
	int i = 0;
	char auxiliar[15];
	FILE *premio = fopen("PREMIOS.dat", "r");
	if (! premio ) // equivalent to saying if ( in_file == NULL )
	{
		printf("oops, file can't be read\n");
		exit(-1);
	}
	char buffer[15];
	star->test = genRandoms(12);
	while ( i <= star->test)
	{
		fgets(buffer, 15, premio);
		i++;
	}
	i = 0;
	while (buffer[i] != '\n')
	{
		auxiliar[i] = buffer[i];
		i++;
	}
	auxiliar[i] = '\0';
	printf("Roda sendo rodada...\n");
	star->premio = atof(auxiliar);
	//printf("premio:%f\n", star->premio);
	if (star->premio == 0.0)
	{

		printf("PASSA A VEZ!\n\n\n\n");
		star->indexjog++;
		if ((star->indexjog > 3) && (star->indexLetras > 3))
			star->indexjog = 1;
		printf("A vez será passada para o jogador %i.\n", star->indexjog);
		sleep(3);
		sorteiaPremio(&*star);


	}
	else if (star->premio == 0.1)
	{
		printf("Roda sendo rodada...\n");
		printf("PERDE TUDO!\n\n\n\n");
		if (star->indexjog == 1)
			star->player1 = 0.0;
		else if (star->indexjog == 2)
			star->player2 = 0.0;
		else if (star->indexjog == 3)
			star->player3 = 0.0;
		sleep(3);
		sorteiaPremio(&*star);

	}
	fclose(premio);
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void makeString(t_bdr *star)
{
	int i = 0;
	int y = 0;
	y = star->countResposta * 2;
	while (i < y)
	{
		star->respostaAux[i] = '_';
		i++;
		star->respostaAux[i] = ' ';
		i++;
	}
	star->respostaAux[i] = '\0';
}
void checkName(t_bdr *star, int identifier)
{
	int i = 0;
	if (identifier == 1)
	{
		i = strlen(star->jogador1);
		if (i > 6)
			star->jogador1[7] = '\0';
	}
	else if (identifier == 2)
	{
		i = strlen(star->jogador2);
		if (i > 8)
			star->jogador2[9] = '\0';
		if (i < 8)
		{
			while (i < 9)
			{

				star->jogador2[i] = ' ';
				i++;
			}
			i++;
			star->jogador2[i] = '\0';
		}
	}
}
void	saveData(t_bdr *star)
{
	//star->Winner = "Pamela";
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char s[64];
	assert(strftime(s, sizeof(s), "%c", tm));
	int i= 0;
	i = strlen(star->Winner);
	FILE *results = fopen("Resultados.dat", "a");
	if (! results) // equivalent to saying if ( in_file == NULL )
	{
		printf("oops, file can't be read\n");
		exit(-1);
	}
	fprintf(results, "\n%s JOGADOR:%s", s, star->Winner);
	while(i < 16)
	{
		i++;
		fprintf(results, " ");
	}
	fprintf(results, "PREMIAÇÃO:R$%3.f ", star->premioPote);
	fprintf(results,"\n=================================================================");
	fclose(results);
}

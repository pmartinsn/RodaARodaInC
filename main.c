//Roda a Roda
//Escrito por: Pâmela Martins Nunes
//Projeto do curso de Logica de Programação do IFSP
#include "rodaarodah.h"

int main()
{
	int querJogar = 0;
	t_bdr star;
	init(&star);
	star.entrada = '0';
	FILE *palavras = fopen("PALAVRAS.dat", "r");
	if (! palavras ) // equivalent to saying if ( in_file == NULL )
	{
		printf("oops, file can't be read\n");
		exit(-1);
	}
	char buffer[300];
	while (fgets(buffer, 300, palavras) != NULL)
		star.upper++;//somente verifica quantas linhas exitem no arquivo de palavras
	fclose(palavras);
	//genRandoms faz o sorteio da linha a ser usada
	star.test = genRandoms(star.upper);
	sorteio(&star);
	star.countResposta = ft_strlen(star.resposta);
	star.respostaAux = malloc(2 * star.countResposta);
	makeString(&star);
	//primeira view
	//ARTE EM ASCII
	printf( "\t\tBem-vindo ao\n"
	"██████╗░░█████╗░██████╗░░█████╗░  ░█████╗░  ██████╗░░█████╗░██████╗░░█████╗░\n"
	"██╔══██╗██╔══██╗██╔══██╗██╔══██╗  ██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗██╔══██╗\n"
	"██████╔╝██║░░██║██║░░██║███████║  ███████║  ██████╔╝██║░░██║██║░░██║███████║\n"
	"██╔══██╗██║░░██║██║░░██║██╔══██║  ██╔══██║  ██╔══██╗██║░░██║██║░░██║██╔══██║\n"
	"██║░░██║╚█████╔╝██████╔╝██║░░██║  ██║░░██║  ██║░░██║╚█████╔╝██████╔╝██║░░██║\n"
	"╚═╝░░╚═╝░╚════╝░╚═════╝░╚═╝░░╚═╝  ╚═╝░░╚═╝  ╚═╝░░╚═╝░╚════╝░╚═════╝░╚═╝░░╚═╝\n"
	"						By: Pamela M Nunes\n"
			"Para iniciar digite: 1\n Para sair digite: 0\n");
	scanf(" %i", &querJogar);
	//dar nome aos jogadores
	if(querJogar == 1){
		printf( "INSTRUÇÕES:\nO jogo começa pelo primeiro jogador a entrar.\nO jogador pode dizer uma letra por vez\n");
		printf( "Se errar passa a vez, se acertar joga novamente\nSe ao rodas a roda for sorteado: \"0,00 = PASSA A VEZ\" OU \"0,01 = PERDE TUDO\"\n");
		printf( "Quando faltarem 3 letras, ou menos, para completar a(s) palavra(s) o jogador da vez deverá obrigatoriamente responder qual é(são) a(s) palavra(s)\n");
		printf( "VAMOS AO JOGO!!!\n\n\n\n");
		printf( "Qual o nome do Jogador 1?\nNo máximo 06 letras.\n");
		scanf(" %[^\n]%*c", &*star.jogador1);
		checkName(&star, 1);
		printf( "Agora o nome do Jogador 2?\nNo máximo 06 letras.\n");
		scanf(" %[^\n]%*c", &*star.jogador2);
		checkName(&star, 2);
		printf( "Por ultimo, nome do Jogador 3?\nNo máximo 06 letras.\n");
		scanf(" %[^\n]%*c", &*star.jogador3);
		//checkName(&star, 3);
		printf("\t\tA palavra está associada com: %s\n"
				"\n%s\t\t\t\t%s\t\t\t%s\n"
				"=========\t\t\t=========\t\t\t=========\n"
				"R$%3.f\t\t\t\t R$%3.f\t\t\t\t R$%3.f\t\t\n", star.pista, star.jogador1, star.jogador2, star.jogador3, star.player1,
				star.player2, star.player3);
		sleep(3);
		printf("\n\n");
		sorteiaPremio(&star);
		while (star.indexAcertos <= star.countResposta)
		{
			while ((star.indexjog <= 3) && (star.acertou == 1))
			{
				jogo(&star);
				play(&star);
				checkLetra(&star);
				definePlayer(&star);

			}
			if (star.indexjog > 3)
				return(0);
		}
	}
	printf( "FIM DO JOGO!!!\n OBRIGADA POR JOGAR!!!\n");
	free(star.respostainput);
	free(star.respostaAux);
	return(0);
}

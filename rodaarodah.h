#ifndef RODAARODAH_H
# define RODAARODAH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef	struct	s_pf
{
	char	pista[30];
	char	resposta[30];
	char	jogador1[11];
	char	jogador2[11];
	char	jogador3[11];
	char	*Winner;
	char	*respostaAux;
	char	*respostainput;
	char	entrada;
	float	player1, player2, player3;
	float	premio;
	float	premioPote;
	int		indexjog;
	int		indexLetras;
	int		indexAcertos;
	int		indexAcertosPremio;
	int		acertou;
	int		verifyRepeat;
	int		indexPlayer;
	int		test;
	int		upper;
	int		num;
	int		rodada;
	int		countResposta;
	int		countPercorrer;
	int		indexPalavras;
	int		numerodPalvras;
}				t_bdr;

void	init(t_bdr *star);
void	jogo(t_bdr *star);
void 	checkLetra(t_bdr *star);
void 	makeString(t_bdr *star);
int 	genRandoms(int upper);
int 	ft_strlen(char *s);
void	definePlayer(t_bdr *star);
void	endGame(t_bdr *star);
void	play(t_bdr *star);
void	checkName(t_bdr *star, int identifier);
//int		checkResposta(t_bdr *star);
void 	sorteio(t_bdr *star);
void	sorteiaPremio(t_bdr *star);
void	saveData(t_bdr *star);



#endif

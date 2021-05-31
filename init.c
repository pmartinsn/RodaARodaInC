#include "rodaarodah.h"

void	init(t_bdr *star){
	star->player1 = 0.00;
	star->player2 = 0.00;
	star->player3 = 0.00;
	star->premio = 0.0;
	star->premioPote = 0.0;
	star->indexjog = 1;
	star->indexLetras = 0;
	star->indexAcertos = 0;
	star->indexAcertosPremio = 0;
	star->verifyRepeat = 0;
	star->acertou = 1;
	star->indexPlayer = 0;
	star->test = 0;
	star->upper = 0;
	star->num = 0;
	star->rodada = 0;
	star->countResposta = 0;
	star->countPercorrer = 0;
	star->indexPalavras = 0;
	star->numerodPalvras = 0;
	//star->entrada = 0;
}

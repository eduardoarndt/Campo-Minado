#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

const int tm = 10, qtb = 10;
int opc;

char matA[tm][tm];
char matRev[tm][tm];
void menu();
void CriaMat();
void MmatA();
void Mrev();
void compMat(int lin, int col);
void contB(int lin, int col);
void GameLoop();
int verifmat(int li, int cl);

int main() {
	setlocale(LC_ALL, "");
	menu();
	CriaMat();
	GameLoop();
}

void menu() {	
		system("cls");	
		printf("\n       CAMPO MINADO\n");
	do {
		printf("\n (1) Jogar \n (2) Sair\n\n");
		scanf("%d", &opc);

		if (opc == 2) {
			exit(0);
		}
		else if (opc < 1 || opc > 2) {
			printf("Opção invalida!\n\n");			
		}
	} while (opc < 1 || opc > 2);
}

void CriaMat() { //cria matrizz
	for (int l = 0; l < tm; l++) {
		for (int c = 0; c < tm; c++) {
			matA[l][c] = 'X';
			matRev[l][c] = 'X';
		}
	}

	int cont = 0;
	srand(time(NULL));

	while (cont < qtb) { //espalha as bombas aleatoriamente
		int l = rand() % 9;
		int c = rand() % 9;

		if (matA[l][c] == 'X') { //verifica se ja não existe bomba na posição selecionada
			matA[l][c] = 'B';
			matRev[l][c] = 'B';
			cont++;
		}
	}
}

void MmatA() { //mostra matriz
	printf("   0  1  2  3  4  5  6  7  8  9\n");
	for (int l = 0; l < tm; l++) {
		printf("%d  ", l);
		for (int c = 0; c < tm; c++) {
			if (matA[l][c] == 'B') { // esconde as bombas do usuario
				printf("X  ");
			}
			else {
				printf("%c  ", matA[l][c]);
			}
		}
		printf("\n");
	}
}

void Mrev() { //mostra matriz
	for (int l = 0; l <= 9; l++) {// abre as casas ou preenche com o numero de bombas ao redor
		for (int c = 0; c <= 9; c++) {
			if (matRev[l][c] != 'X' || matRev[l][c] == 'B') {
				continue;
			}
			else {
				contB(l, c);
			}
		}
	}

	//mostra a matriz pra mim poder testar o codigo 
	
	printf("\n MODO DEV \n\n");
	printf("   0  1  2  3  4  5  6  7  8  9\n");
	for (int l = 0; l < tm; l++) {
		printf("%d  ", l);
		for (int c = 0; c < tm; c++) {
			printf("%c  ", matRev[l][c]);
		}
		printf("\n");
	}

}

void contB(int lin, int col) { //Testa as 8 posições ao redor
	int cont = 0;
	if (lin != 0) {
		if (col != 0) {
			if (matRev[lin - 1][col - 1] == 'B') {
				cont++;
			}
		}
		if (matRev[lin - 1][col] == 'B') {
			cont++;
		}
		if (col != 9) {
			if (matRev[lin - 1][col + 1] == 'B') {
				cont++;
			}
		}
	}
	if (col != 0) {
		if (matRev[lin][col - 1] == 'B') {
			cont++;
		}
	}
	if (col != 9) {
		if (matRev[lin][col + 1] == 'B') {
			cont++;
		}
	}
	if (lin != 9) {
		if (col != 0) {
			if (matRev[lin + 1][col - 1] == 'B') {
				cont++;
			}
		}
		if (matRev[lin + 1][col] == 'B') {
			cont++;
		}
		if (col != 9) {
			if (matRev[lin + 1][col + 1] == 'B') {
				cont++;
			}
		}
	}
	
	if (cont > 0) {
		matRev[lin][col] = cont + 48;
	}
	else {
		matRev[lin][col] = ' ';
	}
}

void compMat(int lin,int col) { //função recursiva que compara a matriz que o usuario ve com a matriz já aberta
	if (matA[lin][col] == ' ') {
		return;
	}
	else {
		if (matRev[lin][col] == ' ') {
			matA[lin][col] = ' ';

			if (lin != 0) {
				compMat(lin - 1, col);
				if (col != 0) {
					compMat(lin - 1, col - 1);
				}
				if (col != 9) {
					compMat(lin - 1, col + 1);
				}
			}
			if (col != 0) {
				compMat(lin, col - 1);
			}			
			if (col != 9) {
				compMat(lin, col + 1);
			}
			if (lin != 9) {
				if (col != 0) {
					compMat(lin + 1, col - 1);
				}
				compMat(lin + 1, col);
				if (col != 9) {
					compMat(lin + 1, col + 1);
				}
			}
		}
		else {
			matA[lin][col] = matRev[lin][col];
		}
	}
}

int verifmat(int li, int cl) { //verifica a casa que o usuario escolheu
	if (matA[li][cl] == 'B') {
		printf("\n\n            GAME OVER\n        Bomba selecionada \n\n");
		printf("   0  1  2  3  4  5  6  7  8  9 \n"); //mostra a matriz com as bombas se o usuario perdeu o jogo 
		for (int l = 0; l < tm; l++) {
			printf("%d  ", l);
			for (int c = 0; c < tm; c++) {
				printf("%c  ", matA[l][c]);
			}
			printf("\n");
		}
		printf("\n");
		system("pause");
		CriaMat();
		menu();
	}
	else if (matA[li][cl] != 'X') {
		printf("\n \n Posição já revelada! \n\n");
		system("pause");
		return 1;
	}
	else {  //se a posição escolhida não é bomba, chama a função recursiva que abre as casa vizinha
			compMat(li, cl);
								//em seguida testa todas as posições da matriz, se o numero de casa fechadas for igual ao numero de bombas o usuario ganhou
								// porem não funciona :(
			int contBomb = 0;
			for (int l = 0; l < tm; l++) {
				for (int c = 0; c < tm; c++) {
					if (matA[l][c] == 'X') {
						contBomb++;
					}
				}
			}
			if (contBomb == qtb) {
				printf("Parabéns você ganhou!!!\n\n");
				system("pause");
			}		
				return 1;			
	}
	
}

void GameLoop() {
	int lin, col;
	do {
		system("cls");
		MmatA();
		puts("");
		Mrev();
		do {
			printf("\nInsira a linha:(0 a 9): ");
			scanf("%d", &lin);
			if (lin < 0 || lin > 9) {
				printf("Posição invalida! \n");
			}
		} while (lin < 0 || lin > 9);
		do {
			printf("Insira a coluna(0 a 9): ");
			scanf("%d", &col);
			if (col < 0 || col > 9){
				printf("Posição invalida! \n\n");
			}
		} while (col < 0 || col > 9);
	} while (verifmat(lin, col) == 1);
}

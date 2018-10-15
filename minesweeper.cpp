//   Project     : [Campo Minado]
//   File        : [minesweeper.cpp]
//   Encoding    : [UTF-8]
//   Description : [Campo Minado]
//   Created On  : [30/09/2018 2:24:07 PM]
//   Created By  : [Eduardo Arndt]

#include<bits/stdc++.h>
using namespace std;

//CAMPO!
#define maxLados 50 //TAMANHO MAXIMO DO CAMPO
#define maxMinas 200 //NUMERO MAXIMO DE MINAS
//#define espacos 526 // NUMERO DE ESPACOS PARA JOGAR SEM BOMBA (25 * 25 - 99)

//VARS
int lado;  //TAMANHO DO CAMPO
int qt_minas;  //NUMERO DE MINAS

char campo[maxLados][maxLados]; //tamanho maximo de 50x50
bool revelados[maxLados][maxLados]; //matriz que guarda pos reveladas
int  bombas[200][1]; //200 linhas, 2 colunas

//FUNCOES

void campoPrint();
void criarCampo();
void colocarBombas();
void hack();
void controle();
void dificuldade();
void jogar();
void revelar(int lin, int col);
bool posValida();
bool posBomba();
bool gameOver(int lin, int col);
int contarBombas(int lin, int col);

int main(){
    controle();
    return 1337; // #LEET
}

void dificuldade(){
    int dificuldade = 0;
    printf("Escolha a dificuldade do jogo.\n");
    printf("Para FACIL: 1.\nPara MEDIO: 2.\nPara DIFICIL: 3.\n");
    printf("Digite: ");
    scanf(" %d", &dificuldade);

    while ((dificuldade != 1)&&(dificuldade != 2)&&(dificuldade != 3)){
        printf("\nComando invalido. Digite novamente.\n");
        printf("Para FACIL: 1.\nPara MEDIO: 2.\nPara DIFICIL: 3.\n");
        printf("Digite: ");
        scanf(" %d", &dificuldade);
    }

    if (dificuldade == 1){
        lado = 10;
        qt_minas = 10;
    }
    if (dificuldade == 2){
        lado = 20;
        qt_minas = 80;
    }
    if (dificuldade == 3){
        lado = 30;
        qt_minas = 180;
    }
}

bool posValida(int lin, int col){
    if ((lin >= 0) && (lin < lado) && (col >= 0) && (col < lado)){
        return true;
    } else {
        return false;
    }
}

bool posBomba(int lin, int col){
    if (campo[lin][col] == 'X'){
        return true;
    } else {
        return false;
    }
}

void criarCampo(){
    int i, j;
    for (i=0; i<lado; i++){
        for (j=0; j<lado; j++){
            campo[i][j] = '-';
            revelados[i][j] = false;
        }
    }
    return;
}

void colocarBombas(){
    int i, j;
    int x, y;

    //Bombas[][] é uma matriz que contém as coordenadas de todas as bombas do campo;
    //São duas colunas, e quantidade de linhas = quantidade de bombas;

    //Pode ser que não fique exatamente a quantidade de bombas definidade, pois pode cair na mesma posicao mais de uma vez

    srand(time(NULL));
    for (i=0; i<qt_minas; i++){
        int random = rand() %(lado*lado);
		int x = random / lado;
		int y = random % lado;

        bombas[i][0] = x;
        bombas[i][1] = y;

        campo[bombas[i][0]][bombas[i][1]] = 'X';
    }
    return;
}

void campoPrint(){
    int i, j;
	printf("\nCampo:\n\n  ");
    for (i=0; i<lado; i++){
        printf("%d ", i);
    }
    printf("\n");

    for (i=0; i<lado; i++){
        printf("%d ", i);
        for (j=0; j<lado; j++){
            if (campo[i][j] == 'X'){
                printf("%c ", '-');
            } else {
            printf("%c ", campo[i][j]);
            }
        }
        printf("\n");
    }
    return;
}

void hack(){
    int i, j;
    printf("\nEh feio usar cheats...\n");
	printf("\nCampo:\n\n  ");
    for (i=0; i<lado; i++){
        printf("%d ", i);
    }
    printf("\n");

    for (i=0; i<lado; i++){
        printf("%d ", i);
        for (j=0; j<lado; j++){
            printf("%c ", campo[i][j]);
        }
        printf("\n");
    }
    return;
}

void msgInicio(){
    puts("");     
    puts("      .--.                               .-..-. _                 .-.      "); 
    puts("     | .--'                              | `' ||_;                | |      "); 
    puts("     | |    .--.  ,-.,-.,-..---.  .--.   | .. |.-.,-.,-. .--.   .-' | .--. "); 
    puts("     | |__ ' .; ; | ,. ,. || .; `' .; |  | |; || || ,. |' .; ; ' .; |' .; |"); 
    puts("     `.__.'`.__,_;|_;|_;|_;| ._.'`.__.'  |_;|_;|_;|_;|_;`.__,_;`.__.'`.__.'"); 
    puts("                           | |                                             ");      
    puts("                           |_;                                             ");
    puts("\n\nDesenvolvido por Eduardo Arndt.\n\n");
    puts("Tecle ENTER para comecar.");
    getchar();
    system("cls");
}

void controle(){
    msgInicio();
    dificuldade();
    criarCampo();
    colocarBombas();
    jogar();
}

void jogar(){
    int lin, col;
    int i, j;
    char cont;
    bool isOver = false;

    while (isOver == false){

        //campoPrint();
        hack();

        printf("\nSelecione a linha: ");
        scanf(" %d", &lin);
        printf("\nSelecione a coluna: ");
        scanf(" %d", &col);

        isOver = gameOver(lin, col);
        if (isOver == true){
            printf("\nGame Over!\n");
            hack();
            return;
        }

        //revelar(lin, col);

        cont = '0';

        if ((posValida(lin+1, col) == true) && (posBomba(lin+1, col) == true)){
            cont++;
        }
        if ((posValida(lin, col+1) == true) && (posBomba(lin, col+1) == true)){
            cont++;
        }
        if ((posValida(lin-1, col) == true) && (posBomba(lin-1, col) == true)){
            cont++;
        }
        if ((posValida(lin, col-1) == true) && (posBomba(lin, col-1) == true)){
            cont++;
        }
        if ((posValida(lin+1, col+1) == true) && (posBomba(lin+1, col+1) == true)){
            cont++;
        }
        if ((posValida(lin-1, col-1) == true) && (posBomba(lin-1, col-1) == true)){
            cont++;
        }
        if ((posValida(lin+1, col-1) == true) && (posBomba(lin+1, col-1) == true)){
            cont++;
        }
        if ((posValida(lin-1, col+1) == true) && (posBomba(lin-1, col+1) == true)){
            cont++;
        }
        campo[lin][col] = cont;
        revelados[lin][col] = true;

        if (cont == '0'){
            if (revelados[lin+1][col+1] == false){
                revelar(lin+1,col+1);
            }
            if (revelados[lin+1][col+1] == false){
                revelar(lin-1,col-1);
            }
            if (revelados[lin+1][col+1] == false){
                revelar(lin+1,col);
            }
            if (revelados[lin+1][col+1] == false){
                revelar(lin,col+1);
            }
            if (revelados[lin+1][col+1] == false){
                revelar(lin-1,col);
            }
            if (revelados[lin+1][col+1] == false){
                revelar(lin,col-1);
            }
            if (revelados[lin+1][col+1] == false){
                revelar(lin+1,col-1);
            }
            if (revelados[lin+1][col+1] == false){
                revelar(lin-1,col+1);
            }
        }
    }
    return;
}

void revelar (int lin, int col){
    char cont = '0';

    if (revelados[lin][col] == true){
        return;
    }

    //comentado para n�o crashar

    /* if ((posValida(lin+1, col) == true) && (posBomba(lin+1, col) == true)){
        cont++;
    } 
    if ((posValida(lin, col+1) == true) && (posBomba(lin, col+1) == true)){
        cont++;
    }
    if ((posValida(lin-1, col) == true) && (posBomba(lin-1, col) == true)){
        cont++;
    }
    if ((posValida(lin, col-1) == true) && (posBomba(lin, col-1) == true)){
        cont++;
    }
    if ((posValida(lin+1, col+1) == true) && (posBomba(lin+1, col+1) == true)){
        cont++;
    }
    if ((posValida(lin-1, col-1) == true) && (posBomba(lin-1, col-1) == true)){
        cont++;
    }
    if ((posValida(lin+1, col-1) == true) && (posBomba(lin+1, col-1) == true)){
        cont++;
    }
    if ((posValida(lin-1, col+1) == true) && (posBomba(lin-1, col+1) == true)){
        cont++;
    } */

    campo[lin][col] = cont;

    if (cont == '0'){
        if ((posValida(lin+1, col) == true) && (posBomba(lin+1, col) == false)){
            revelar(lin+1, col);
        }
        if ((posValida(lin, col+1) == true) && (posBomba(lin, col+1) == false)){
            revelar(lin, col+1);
        }
        if ((posValida(lin-1, col) == true) && (posBomba(lin-1, col) == false)){
            revelar(lin-1, col);
        }
        if ((posValida(lin, col-1) == true) && (posBomba(lin, col-1) == false)){
            revelar(lin, col-1);
        }
        if ((posValida(lin+1, col+1) == true) && (posBomba(lin+1, col+1) == false)){
            revelar(lin+1, col+1);
        }
        if ((posValida(lin-1, col-1) == true) && (posBomba(lin-1, col-1) == false)){
            revelar(lin-1, col-1);
        }
        if ((posValida(lin+1, col-1) == true) && (posBomba(lin+1, col-1) == false)){
            revelar(lin+1, col-1);
        }
        if ((posValida(lin-1, col+1) == true) && (posBomba(lin-1, col+1) == false)){
            revelar(lin-1, col+1);
        }
    }
    return;
}

bool gameOver(int lin, int col){
    if (campo[lin][col] == 'X'){
        return true;
    } else {
        return false;
    }
}

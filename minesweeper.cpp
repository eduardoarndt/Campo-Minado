//   Project     : [Campo Minado]
//   File        : [campo_minado_earndt.cpp]
//   Description :
//      [TODO: Write the purpose of ... ]
//
//   Created On: 30/09/2018 2:24:07 PM
//   Created By: [Eduardo Arndt] <mailto:[eduardo-arndt@hotmnail.com]>

//CAMPO MINADO - FACCAT

/* PROGRAM START! */

//INCLUIR TODAS BIBLIOTECAS BASICAS DE UMA VEZ
//https://www.geeksforgeeks.org/bitsstdc-h-c/
#include<bits/stdc++.h>
using namespace std;

//DIFICULDADE!
#define FACIL 0
#define MEDIO 1
#define DIFICIL 2

//CAMPO!
#define maxLados 25 //TAMANHO MAXIMO DO CAMPO
#define maxMinas 99 //TAMANHO MAXIMO DE MINAS
#define espacos 526 // NUMERO DE ESPACOS PARA JOGAR SEM BOMBA (25 * 25 - 99)

//VARS
int lado;  //TAMANHO DO CAMPO
int qt_minas;  //NUMERO DE MINAS

//FUNCOES

bool posValida();
bool posBomba();
void campoPrint();
void criarCampo();
void colocarBombas();
void hack();
void iniciar();
void dificuldade();

int main(){
    iniciar();
    dificuldade();
    return 1337; // #LEET
}
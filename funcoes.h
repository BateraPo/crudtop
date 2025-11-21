#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define cadastro "alunos.dat"
#define MAX 1000

#define COR_RESET     "\x1b[0m"
#define COR_VERMELHO  "\x1b[31m"
#define COR_VERDE     "\x1b[32m"
#define COR_AMARELO   "\x1b[33m"
#define COR_AZUL      "\x1b[34m"
#define COR_MAGENTA   "\x1b[35m"
#define COR_CIANO     "\x1b[36m"


typedef struct
{
    int id;
    char nome[100];
    char curso[50];
    char CPF[15];
    int idade;
    float nota1;
    float nota2;
    char status;
    
}Aluno;

void cadastrarAluno();
void listarAluno();
void alterarAluno();
void removerAluno();
void lancarNotas();
void buscarAlunoPorNome();
void listarAlunoOrdenado();
void listarAlunoOrdenadoID();
void buscarAlunoPorID();
void gerarRelatorioMedias();
void limparBuffer();
void buscaPorCurso();
int gerarProximoID();

#endif

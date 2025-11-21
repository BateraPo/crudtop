#include "funcoes.h"
#include <windows.h>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004

void ativarCoresANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return;
    }
}
 
void exibirMenu(){
        printf(COR_CIANO"\n----Sistema de Gestao de Alunos ----\n"COR_RESET);
        printf(COR_AMARELO"\n(1) - Cadastrar Aluno\n");
        printf("\n(2) - Listar Alunos...\n");
        printf("\n(3) - Consultar Aluno...\n");
        printf("\n(4) - Alterar Dados...\n");
        printf("\n(5) - Relatorios\n");
        printf("\n(6) - Remover Aluno\n"COR_RESET);
        printf(COR_VERMELHO"\n(0) - Sair\n"COR_RESET);
        printf("\n------------------------------------------------\n");
        printf(COR_VERDE"\nDigite sua opcao: "COR_RESET);
}

void menuConsultar() {

    int opcao;
    do {
        printf(COR_CIANO"\n----- Consultar Aluno -----\n"COR_RESET);
        printf(COR_AMARELO"\n(1) - Buscar por ID\n");
        printf("\n(2) - Buscar por Nome\n");
        printf("\n(0) - Voltar ao Menu Principal\n"COR_RESET);
        printf("\n------------------------------------------------\n");
        printf(COR_VERDE"\nDigite sua opcao: "COR_RESET);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                buscarAlunoPorID();
                break;
            case 2:
                buscarAlunoPorNome();
                break;
            case 0:
                printf(COR_VERDE"\nVoltando ao menu principal...\n"COR_RESET);
                break;
            default:
                printf(COR_VERMELHO"\nOpcao invalida! Tente novamente.\n"COR_RESET);
                break;
        }
    } while (opcao != 0);
}

void menuAlterar() {
    int opcao;
    do {
        printf(COR_CIANO"\n----- Alterar Dados -----\n"COR_RESET);
        printf(COR_AMARELO"\n(1) - Alterar Dados (Nome, Curso, etc.)\n");
        printf("\n(2) - Lançar Notas  |  Alterar Notas\n");
        printf("\n(0) - Voltar ao Menu Principal\n"COR_RESET);\
        printf("\n------------------------------------------------\n");
        printf(COR_VERDE"\nDigite sua opcao: "COR_RESET);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                alterarAluno();
                break;
            case 2:
                lancarNotas();
                break;
            case 0:
                printf(COR_VERDE"\nVoltando ao menu principal...\n"COR_RESET);
                break;
            default:
                printf(COR_VERMELHO"\nOpcao invalida! Tente novamente.\n"COR_RESET);
                break;
        }
    } while (opcao != 0);
}

void listarAlunoMenu() {
    int opcao;
    do {
        printf(COR_CIANO"\n----- Listar Alunos -----\n"COR_RESET);
        printf(COR_AMARELO"\n(1) - Listar Alunos(Ordenado por Cadastro)\n");
        printf("\n(2) - Listar Alunos(Ordenado por nome)\n");
        printf("\n(3) - Listar Alunos(Ordenado por ID)\n");
        printf("\n(4) - Listar Alunos por Curso\n");
        printf("\n(0) - Voltar ao Menu Principal\n"COR_RESET);
        printf("\n------------------------------------------------\n");
        printf(COR_VERDE"\nDigite sua opcao: "COR_RESET);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                listarAluno();
                break;
            case 2:
                listarAlunoOrdenado();
                break;
            case 3:
                listarAlunoOrdenadoID();
                break;
            case 4:
                buscaPorCurso();
                break;
            case 0:
                printf(COR_VERDE"\nVoltando ao menu principal...\n"COR_RESET);
                break;
            default:
                printf(COR_VERMELHO"\nOpcao invalida! Tente novamente.\n"COR_RESET);
                break;
        }
    } while (opcao != 0);
}

int main(){

    ativarCoresANSI();

    int tipo = 99;

    do{

        exibirMenu();
        scanf("%d", &tipo);
        limparBuffer();

        switch (tipo)
        {
        case 1:
        cadastrarAluno();
        break;

        case 2:
        listarAlunoMenu();
        break;
        
        case 3:
        menuConsultar();
        break;

        case 4:
        menuAlterar();
        break;

        case 5:
        gerarRelatorioMedias();
        break;

        case 6:
        removerAluno();
        break;

        case 0:
        printf(COR_VERDE"\nEncerrando o sistema. Ate mais!!\n"COR_RESET);
        break;

        default:
        printf(COR_VERMELHO"\nOpcao invalida! Tente novamente.\n"COR_RESET);
        break;
    }
} while(tipo != 0);
return 0;
}
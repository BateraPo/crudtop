#include "funcoes.h"


// limpa as quebra de linha
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



//1
void cadastrarAluno(){
    
    FILE *registro;
    //pro switch case
    int opcao = 100;
    int cpfValido = 0;
    int i;

    registro = fopen(cadastro, "ab");



    // verifica erro krl
    if(registro == NULL){
        perror(COR_VERMELHO"Erro ao abrir o arquivo."COR_RESET);
        return;
    }



    Aluno A;



    printf(COR_CIANO"\n---- Cadastro de Novo Aluno ----\n"COR_RESET);
    A.id = gerarProximoID();
    printf(COR_VERDE"\n-----------ID: %d-----------\n"COR_RESET, A.id);
    
   



    printf(COR_MAGENTA"\nDigite o nome: \n"COR_RESET);
    fgets(A.nome, 100, stdin);
    A.nome[strcspn(A.nome, "\n")] = 0;



    do {
        printf(COR_MAGENTA"\nDigite o CPF (apenas os 11 numeros): "COR_RESET);
        fgets(A.CPF, 15, stdin); //LE O CPF
        A.CPF[strcspn(A.CPF, "\n")] = 0;


        //vai validar o tamanho do cpf se tem 11 mesmo
        if (strlen(A.CPF) != 11) {
            printf(COR_VERMELHO"O CPF deve ter exatamente 11 digitos.\n"COR_RESET);
            continue;
        }

        // ve se tem so numro tbm
        int apenasNumeros = 1; // comeca verdadeiro e se tiver algo alem de numero fica falso
        for (i = 0; i < 11; i++) {
            if (!isdigit(A.CPF[i])) { //procura se tem so numero
                apenasNumeros = 0;
                break;
            }
        }

        if (apenasNumeros) {
            cpfValido = 1; // libera do loop
        } else {
            printf(COR_VERMELHO"O CPF deve conter apenas numeros.\n"COR_RESET);
        }

    } while (!cpfValido); // repete enquanto cpfValido for falso



    printf(COR_MAGENTA"\nDigite a idade: \n"COR_RESET);
    scanf("%d", &A.idade);



    printf(COR_AZUL"\nQual curso o aluno esta sendo cadastrado?\n"COR_RESET);
    printf(COR_AMARELO"\n1 - ADS \n");
    printf("\n2 - MECANICA \n");
    printf("\n3 - COMPUTACAO BASICA \n");
    printf("\n4 - DESIGN GRAFICO \n");
    printf("\n5 - DRONE \n");
    printf("\n6 - CULINARIA \n"COR_RESET);
    printf(COR_VERMELHO"\n0 - SAIR \n"COR_RESET);
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao)
    {
    case 1:
        strcpy(A.curso, "ADS");
        break;
    case 2:
        strcpy(A.curso, "MECANICA");
        break;
    case 3:
        strcpy(A.curso, "COMPUTACAO BASICA");
        break;
    case 4:
        strcpy(A.curso, "DESIGN GRAFICO");
        break;
    case 5:
        strcpy(A.curso, "DRONE");
        break;
    case 6:
        strcpy(A.curso, "Culinaria");
        break;
    case 0:
        break;
    default:
        strcpy(A.curso, "Nao definido");
        break;
    }

    A.nota1 = 0;
    A.nota2 = 0;
    A.status = 'P';


    //escreve na file BINARIO
    fwrite(&A, sizeof(Aluno), 1, registro);



    fclose(registro);



    printf(COR_VERDE"\nAluno cadastrado com sucesso!\n"COR_RESET);
    system("pause");


}

//2
void listarAluno(){

    FILE *registro;

    // r read // rb read binario
    registro = fopen(cadastro, "rb");




    //verifica se tem aluno ai
    if (registro == NULL) {
        printf(COR_VERMELHO"\nNenhum aluno cadastrado ainda.\n"COR_RESET);
        return;
    }
    Aluno A;


    // loop pra ler e printar
    printf(COR_CIANO"\n---------------------Dados do Aluno---------------------\n"COR_RESET);
    
    while(fread(&A, sizeof(Aluno), 1, registro) == 1){
        printf(COR_MAGENTA"\nID: %d\n", A.id);
        printf("\nNome: %s\n", A.nome);
        printf("\nCurso: %s\n", A.curso);
        printf("\nNota 1: %.2f\n", A.nota1);
        printf("\nNota 2: %.2f\n", A.nota2);
        printf("\nStatus: %c\n"COR_RESET, A.status);
        printf("\n--------------------------------------------------------------------------------------------");
    }



    fclose(registro);
    system("pause");
}

//3
void alterarAluno(){
    
    // registro temporario para mudar
    FILE *tempRegistro;
    FILE *registro;
    Aluno A;



    //id de pesquisa e ponto para ver se encontrou o id
    int idAltera, encontro = 0;




    // arquivo temporario
    char tempNome[] = "temp.dat";

    registro = fopen(cadastro, "rb");
    
    while(fread(&A, sizeof(Aluno), 1, registro) == 1){
        printf("\nID: %d  |  Nome: %s  |  Curso: %s\n", A.id, A.nome,A.curso);
    }

    fclose(registro);
    
    
    //r read | w write // rb read binary, wb write binario
    registro = fopen(cadastro, "rb");

    

    tempRegistro = fopen(tempNome, "wb");


    printf(COR_MAGENTA"\nDigite o ID do aluno que deseja alterar: "COR_RESET);
    scanf("%d", &idAltera);
    limparBuffer();






    //verifica se ta tudo certo ai fi
    if (registro == NULL || tempRegistro == NULL) {
        printf(COR_VERMELHO"\nErro ao abrir os arquivos.\n"COR_RESET);
        return;
    }



    // loop pra ler e mudar os dados
    while((fread(&A, sizeof(Aluno), 1, registro) == 1)){
        if (A.id == idAltera){
            encontro = 1;
            int opcao = 100;
            printf(COR_CIANO"\n----Alterando Aluno: %s ----\n"COR_RESET, A.nome);
            printf(COR_MAGENTA"\nDigite o novo nome: "COR_RESET);
            fgets(A.nome, 100, stdin);
            A.nome[strcspn(A.nome, "\n")] = 0;

            printf(COR_MAGENTA"\nDigite o CPF: \n"COR_RESET);
            fgets(A.CPF, 100, stdin);
            A.CPF[strcspn(A.CPF, "\n")] = 0;

            printf(COR_MAGENTA"\nDigite a idade: \n"COR_RESET);
            scanf("%d", &A.idade);

            printf("\nEscolha o novo Curso: \n");
            printf(COR_AMARELO"\n1 - ADS \n");
            printf("\n2 - MECANICA \n");
            printf("\n3 - COMPUTACAO BASICA \n");
            printf("\n4 - DESIGN GRAFICO \n");
            printf("\n5 - DRONE \n");
            printf("\n6 - CULINARIA \n"COR_RESET);
            printf("\n0 - SAIR \n");
            scanf("%d", &opcao);
            limparBuffer();

            switch (opcao)
            {
            case 1:
                strcpy(A.curso, "ADS");
                break;
            case 2:
                strcpy(A.curso, "MECANICA");
                break;
            case 3:
                strcpy(A.curso, "COMPUTACAO BASICA");
                break;
            case 4:
                strcpy(A.curso, "DESIGN GRAFICO");
                break;
            case 5:
                strcpy(A.curso, "DRONE");
                break;
            case 6:
                strcpy(A.curso, "Culinaria");
                break;
            case 0:
                break;
            default:
                strcpy(A.curso, "Nao definido");
                break;
            }
            printf(COR_AZUL"\nDigite a nova Nota 1: ");
            scanf("%f", &A.nota1);
            limparBuffer();

            printf("\nDigite a nova Nota 2: "COR_RESET);
            scanf("%f", &A.nota2);
            limparBuffer();

            float media = (A.nota1 + A.nota2) / 2;
            if(media >= 7.0){
                A.status = 'A';
            } else{
                A.status = 'R';
            }
            printf(COR_VERDE"\nDados alterados com sucesso! \n"COR_RESET);
        }
    

        // regrava no arquivo temp
        fwrite(&A, sizeof(Aluno), 1, tempRegistro);
    }



    fclose(registro);
    fclose(tempRegistro);


    // renomeia o arqauivo modificado
    if (encontro){
        remove(cadastro);
        rename(tempNome, cadastro);
    } else {
        printf(COR_VERMELHO"\nAluno com ID %d nao encontrado.\n"COR_RESET, idAltera);
        remove(tempNome);
    }
    system("pause");
}

//4
void removerAluno(){

    //mema coisa do de cima
    FILE *tempRegistro;
    FILE *registro;
    Aluno A;
    int idRemove, encontro = 0;
    char tempNome[] = "temp.dat";

    // listar os id antes de qualquer coisa
    registro = fopen(cadastro, "rb");

    if(registro == NULL){
        printf(COR_VERMELHO"\nArquivo de dados não encontrado.\n"COR_RESET);
        return;
    }
    
        printf("\n------ Alunos Atuais ------\n");
        while(fread(&A, sizeof(Aluno), 1, registro) == 1){
        printf("\nID: %d  |  Nome: %s  |  Curso: %s\n", A.id, A.nome,A.curso);
    }

    fclose(registro);

    
    
    printf(COR_AMARELO"\nDigite o ID do aluno que deseja remover: "COR_RESET);
    scanf("%d", &idRemove);
    limparBuffer();
    
    registro = fopen(cadastro, "rb");
    tempRegistro = fopen(tempNome, "wb");


    if(registro == NULL){
        printf(COR_VERMELHO"\nArquivo de dados não encontrado.\n"COR_RESET);
        if(tempRegistro) fclose(tempRegistro);
        remove(tempNome);
        return;
    }
    if(tempRegistro == NULL){
        printf(COR_VERMELHO"\nErro ao criar arquivo temporario.\n"COR_RESET);
        fclose(registro);
        return;
    }


    //caca o ID que pediu pra remover, caso ache, nao copia para o arquivo (o else faz a copia pra dentro ali)
    while((fread(&A, sizeof(Aluno), 1, registro) == 1)){
        if(A.id == idRemove){
            encontro = 1;
            printf(COR_VERDE"\nAluno %s (ID %d) removido com sucesso!.\n"COR_RESET,A.nome, A.id);
        } else {
            // copia a linha que ta passando pro temp
            fwrite(&A, sizeof(Aluno), 1, tempRegistro);
        }

    }
        fclose(registro);
        fclose(tempRegistro);

        // sobreescreve o arquivo principal com o temporario criado


        if(encontro){
            remove(cadastro);
            rename(tempNome, cadastro);
        }   else {
            printf(COR_VERMELHO"\nAluno com ID %d nao encontrado.\n"COR_RESET, idRemove);
            remove(tempNome);
        }
        system("pause");
}

//5 mudar
void gerarRelatorioMedias(){
//         Aluno A;
//         FILE *registro;

//         float somaMediasTurma = 0;
//         int totalAlunos = 0;

//     registro = fopen(cadastro, "rb");
//     if(registro == NULL){
//         printf(COR_VERMELHO"\nNenhum aluno cadastrado para gerar relatorio.\n"COR_RESET);
//         return;
//     }

//     printf(COR_CIANO"\n-----Relatorio de Medias dos Alunos-----\n"COR_RESET);
//     // escaneia os alunos e printa na tela os dados, adiciona as medias na variavel soma, e adiciona um aluno pra calcular a media da turma depois
//     while((fread(&A, sizeof(Aluno), 1, registro) == 1)){
//         float mediaAluno = (A.nota1 + A.nota2 ) / 2;
//         printf(COR_MAGENTA"\nID: %d | Nome: %s | Media: %.2f | Status: %c\n"COR_RESET, A.id, A.nome, mediaAluno, A.status);


//         somaMediasTurma += mediaAluno;
//         totalAlunos++;
//     }

//     fclose(registro);


//     //calcula a media da turma e printa
//     if(totalAlunos > 0){
//         float mediaTurma = somaMediasTurma / totalAlunos;
//         printf("\n----------------------------------------\n");
//         printf(COR_MAGENTA"\nTotal de Alunos: %d\n", totalAlunos);
//         printf("\nMédia Geral da Turma: %.2f\n"COR_RESET, mediaTurma);
//         printf("\n----------------------------------------\n");
//     }else printf(COR_VERMELHO"\nNenhum aluno cadastrado.\n"COR_RESET);

//         system("pause");
}

//6
void lancarNotas(){

        FILE *registro;
        FILE *tempRegistro;
        Aluno A;
        int idBusca, encontro = 0;
        char tempNome[] = "temp.dat";

        
        registro = fopen(cadastro, "rb");
        
        while(fread(&A, sizeof(Aluno), 1, registro) == 1){
            printf(COR_AZUL"\nID: %d  |  Nome: %s  |  Curso: %s\n"COR_RESET, A.id, A.nome,A.curso);
        }

        fclose(registro);
            

        printf(COR_CIANO"\n---- Lancamento de Notas ----\n"COR_RESET);
        printf(COR_VERDE"\nDigite o ID do aluno para lançar as notas: "COR_RESET);
        scanf("%d", &idBusca);
        limparBuffer();
        
        registro = fopen(cadastro, "rb");
        tempRegistro = fopen(tempNome, "wb");


        if(registro == NULL || tempRegistro == NULL){
            printf(COR_VERMELHO"\nErro ao abrir os arquivos.\n"COR_RESET);
            if (registro) fclose(registro);
            if(tempRegistro) fclose(tempRegistro);
            return;
        }


        //acha o id que pediu e lanca as notas, recalcula as medias tambem para Aprovado ou Reprovado
        while((fread(&A, sizeof(Aluno), 1, registro) == 1)){

            if(A.id == idBusca){
                encontro = 1;
                printf(COR_CIANO"\nAluno encontrado: %s\n"COR_RESET, A.nome);
                printf(COR_MAGENTA"\nNota 1: %.2f  |  Nota 2: %.2f \n"COR_RESET, A.nota1, A.nota2);

                printf(COR_MAGENTA"\nDigite a nova Nota 1: "COR_RESET);
                scanf("%f", &A.nota1);
                limparBuffer();


                printf(COR_MAGENTA"\nDigite a nova Nota 2: "COR_RESET);
                scanf("%f", &A.nota2);
                limparBuffer();

                float media = (A.nota1 + A.nota2) / 2;
                
                if(media >= 7.0){
                    A.status = 'A';
                } else{
                    A.status = 'R';
                }
                printf(COR_VERDE"\nNotas atualizadas com sucesso! Novo status: %c\n"COR_RESET, A.status);
                
            }

            

            //grava os dados no arquivo temp
            fwrite(&A, sizeof(Aluno), 1, tempRegistro);


        }
        fclose(registro);
        fclose(tempRegistro);


        //sobrepoe o arquivo antigo com o novo
        if(encontro){
            remove(cadastro);
            rename(tempNome, cadastro);
        } else {
            printf(COR_VERMELHO"\nAluno com ID %d nao foi encontrado.\n"COR_RESET, idBusca);
            remove(tempNome);
        }
        system("pause");
}

//7
void buscarAlunoPorID(){
    FILE *registro;
    Aluno A;
    int idBusca;
    int encontro = 0;

    printf(COR_MAGENTA"\nDigite o ID do aluno que deseja buscar: "COR_RESET);
    scanf("%d", &idBusca);
    limparBuffer();

    registro = fopen(cadastro, "rb");
    if(registro == NULL){
        printf(COR_VERMELHO"\nErro ao abrir o arquivo.\n"COR_RESET);
        return;
    }


    //busca e da print no id solicitado aaaaaaaaaaaaaaaaaaaaa
    while((fread(&A, sizeof(Aluno), 1, registro) == 1)){

        if(A.id == idBusca){
            printf(COR_CIANO"\n----- Aluno encontrado -----\n"COR_RESET);
            printf(COR_MAGENTA"\n ID: %d \n Nome: %s \n Curso: %s \n CPF: %s\n Idade: %d\n N1: %.2f \n N2: %.2f \n Status: %c\n"COR_RESET,A.id, A.nome, A.curso,A.CPF,A.idade, A.nota1, A.nota2, A.status);
            encontro = 1;
            break;
        }
    }

        fclose(registro);

        // se nao encontrou da erro
        if(!encontro){
            printf(COR_VERMELHO"\nAluno com ID %d nao encontrado.\n"COR_RESET, idBusca);
        }

        system("pause");
}

//8
void buscarAlunoPorNome() {
    FILE *registro;
    Aluno A;
    char nomeBusca[100];
    int encontrou = 0;

    printf(COR_CIANO"\n--- Busca por Nome ---\n"COR_RESET);
    printf(COR_MAGENTA"\nDigite o nome (ou parte do nome) do aluno: "COR_RESET);
    fgets(nomeBusca, 100, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    registro = fopen(cadastro, "rb");
    if (registro == NULL) {
        printf(COR_VERMELHO"\nArquivo de dados não encontrado.\n"COR_RESET);
        return;
    }

    printf(COR_CIANO"\n----- Alunos Encontrados -----\n"COR_RESET);
    
    while((fread(&A, sizeof(Aluno), 1, registro) == 1)){
        
        //strstr ve se o nome que pediu ta em A.nome, nao precisa ser exato
        if (strstr(A.nome, nomeBusca) != NULL) {
            printf(COR_MAGENTA"\n ID: %d \n Nome: %s \n Curso: %s \n CPF: %s\n Idade: %d\n N1: %.2f \n N2: %.2f \n Status: %c\n"COR_RESET,A.id, A.nome, A.curso,A.CPF,A.idade, A.nota1, A.nota2, A.status);
            encontrou = 1;
        }
    }
    

    fclose(registro);


    if (!encontrou) {
        printf(COR_VERMELHO"\nNenhum aluno encontrado com o nome '%s'.\n" COR_RESET, nomeBusca);
    }
}

//9
void listarAlunoOrdenado(){
    FILE *registro;
    Aluno lista[MAX]; //vetor pra guardar alunois
    Aluno temp; // struct para troca 


    Aluno A;

    int totalAlunos = 0;
    int i, j;

    registro = fopen(cadastro, "rb");

    if(registro == NULL){
        printf(COR_VERMELHO"\nNenhum aluno cadastrado ainda.\n"COR_RESET);
        return;
    }

    while(totalAlunos < MAX && fread(&lista[totalAlunos], sizeof(Aluno), 1, registro) == 1) {
        totalAlunos++;
    }
    fclose(registro);

    if (totalAlunos == 0) {
        printf(COR_VERMELHO"\nNenhum aluno para ordenar.\n"COR_RESET);
        return;
    }
    
    for (i = 0; i < totalAlunos - 1; i++) {
        for (j = 0; j < totalAlunos - 1 - i; j++) {
            
            // se o nome j vem depoiis do j+1 no alfabeto
            if (strcmp(lista[j].nome, lista[j+1].nome) > 0) {
                // troca eles de lugar
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    printf(COR_CIANO"\n----- Lista de Alunos (Ordenada por Nome) -----\n"COR_RESET);
    for (i = 0; i < totalAlunos; i++) {
        printf(COR_MAGENTA"\n ID: %d \n Nome: %s \n Curso: %s \n CPF: %s \n Idade: %d\n N1: %.2f \n N2: %.2f \n Status: %c\n"COR_RESET, lista[i].id, lista[i].nome, lista[i].curso, lista[i].CPF, lista[i].idade, lista[i].nota1, lista[i].nota2, lista[i].status);
        printf("\n------------------------------------------------------\n");
    }

    system("pause");
}

//10
void listarAlunoOrdenadoID(){
     FILE *registro;
    Aluno lista[MAX]; //vetor pra guardar alunois
    Aluno temp; // struct para troca 

    Aluno A;

    int totalAlunos = 0;
    int i, j;

    registro = fopen(cadastro, "rb");

    if(registro == NULL){
        printf(COR_VERMELHO"\nNenhum aluno cadastrado ainda.\n"COR_RESET);
        return;
    }

    while(totalAlunos < MAX && fread(&lista[totalAlunos], sizeof(Aluno), 1, registro) == 1) {
        totalAlunos++;
    }
    fclose(registro);

    if (totalAlunos == 0) {
        printf(COR_VERMELHO"\nNenhum aluno para ordenar.\n"COR_RESET);
        return;
    }
    
    for (i = 0; i < totalAlunos - 1; i++) {
        for (j = 0; j < totalAlunos - 1 - i; j++) {
            
            // se o id j vem depoiis do j+1 
            if(lista[j].id > lista[j+1].id) {
                // troca eles de lugar
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

     printf(COR_CIANO"\n----- Lista de Alunos (Ordenada por ID) -----\n"COR_RESET);
    for (i = 0; i < totalAlunos; i++) {
       printf(COR_MAGENTA"\n ID: %d \n Nome: %s \n Curso: %s \n CPF: %s\n Idade: %d\n N1: %.2f \n N2: %.2f \n Status: %c\n"COR_RESET, lista[i].id, lista[i].nome, lista[i].curso, lista[i].CPF, lista[i].idade, lista[i].nota1, lista[i].nota2, lista[i].status);
        printf("\n------------------------------------------------------\n");
    }
    system("pause");
}

//11
int gerarProximoID() {
    FILE *registro;
    registro = fopen(cadastro, "rb");

    if (registro == NULL) {
        return 1;
    }

    int idsOcupados[MAX + 1]; 
    int i;

    for (i = 0; i <= MAX; i++) {
        idsOcupados[i] = 0;
    }

    Aluno A;
    int maiorID = 0;


    while (fread(&A, sizeof(Aluno), 1, registro) == 1) {
        if (A.id > 0 && A.id < MAX) {
            idsOcupados[A.id] = 1; 
        }
        
        if (A.id > maiorID) {
            maiorID = A.id;
        }
    }
    fclose(registro);
    
    for (i = 1; i <= maiorID; i++) {
        if (idsOcupados[i] == 0) {
            return i; 
        }
    }
    return maiorID + 1;
}

//12
void buscaPorCurso(){

    FILE *registro;


    int opcao;
    char busca[50];
    int encontrou = 0;

    printf(COR_CIANO"--------------BUSCA POR CURSO--------------"COR_RESET);

    printf(COR_AZUL"\nQual curso deseja buscar?\n"COR_RESET);
    printf(COR_AMARELO"\n1 - ADS \n");
    printf("\n2 - MECANICA \n");
    printf("\n3 - COMPUTACAO BASICA \n");
    printf("\n4 - DESIGN GRAFICO \n");
    printf("\n5 - DRONE \n");
    printf("\n6 - CULINARIA \n"COR_RESET);
    printf("\n0 - SAIR \n");
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao)
    {
    case 1:
        strcpy(busca, "ADS");
        break;
    case 2:
        strcpy(busca, "MECANICA");
        break;
    case 3:
        strcpy(busca, "COMPUTACAO BASICA");
        break;
    case 4:
        strcpy(busca, "DESIGN GRAFICO");
        break;
    case 5:
        strcpy(busca, "DRONE");
        break;
    case 6:
        strcpy(busca, "Culinaria");
        break;
    case 0:
        break;
    default:
        strcpy(busca, COR_VERMELHO"Curso nao encontrado."COR_RESET);
        break;
        system("pause");
    }

    registro = fopen(cadastro, "rb");

    if (registro == NULL) {
        printf(COR_VERMELHO"\nNenhum aluno cadastrado.\n"COR_RESET);
        return;
    }


    Aluno A;


    while(fread(&A, sizeof(Aluno), 1, registro) == 1) {
        if (strcmp(A.curso, busca) == 0) {
            printf(COR_CIANO"=========================%s========================="COR_RESET, busca);
            printf(COR_MAGENTA"\n ID: %d \n Nome: %s \n N1: %.2f \n N2: %.2f \n Status: %c\n"COR_RESET, A.id,A.nome,A.nota1,A.nota2,A.status);
            encontrou = 1;
        }
    }

    if (!encontrou){
        printf(COR_VERMELHO"\nNenhum aluno encontrado neste curso.\n"COR_RESET);
    }

    system("pause");

}
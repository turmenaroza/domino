#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <time.h>

#define qtdTotalPecas 28

typedef struct {
    int numero1;
    int numero2;
} Peca;

void mostrarPecas(Peca vetPecas[], int tamanhoVetor){
    for(int i = 0; i < tamanhoVetor; i++){
        printf("[%i|%i] ", vetPecas[i].numero1, vetPecas[i].numero2);
    }
}

void embaralhaPecas(Peca vetPecas[]){
    for (int i = (qtdTotalPecas - 1); i > 0; i--) {
        int j = rand() % (i + 1);

        Peca aux = vetPecas[i];
        vetPecas[i] = vetPecas[j];
        vetPecas[j] = aux;
    }
}

void limparTela() {
    #ifdef _WIN32
        system("cls");   // Windows
    #else
        system("clear"); // Linux
    #endif
}

bool possuiPeca(Peca pecas[], int qtdPecas, Peca peca){
    bool possui = false;
    for(int i = 0; i < qtdPecas; i++){
        if((pecas[i].numero1 == peca.numero1 && pecas[i].numero2 == peca.numero2) || (pecas[i].numero1 == peca.numero2 && pecas[i].numero2 == peca.numero1)){
            possui = true;
        }
    }
    return possui;
}

bool inserirPecaMesa(Peca peca, Peca mesa[], int indiceMesaE, int indiceMesaD){
    //if(mesa[indiceMesaE].numero1 == peca.numero1)
}

void jogada(int jogador, Peca monte[], Peca mesa[], Peca pecasJogador[], int qtdPecasMonte, int qtdPecasJog, int indiceMesaE, int indiceMesaD){
    limparTela();
    printf("Vez do Jogador %i", (jogador + 1));
    printf("\nPecas suas: %i", qtdPecasJog);
    printf("\nPecas no monte %i", qtdPecasMonte);
    
    
    char entrada[20];
    int a, b;
    bool sairWhile = false;
    while (!sairWhile)
    {
        printf("\nDigite a peca no formato [0|0] para jogar ou digite 'pecas' para ver suas pecas: ");
        scanf("%19s", entrada);

        if (strcmp(entrada, "pecas") == 0) {
            printf("\n");
            mostrarPecas(pecasJogador, qtdPecasJog);
            printf("\n");
        }
        else if (sscanf(entrada, "[%d|%d]", &a, &b) == 2) {
            
            printf("Primeiro numero: %d\n", a);
            printf("Segundo numero: %d\n", b);
            Peca pecaAdicionada;
            pecaAdicionada.numero1 = a;
            pecaAdicionada.numero2 = b;
            if(possuiPeca(pecasJogador, qtdPecasJog, pecaAdicionada)){
                printf("\n Peca valida.");
                sairWhile = true;
            }else{
                printf("\n Voce nao possui a peca, selecione outra.");
            }
            getchar();
            getchar();
        }
    }
    
}

bool jogoEncerrou(){
    return false;
}

int main(){
    srand((unsigned)time(NULL)); // Usado para aleatoriedade do Rand
    int qtdJogadores = 0;
    int indiceMesaE = 49;
    int indiceMesaD = 50;

    //Construir todas as peças

    Peca pecas[qtdTotalPecas] = {0};
    Peca mesa[100] = {0};

    int aux1 = 0;
    for(int i = 0; i < 7; i++){
        for(int j = i; j < 7;j++){
            Peca novaPeca;
            novaPeca.numero1 = i;
            novaPeca.numero2 = j;
            pecas[aux1] = novaPeca;
            aux1++;
        }
    }

    //Embaralhar
    embaralhaPecas(pecas);

    //Quantidade de jogadores
    printf("=-=-=-=- DOMINO -=-=-=-=");
    printf("\n\n Digite quantos jogadores vao jogar (2 a 4): ");
    scanf("%i", &qtdJogadores);
    while(qtdJogadores  > 4 || qtdJogadores < 2){
        printf("\nNumero invalido! Digite um número entre 2 e 4: ");
        scanf("%i", &qtdJogadores);
    }
    printf("\n\n As pecas estao sendo distribuidas aos %i jogadores...", qtdJogadores);

    //Distribuir as Pecas

    int qtdPecasMonte = qtdTotalPecas - (qtdJogadores * 7);
    Peca *monte = malloc(qtdPecasMonte * sizeof(Peca));
    int qtdPecasJog[4] = {0, 0, 0, 0};
    Peca pecasJog[4][qtdTotalPecas];

    //Distribui para jogadores
    for(int i = 0; i < qtdJogadores; i++){
        qtdPecasJog[i] = 7;
        for(int j = 0; j < 7; j++){
            pecasJog[i][j] = pecas[(j + (i*7))];
        }
        
    }

    //Distribui o resto para o monte
    for(int i = 0; i < qtdPecasMonte; i++){
        monte[i] = pecas[(qtdTotalPecas - qtdPecasMonte) + i];
    }

    // Confirmação
    printf("\n Todos os jogadores possuem 7 pecas. %i pecas estao no monte e podem ser 'compradas'", qtdPecasMonte);
    printf("\nAperte ENTER para comecar");
    getchar();
    getchar();

    //Debug
    limparTela();
    printf("\nTodas as pecas embaralhadas: ");
    mostrarPecas(pecas, 28);
    for(int i = 0; i < qtdJogadores; i++){
        printf("\n%i: ", i);
        mostrarPecas(pecasJog[i], 7);
    }
    printf("\nMonte: ");
    mostrarPecas(monte, qtdPecasMonte);
    limparTela();

    // Jogadas de cada jogador
    
    while (!jogoEncerrou())
    for(int i = 0; i < qtdJogadores; i++){
        jogada(i, monte, mesa, pecasJog[i], qtdPecasMonte, qtdPecasJog[i], indiceMesaE, indiceMesaD);
    }
    
    return 0;
}


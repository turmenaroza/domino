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
    printf("\n\n-----------------------------------------\n\n");
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

// Remove a peça da mão do jogador puxando os elementos para trás
void removerPecaJogador(Peca pecasJogador[], int *qtdPecasJog, Peca pecaRemover) {
    int indiceRemover = -1;
    for (int i = 0; i < *qtdPecasJog; i++) {
        if ((pecasJogador[i].numero1 == pecaRemover.numero1 && pecasJogador[i].numero2 == pecaRemover.numero2) || 
            (pecasJogador[i].numero1 == pecaRemover.numero2 && pecasJogador[i].numero2 == pecaRemover.numero1)) {
            indiceRemover = i;
            break;
        }
    }
    if (indiceRemover != -1) {
        for (int i = indiceRemover; i < (*qtdPecasJog) - 1; i++) {
            pecasJogador[i] = pecasJogador[i + 1];
        }
        (*qtdPecasJog)--;
    }
}

// Insere a peça na mesa validando as extremidades abertas
bool inserirPecaMesa(Peca peca, Peca mesa[], int *indiceMesaE, int *indiceMesaD){
    // Caso a mesa esteja vazia (primeira jogada do jogo)
    if (*indiceMesaE == 49 && *indiceMesaD == 50 && mesa[50].numero1 == -1) {
        mesa[50] = peca;
        *indiceMesaE = 50; 
        *indiceMesaD = 50; 
        return true;
    }

    int valorEsquerda = mesa[*indiceMesaE].numero1; 
    int valorDireita = mesa[*indiceMesaD].numero2;  

    // Tenta encaixar na ponta Esquerda
    if (peca.numero2 == valorEsquerda) {
        (*indiceMesaE)--;
        mesa[*indiceMesaE] = peca;
        return true;
    } else if (peca.numero1 == valorEsquerda) {
        Peca invertida = {peca.numero2, peca.numero1};
        (*indiceMesaE)--;
        mesa[*indiceMesaE] = invertida;
        return true;
    }

    // Tenta encaixar na ponta Direita
    if (peca.numero1 == valorDireita) {
        (*indiceMesaD)++;
        mesa[*indiceMesaD] = peca;
        return true;
    } else if (peca.numero2 == valorDireita) {
        Peca invertida = {peca.numero2, peca.numero1};
        (*indiceMesaD)++;
        mesa[*indiceMesaD] = invertida;
        return true;
    }

    return false;
}

// FUNÇÃO ATUALIZADA: Agora altera a variável pecaInicial por ponteiro para sabermos qual peça ganhou
int definirPrimeiroJogador(Peca pecasJog[4][qtdTotalPecas], int qtdPecasJog[], int qtdJogadores, Peca *pecaInicial) {
    // 1ª Regra: Procura pela maior dupla de [6|6] até [0|0]
    for (int dupla = 6; dupla >= 0; dupla--) {
        Peca buscaDupla = {dupla, dupla};
        for (int i = 0; i < qtdJogadores; i++) {
            if (possuiPeca(pecasJog[i], qtdPecasJog[i], buscaDupla)) {
                *pecaInicial = buscaDupla;
                return i;
            }
        }
    }

    // 2ª Regra: Se nenhum tiver dupla, busca quem tem a maior peça (pela soma dos lados)
    int jogadorMaiorPeca = 0;
    int maiorSoma = -1;
    Peca maiorPecaEncontrada = {-1, -1};

    for (int i = 0; i < qtdJogadores; i++) {
        for (int j = 0; j < qtdPecasJog[i]; j++) {
            int somaAtual = pecasJog[i][j].numero1 + pecasJog[i][j].numero2;
            if (somaAtual > maiorSoma) {
                maiorSoma = somaAtual;
                maiorPecaEncontrada = pecasJog[i][j];
                jogadorMaiorPeca = i;
            }
        }
    }
    *pecaInicial = maiorPecaEncontrada;
    return jogadorMaiorPeca;
}

void jogada(int jogador, Peca monte[], Peca mesa[], Peca pecasJogador[], int *qtdPecasMonte, int *qtdPecasJog, int *indiceMesaE, int *indiceMesaD){
    limparTela();
    printf("=========================================\n");
    printf("             VEZ DO JOGADOR %i           \n", (jogador + 1));
    printf("=========================================\n");
    printf("Suas pecas: %i | Pecas no monte: %i\n\n", *qtdPecasJog, *qtdPecasMonte);
    
    printf("Mesa atual: ");
    if (*indiceMesaE == 49 && *indiceMesaD == 50 && mesa[50].numero1 == -1) {
        printf("[Vazia]\n");
    } else {
        for (int i = *indiceMesaE; i <= *indiceMesaD; i++) {
            printf("[%i|%i] ", mesa[i].numero1, mesa[i].numero2);
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
    
    char entrada[20];
    int a, b;
    bool sairWhile = false;
    while (!sairWhile)
    {
        if (*qtdPecasMonte > 0) {
            printf("\nComandos: '[0|0]' para jogar, 'pecas' para ver a mao, 'comprar' para pegar do monte.\nDigite: ");
        } else {
            printf("\nComandos: '[0|0]' para jogar, 'pecas' para ver a mao, 'passar' para pular a vez (monte vazio).\nDigite: ");
        }
        scanf("%19s", entrada);

        if (strcmp(entrada, "pecas") == 0) {
            printf("\nSua mao: ");
            mostrarPecas(pecasJogador, *qtdPecasJog);
            printf("\n");
        }
        else if (strcmp(entrada, "comprar") == 0) {
            if (*qtdPecasMonte > 0) {
                Peca pecaComprada = monte[*qtdPecasMonte - 1];
                pecasJogador[*qtdPecasJog] = pecaComprada;
                (*qtdPecasJog)++;
                (*qtdPecasMonte)--;
                
                printf("\nVoce comprou a peca [%i|%i]!\n", pecaComprada.numero1, pecaComprada.numero2);
            } else {
                printf("\nO monte esta vazio! Use o comando 'passar' se nao tiver jogadas.\n");
            }
        }
        else if (strcmp(entrada, "passar") == 0) {
            if (*qtdPecasMonte == 0) {
                printf("\nJogador %i passou a vez!\n", (jogador + 1));
                sairWhile = true; 
            } else {
                printf("\nVoce nao pode passar a vez enquanto houver pecas no monte! Digite 'comprar'.\n");
            }
        }
        else if (sscanf(entrada, "[%d|%d]", &a, &b) == 2) {
            Peca pecaAdicionada;
            pecaAdicionada.numero1 = a;
            pecaAdicionada.numero2 = b;
            
            if(possuiPeca(pecasJogador, *qtdPecasJog, pecaAdicionada)){
                if(inserirPecaMesa(pecaAdicionada, mesa, indiceMesaE, indiceMesaD)) {
                    removerPecaJogador(pecasJogador, qtdPecasJog, pecaAdicionada);
                    sairWhile = true; 
                } else {
                    if (*qtdPecasMonte > 0) {
                        printf("\nEssa peca nao encaixa na mesa! Escolha outra ou digite 'comprar'.");
                    } else {
                        printf("\nEssa peca nao encaixa na mesa! Escolha outra ou digite 'passar'.");
                    }
                }
            } else {
                printf("\nVoce nao possui essa peca.");
            }
        }
    }
}

// Verifica se algum dos jogadores zerou a quantidade de peças
bool jogoEncerrou(int qtdPecasJog[], int qtdJogadores){
    for(int i = 0; i < qtdJogadores; i++) {
        if(qtdPecasJog[i] == 0) {
            limparTela();
            printf("\n=================================");
            printf("\nO JOGADOR %i BATEU E VENCEU O JOGO!", i + 1);
            printf("\n=================================\n");
            return true;
        }
    }
    return false;
}

int main(){
    srand((unsigned)time(NULL)); // Usado para aleatoriedade do Rand
    int qtdJogadores = 0;
    int indiceMesaE = 49;
    int indiceMesaD = 50;

    //Construir todas as peças

    Peca pecas[qtdTotalPecas] = {0};
    
    // Inicializa o tabuleiro limpando posições com -1(tava dando erro e inserindo o [0|0] sozinho, acredito que agr foi arrumado)
    Peca mesa[100];
    for(int i = 0; i < 100; i++) {
        mesa[i].numero1 = -1;
        mesa[i].numero2 = -1;
    }

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
    printf("=-=-=-=- DOMINO -=-=-=-=\n");
    printf("Digite quantos jogadores vao jogar (2 a 4): ");
    
    if (scanf(" %i", &qtdJogadores) != 1) {
        qtdJogadores = 2; 
    }
    
    while(qtdJogadores > 4 || qtdJogadores < 2){
        printf("\nNumero invalido! Digite um número entre 2 e 4: ");
        scanf(" %i", &qtdJogadores);
    }

    printf("\nAs pecas estao sendo distribuidas aos %i jogadores...\n", qtdJogadores);

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
    printf("Todos os jogadores possuem 7 pecas. %i pecas estao no monte.\n", qtdPecasMonte);
    
    //  Variável para armazenar qual peça vai iniciar o jogo
    Peca pecaInicial;
    int jogadorVencedor = definirPrimeiroJogador(pecasJog, qtdPecasJog, qtdJogadores, &pecaInicial);
    
    //  Insere a maior peça na mesa automaticamente
    inserirPecaMesa(pecaInicial, mesa, &indiceMesaE, &indiceMesaD);
    
    //  Remove a peça inicial da mão daquele jogador
    removerPecaJogador(pecasJog[jogadorVencedor], &qtdPecasJog[jogadorVencedor], pecaInicial);
    
    limparTela();
    printf("===================================================\n");
    printf(" O Jogador %i tinha a maior peca: [%i|%i]\n", jogadorVencedor + 1, pecaInicial.numero1, pecaInicial.numero2);
    printf(" Ela foi inserida na mesa automaticamente para abrir o jogo!\n");
    printf("===================================================\n\n");
    
    // Define o jogador que realmente vai JOGAR o primeiro turno (o próximo após o vencedor inicial)
    int jogadorAtual = (jogadorVencedor + 1) % qtdJogadores;

    printf("Aperte ENTER para comecar os turnos...");
    while (getchar() != '\n');
    getchar();

    // Jogadas de cada jogador
    while (!jogoEncerrou(qtdPecasJog, qtdJogadores)) {
        jogada(jogadorAtual, monte, mesa, pecasJog[jogadorAtual], &qtdPecasMonte, &qtdPecasJog[jogadorAtual], &indiceMesaE, &indiceMesaD);
        
        if(jogoEncerrou(qtdPecasJog, qtdJogadores)) {
            break;
        }
        
        jogadorAtual = (jogadorAtual + 1) % qtdJogadores;
    }
    
    free(monte);
    return 0;
}
// #include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 2 - Comparação das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de comparação de cartas de cidades. 
// Siga os comentários para implementar cada parte do desafio.

// int main() {
    // Definição das variáveis para armazenar as propriedades das cidades
    // Você pode utilizar o código do primeiro desafio

    
    // Cadastro das Cartas:
    // Implemente a lógica para solicitar ao usuário que insira os dados das cidades
    // utilizando a função scanf para capturar as entradas.
    // utilize o código do primeiro desafio

    // Exemplo:
    // printf("Digite o código da cidade: ");
    // scanf("%s", codigo);
    // 
    // (Repita para cada propriedade)

    // Comparação de Cartas:
    // Desenvolva a lógica de comparação entre duas cartas.
    // Utilize estruturas de decisão como if, if-else para comparar atributos como população, área, PIB, etc.

    // Exemplo:
    // if (populacaoA > populacaoB) {
    //     printf("Cidade 1 tem maior população.\n");
    // } else {
    //     printf("Cidade 2 tem maior população.\n");
    // }

    // Exibição dos Resultados:
    // Após realizar as comparações, exiba os resultados para o usuário.
    // Certifique-se de que o sistema mostre claramente qual carta venceu e com base em qual atributo.

    // Exemplo:
    // printf("A cidade vencedora é: %s\n", cidadeVencedora);

//   return 0;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Struct Territorio
 * Representa um território com nome, cor do exército (dono) e quantidade de tropas.
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
 * Função: limparBuffer
 * Consome o restante da linha do stdin após leituras com scanf quando necessário.
 */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/*
 * Função: cadastrarTerritorios
 * Objetivo: Preencher os 'n' territórios apontados por 'mapa'.
 * Observação: Toda manipulação é feita via ponteiros.
 */
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        Territorio *t = (mapa + i); // uso explícito de ponteiro
        
        printf("\nCadastro do Território %d\n", i + 1);

        printf("Digite o nome do território: ");
        // Permite espaços; limita a 29 chars + '\0'
        scanf(" %29[^\n]", t->nome);

        printf("Digite a cor (dono) do exército: ");
        scanf(" %9[^\n]", t->cor);

        printf("Digite a quantidade de tropas (>= 0): ");
        while (scanf("%d", &t->tropas) != 1 || t->tropas < 0) {
            printf("Valor inválido. Digite um inteiro >= 0: ");
            limparBuffer();
        }
        limparBuffer();
    }
}

/*
 * Função: exibirTerritorios
 * Objetivo: Mostrar todos os territórios.
 */
void exibirTerritorios(const Territorio *mapa, int n) {
    printf("\n===== Estado Atual dos Territórios =====\n");
    for (int i = 0; i < n; i++) {
        const Territorio *t = (mapa + i);
        printf("[%d] Nome: %s | Dono: %s | Tropas: %d\n", i, t->nome, t->cor, t->tropas);
    }
}

/*
 * Função: rolarDado
 * Objetivo: Simular um dado de 6 faces (1..6).
 */
int rolarDado(void) {
    return (rand() % 6) + 1;
}

/*
 * Função: atacar
 * Objetivo: Simular um ataque entre dois territórios (atacante -> defensor).
 * Regras implementadas (conforme instruções):
 *  - Cada lado rola um dado (1..6) com rand().
 *  - Se o atacante vencer (dadoAtacante > dadoDefensor):
 *      * O defensor muda de dono (recebe a cor do atacante).
 *      * Metade das tropas do atacante (truncado) é transferida para o defensor.
 *      * O atacante perde essas tropas transferidas.
 *  - Se o atacante perder (<= do defensor):
 *      * O atacante perde 1 tropa (não fica negativo).
 *  - Restrições:
 *      * Para atacar, o atacante deve ter pelo menos 2 tropas (regra comum em jogos de território).
 */
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante == NULL || defensor == NULL) return;

    if (atacante->tropas < 2) {
        printf("\n[Aviso] '%s' não possui tropas suficientes para atacar (mínimo: 2).\n", atacante->nome);
        return;
    }

    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();

    printf("\n--- Simulação de Ataque ---\n");
    printf("Atacante: %s (%s) rolou: %d | Tropas: %d\n",
           atacante->nome, atacante->cor, dadoAtacante, atacante->tropas);
    printf("Defensor: %s (%s) rolou: %d | Tropas: %d\n",
           defensor->nome, defensor->cor, dadoDefensor, defensor->tropas);

    if (dadoAtacante > dadoDefensor) {
        // Vitória do atacante
        int tropasTransferidas = atacante->tropas / 2; // metade, truncada
        if (tropasTransferidas < 1) tropasTransferidas = 1; // garante ocupação mínima

        // Atualiza dono do território defensor
        strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
        defensor->cor[sizeof(defensor->cor) - 1] = '\0';

        // Defensor passa a ter as tropas transferidas
        defensor->tropas = tropasTransferidas;

        // Atacante perde as tropas transferidas
        atacante->tropas -= tropasTransferidas;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("\nResultado: Vitória do atacante!\n");
        printf("'%s' agora pertence a %s e ficou com %d tropas.\n",
               defensor->nome, defensor->cor, defensor->tropas);
        printf("'%s' ficou com %d tropas restantes.\n", atacante->nome, atacante->tropas);
    } else {
        // Derrota (ou empate) do atacante
        if (atacante->tropas > 0) atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("\nResultado: Defesa bem-sucedida!\n");
        printf("'%s' perdeu 1 tropa e agora tem %d tropas.\n", atacante->nome, atacante->tropas);
    }
}

/*
 * Função: liberarMemoria
 * Objetivo: Liberar a memória alocada para o vetor de Territorio.
 */
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

/*
 * Menu simples para orientar o jogador entre ações.
 */
int menu(void) {
    printf("\n===== MENU =====\n");
    printf("1 - Exibir territórios\n");
    printf("2 - Realizar ataque\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    int op;
    if (scanf("%d", &op) != 1) {
        limparBuffer();
        return -1;
    }
    limparBuffer();
    return op;
}

int main(void) {
    srand((unsigned)time(NULL)); // semente para números aleatórios

    int n;
    printf("Informe a quantidade de territórios: ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        printf("Valor inválido. Digite um inteiro > 0: ");
        limparBuffer();
    }
    limparBuffer();

    // Alocação dinâmica com calloc para inicializar memória a zero
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
    if (!mapa) {
        fprintf(stderr, "Erro: falha ao alocar memória.\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, n);

    // Exibição inicial
    exibirTerritorios(mapa, n);

    // Loop principal (ataques/exibição)
    for (;;) {
        int op = menu();
        if (op == 0) break;

        switch (op) {
            case 1: {
                exibirTerritorios(mapa, n);
                break;
            }
            case 2: {
                if (n < 2) {
                    printf("\nSão necessários ao menos 2 territórios para atacar.\n");
                    break;
                }

                exibirTerritorios(mapa, n);
                int idxA, idxD;

                printf("\nEscolha o índice do território ATACANTE: ");
                while (scanf("%d", &idxA) != 1 || idxA < 0 || idxA >= n) {
                    printf("Índice inválido. Digite entre 0 e %d: ", n - 1);
                    limparBuffer();
                }
                limparBuffer();

                printf("Escolha o índice do território DEFENSOR: ");
                while (scanf("%d", &idxD) != 1 || idxD < 0 || idxD >= n || idxD == idxA) {
                    printf("Índice inválido (e diferente do atacante). Digite entre 0 e %d: ", n - 1);
                    limparBuffer();
                }
                limparBuffer();

                Territorio *atacante = (mapa + idxA);
                Territorio *defensor  = (mapa + idxD);

                atacar(atacante, defensor);

                // Exibição pós-ataque
                exibirTerritorios(mapa, n);
                break;
            }
            default:
                printf("\nOpção inválida.\n");
        }
    }

    // Liberação da memória
    liberarMemoria(mapa);

    printf("\nPrograma encerrado. Obrigado por jogar!\n");
    return 0;
}

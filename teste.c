#include <stdio.h>
#include "caminho.h"

void ExibirHistorico(Posicao *P) {
    while (P != NULL) {
        printf("(%d, %d)", P->X, P->Y);
        if (P->Proximo != NULL) {
            printf(" -> ");
        }
        P = P->Proximo;
    }
    printf("\n");
}

int main(void) {
    Caminho *C;
    Posicao *Fim;
    Posicao *Historico;

    printf("Teste 1: exemplo do enunciado\n");
    C = InicializarCaminho("LLLLLLLNNNNN", 2, 2);

    if (C == NULL) {
        printf("Erro ao inicializar caminho.\n");
        return 1;
    }

    Fim = DeterminarFim(C);
    Historico = HistoricoPosicoes(C);

    printf("Fim esperado: (9, 7)\n");
    printf("Fim obtido: (%d, %d)\n", Fim->X, Fim->Y);

    printf("Historico:\n");
    ExibirHistorico(Historico);

    printf("Distancia total esperada: 12\n");
    printf("Distancia total obtida: %d\n", CalcularDistanciaTotal(C));

    printf("Distancia geometrica esperada: 8.60\n");
    printf("Distancia geometrica obtida: %.2f\n", CalcularDistanciaGeometrica(C));

    printf("Distancia Manhattan esperada: 12\n");
    printf("Distancia Manhattan obtida: %d\n", CalcularDistanciaManhattan(C));

    printf("Quantidade de instrucoes esperada: 12\n");
    printf("Quantidade de instrucoes obtida: %d\n", ContarInstrucoes(C));

    DestruirCaminho(C);

    printf("\nTeste 2: sequencia vazia\n");
    C = InicializarCaminho("", 5, -3);
    Fim = DeterminarFim(C);

    printf("Fim esperado: (5, -3)\n");
    printf("Fim obtido: (%d, %d)\n", Fim->X, Fim->Y);
    printf("Instrucoes esperadas: 0\n");
    printf("Instrucoes obtidas: %d\n", ContarInstrucoes(C));

    DestruirCaminho(C);

    printf("\nTeste 3: comando invalido\n");
    C = InicializarCaminho("NNLXSS", 0, 0);

    if (C == NULL) {
        printf("Resultado correto: retornou NULL para comando invalido.\n");
    } else {
        printf("Erro: deveria retornar NULL.\n");
        DestruirCaminho(C);
    }

    printf("\nTeste 4: ponteiro NULL nas funcoes\n");
    printf("DeterminarFim(NULL): %s\n", DeterminarFim(NULL) == NULL ? "NULL" : "erro");
    printf("HistoricoPosicoes(NULL): %s\n", HistoricoPosicoes(NULL) == NULL ? "NULL" : "erro");
    printf("CalcularDistanciaTotal(NULL): %d\n", CalcularDistanciaTotal(NULL));
    printf("CalcularDistanciaGeometrica(NULL): %.1f\n", CalcularDistanciaGeometrica(NULL));
    printf("CalcularDistanciaManhattan(NULL): %d\n", CalcularDistanciaManhattan(NULL));
    printf("ContarInstrucoes(NULL): %d\n", ContarInstrucoes(NULL));

    return 0;
}
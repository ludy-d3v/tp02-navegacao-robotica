#include <stdlib.h>
#include "caminho.h"

// cria um novo no de posicao com as coordenadas x e y 
static Posicao *CriarPosicao(int x, int y) {
    Posicao *P = (Posicao *) malloc(sizeof(Posicao));
    
    if (P == NULL) {
        return NULL;
    }

    P->X = x;
    P->Y = y;
    P->Proximo = NULL;

    return P;
}

// cria um novo no de comando com a direcao informada
static Comando *CriarComando(char direcao) {
    Comando *C = (Comando *) malloc(sizeof(Comando));

    if (C == NULL) {
        return NULL;
    }

    C->Direcao = direcao;
    C->Proximo = NULL;

    return C;
}

// verifica se o caractere e um comando valido (N, S, L ou O)
static int ComandoValido(char direcao) {
    if (direcao == 'N' || direcao == 'S' || direcao == 'L' || direcao == 'O') {
        return 1;
    }
    return 0;
}

// atualiza as coordenadas x e y de acordo com a direcao
static void AplicarComando(char direcao, int *x, int *y) {
    if (direcao == 'N') {
        *y = *y + 1;
    } else if (direcao == 'S') {
        *y = *y - 1;
    } else if (direcao == 'L') {
        *x = *x + 1;
    } else if (direcao == 'O') {
        *x = *x - 1;
    }
}

// libera todos os nos da lista de comandos
static void LiberarComandos(Comando *I) {
    Comando *Aux;

    while (I != NULL) {
        Aux = I->Proximo;
        free(I);
        I = Aux;
    }
}

// libera todos os nos da lista de posicoes
static void LiberarPosicoes(Posicao *P) {
    Posicao *Aux;
    while (P != NULL) {
        Aux = P->Proximo;
        free(P);
        P = Aux;
    }
}

static double RaizQuadrada(double valor) {
    double resultado;
    int i;

    if (valor <= 0.0) {
        return 0.0;
    }

    resultado = valor;
    for (i = 0; i < 20; i++) {
        resultado = (resultado + valor / resultado) / 2.0;
    }

    return resultado;
}

Caminho *InicializarCaminho(const char *Sequencia, int xInicial, int yInicial) {
    Caminho *C;
    Comando *UltimoComando = NULL;
    Posicao *UltimaPosicao;
    int x = xInicial;
    int y = yInicial;
    int i = 0;

    if (Sequencia == NULL) {
        return NULL;
    }

    // aloca e inicializa a struct do caminho
    C = (Caminho *) malloc(sizeof(Caminho));
    if (C == NULL) {
        return NULL;
    }

    C->Inicio = NULL;
    C->Fim = NULL;
    C->Historico = NULL;
    C->Instrucoes = NULL;
    C->N = 0;

    // insere a posicao inicial no historico
    C->Historico = CriarPosicao(xInicial, yInicial);
    if (C->Historico == NULL) {
        DestruirCaminho(C);
        return NULL;
    }

    C->Inicio = C->Historico;
    C->Fim = C->Historico;
    UltimaPosicao = C->Historico;

    // percorre a sequencia de comandos
    while (Sequencia[i] != '\0') {
        Comando *NovoComando;
        Posicao *NovaPosicao;

        // checa se o comando e valido
        if (!ComandoValido(Sequencia[i])) {
            DestruirCaminho(C);
            return NULL;
        }

        // cria e encadeia o novo comando
        NovoComando = CriarComando(Sequencia[i]);
        if (NovoComando == NULL) {
            DestruirCaminho(C);
            return NULL;
        }

        if (UltimoComando == NULL) {
            C->Instrucoes = NovoComando;
        } else {
            UltimoComando->Proximo = NovoComando;
        }
        UltimoComando = NovoComando;

        // aplica o comando e registra a nova posicao
        AplicarComando(Sequencia[i], &x, &y);

        NovaPosicao = CriarPosicao(x, y);
        if (NovaPosicao == NULL) {
            DestruirCaminho(C);
            return NULL;
        }

        UltimaPosicao->Proximo = NovaPosicao;
        UltimaPosicao = NovaPosicao;
        C->Fim = NovaPosicao;
        C->N++;
        i++;
    }

    return C;
}

void DestruirCaminho(Caminho *C) {
    if (C == NULL) {
        return;
    }
    // libera as listas e depois a struct principal
    LiberarPosicoes(C->Historico);
    LiberarComandos(C->Instrucoes);
    free(C);
}

Posicao *DeterminarFim(Caminho *C) {
    if (C == NULL || C->Fim == NULL) {
        return NULL;
    }

    return C->Fim;
}

Posicao *HistoricoPosicoes(Caminho *C) {
    if (C == NULL || C->Historico == NULL) {
        return NULL;
    }

    return C->Historico;
}

// a distancia total e o numero de movimentos realizados
int CalcularDistanciaTotal(Caminho *C) {
    if (C == NULL) {
        return -1;
    }

    return C->N;
}

// distancia euclidiana entre inicio e fim usando a formula da hipotenusa
double CalcularDistanciaGeometrica(Caminho *C) {
    int dx;
    int dy;

    if (C == NULL || C->Inicio == NULL || C->Fim == NULL) {
        return -1.0;
    }

    dx = C->Fim->X - C->Inicio->X;
    dy = C->Fim->Y - C->Inicio->Y;

    return RaizQuadrada((double) dx * dx + (double) dy * dy);
}

// distancia de Manhattan: soma dos valores absolutos das diferencas
int CalcularDistanciaManhattan(Caminho *C) {
    int dx;
    int dy;

    if (C == NULL || C->Inicio == NULL || C->Fim == NULL) {
        return -1;
    }

    dx = C->Fim->X - C->Inicio->X;
    dy = C->Fim->Y - C->Inicio->Y;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    return dx + dy;
}

// retorna a quantidade de instrucoes executadas no caminho
int ContarInstrucoes(Caminho *C) {
    if (C == NULL) {
        return -1;
    }

    return C->N;
}

#include "caminho.h"
#ifndef TROPA_H_INCLUDED
#define TROPA_H_INCLUDED

using namespace std;

typedef struct tropa
{
    int vida;
    Caminho caminho;
    int dirAtual = -1;
    int posAtual = 0;
    int animacao;
    int timer;
} Tropa;

void DesenhaTropa(Tropa *t)
{
    int *p = &t->posAtual;
    int timer = t->timer;
    if (t->vida > 0)
    {
        DesenhaAnimacao(t->animacao);
        if (*p == t->caminho.posicoes.size()) return;

        if (TempoDecorrido(timer) > 0.03)
        {
            MoveAnimacao(t->animacao, t->caminho.posicoes[*p].x, t->caminho.posicoes[*p].y);
            if (t->dirAtual != t->caminho.posicoes[*p].direcao)
            {
                MudaModoAnimacao(t->animacao, t->caminho.posicoes[*p].direcao, 1);
                t->dirAtual = t->caminho.posicoes[*p].direcao;
                printf ("Direcao: %d\n", t->dirAtual);
            }
            t->posAtual++;
            ReiniciaTimer(timer);
        }
    }
    else DestroiAnimacao(t->animacao);
}

#endif // TROPA_H_INCLUDED

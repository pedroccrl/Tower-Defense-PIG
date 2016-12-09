#include <vector>
#include <stdio.h>
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef CAMINHO_H_INCLUDED
#define CAMINHO_H_INCLUDED

using namespace std;

typedef struct posicao
{
    int x,y;
    int direcao;
} Posicao;


typedef struct caminho
{
    vector<Posicao> posicoes;
} Caminho;


Caminho  LerCaminho1()
{
    Caminho caminho;
    int qual=2;
    //c->animacao = an;
    FILE *f = fopen ("caminhos_1.txt", "rt");
    int d,x,y,x2=-1,y2=-1;
    while (fscanf(f, "%d %d %d\n", &d, &x, &y) == 3)
    {
        if (x2==-1 && y2==-1) fscanf(f, "%d %d %d\n", &d, &x2, &y2);
        else
        {
            int aux = x2;
            x2 = x;
            x = aux;
            aux = y2;
            y2 = y;
            y = aux;
        }

        int cx,cy;
        cx = x2-x;
        cy = y2-y;
        int razao = abs(cx/cy);
        int pontos = abs(cy)/qual;
        printf("\n\nPONTOS: %d\n\n", pontos);
        for (int q=qual; q<pontos*qual; q+=qual)
        {
            Posicao ca;
            if (cx>0)x += razao*qual;
            else x -= razao*qual;
            if (cy>0) y += qual;
            else y -= qual;
            ca.x = x;
            ca.y = y;
            ca.direcao = d;

            caminho.posicoes.push_back(ca);
            printf("(%d, %d)\n", x, y);
        }

    }
    fclose(f);

    return caminho;
}
#endif // CAMINHO_H_INCLUDED

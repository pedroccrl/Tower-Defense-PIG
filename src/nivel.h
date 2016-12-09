#ifndef NIVEL_H_INCLUDED
#define NIVEL_H_INCLUDED

using namespace std;

typedef struct nivel
{
    vector <Tropa> tropas1;
    vector <Tropa> tropas2;
    vector <Tropa> tropas3;
    int qtdTropas;
    float velTropas;
    int level;
    Caminho caminho1;
    Caminho caminho2;
    Caminho caminho3;
    int timer;
} Nivel;

Nivel CriaNivel(int level, int qtd, float vel)
{
    Nivel nivel;
    nivel.level = level;
    nivel.qtdTropas = qtd;
    nivel.velTropas = vel;
    nivel.caminho1 = LerCaminho1();
    nivel.timer = CriaTimer();
    printf ("Nivel criado\n");

    return nivel;
}

void DesenhaNivel(Nivel *nivel)
{
    if (TempoDecorrido(nivel->timer) > nivel->velTropas && nivel->tropas1.size() < nivel->qtdTropas)
    {
        Tropa t;
        t.caminho = nivel->caminho1;
        t.vida = 100;
        t.posAtual=0;
        t.animacao = CriaAnimacaoCarroBombaHD();
        t.timer = CriaTimer();
        MudaModoAnimacao(t.animacao, CIMA, 1);
        nivel->tropas1.push_back(t);
        ReiniciaTimer(nivel->timer);
    }
    for (int i=0; i<nivel->tropas1.size(); i++)
    {
        //printf ("Posição tropa %d: %d\n", i+1, nivel->tropas1[i].posAtual);
        DesenhaTropa(&nivel->tropas1[i]);

    }

}

#endif // NIVEL_H_INCLUDED

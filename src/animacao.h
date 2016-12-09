#ifndef ANIMACAO_H_INCLUDED
#define ANIMACAO_H_INCLUDED

int CriaAnimacaoFogo()
{
    int fogo = CriaAnimacao("..//imagens//efeitos.png");
    SetDimensoesAnimacao(fogo,60,43);
    CriaModoAnimacao(fogo, 0, 1);
    MoveAnimacao(fogo, 108, 700);
    for (int i=0; i<14; i++)
    {
        CriaFrameAnimacao(fogo, i, 43*i, 331, 60, 43);
        InsereFrameAnimacao(fogo, 0, i, 0.1);
    }
    MudaModoAnimacao(fogo, 0, 1);
    return fogo;
}

int CriaAnimacaoCarroBomba()
{
    int cb = CriaAnimacao("..//imagens//acarrobomba2.png", 0);
    SetDimensoesAnimacao(cb, 45, 43);

    int frame=0;
    for (int d=0; d < 4; d++)
    {
        CriaModoAnimacao(cb, d, 1);
        for (int i=0; i<10; i++)
        {
            CriaFrameAnimacao(cb, (d*10)+i, 98*i, d*100, 100, 98);
            InsereFrameAnimacao(cb, d, (d*10)+i, 0.15);
        }
    }
    MudaModoAnimacao(cb, 0,1);
    return cb;
}

int CriaAnimacaoCarroBombaHD()
{
    int cb = CriaAnimacao("..//imagens//carrobombahd.png", 0);
    SetDimensoesAnimacao(cb, 99, 97);

    int frame=0;
    for (int d=0; d < 4; d++)
    {
        CriaModoAnimacao(cb, d, 1);
        for (int i=0; i<12; i++)
        {
            CriaFrameAnimacao(cb, d*12+i, 196*i, d*199, 199, 196);
            InsereFrameAnimacao(cb, d, d*12+i, 0.15);
        }
    }
    MudaModoAnimacao(cb, 0, 1);
    return cb;
}

#endif // ANIMACAO_H_INCLUDED

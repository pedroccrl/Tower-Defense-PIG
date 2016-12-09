// PEDRO CÂMARA


#include "PIG.h"
#include "math.h"

#define ESQUERDA 0
#define CIMA 1
#define DIREITA 2
#define BAIXO 3
#include "animacao.h"
#include "Tropa.h"
#include "nivel.h"


PIG_Evento evento;
PIG_Teclado meuTeclado;

int Muros[1000];
int MurosQtd=0;

void DesenhaMuros() { for (int i=0; i<MurosQtd; i++) DesenhaObjeto(Muros[i]); }

void InsereMuroOrdenado(int muro)
{

    int x,y,xa,ya;
    GetXYObjeto(muro,&x,&y);
//    if (MurosQtd-1>=0)
//    {
//        for (int i=0; i<MurosQtd; i++)
//        {
//            GetXYObjeto(Muros[i],&xa,&ya);
//            if (x>xa && y>ya)
//            {
//                int aux = Muros[i];
//                Muros[MurosQtd] = aux;
//                Muros[i]=muro;
//                MurosQtd++;
//                return;
//            }
//        }
//    }
    Muros[MurosQtd] = muro;
    MurosQtd++;
}

void LerObjetosArquivo()
{
    FILE *f = fopen ("muros_f.txt", "rt");
    int tipo,x,y;
    while (fscanf(f, "%d %d %d\n", &tipo, &x, &y) == 3)
    {
        int obj;
        if (tipo==1) obj = CriaObjeto("..//imagens//muro1s.png",1,255);
        else obj = CriaObjeto("..//imagens//muro2s.png",1,255);
        MoveObjeto(obj,x,y);
        Muros[MurosQtd] = obj;
        printf("%d %d %d %d\n", tipo, x, y, obj);
        MurosQtd++;
    }
    fclose(f);
}

void SetObjetosArquivo(int tipo, int objeto)
{
    FILE *f = fopen("caminhos.txt", "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // {tipo muro} {x} {y}

    int x,y;
    GetXYObjeto(objeto,&x,&y);
    fprintf(f, "%d %d %d\n", tipo, x, y);


    fclose(f);
}

float angulo=0.36f;
int var = 12;
//int c=300;
//int ox=c,xx2=1000,xy2=c;
//int oy=c,yx2=c,yy2=700;
//void DesenhaReferenciais()
//{
//    int rox = ox*cos(angulo) - oy*sin(angulo);
//    int roy = ox*sin(angulo) + oy*cos(angulo);
//
//    int rxx2 = xx2*cos(angulo) - xy2*sin(angulo);
//    int rxy2 = xx2*sin(angulo) + xy2*cos(angulo);
//
//    int ryx2 = yx2*cos(angulo) - yy2*sin(angulo);
//    int ryy2 = yx2*sin(angulo) + yy2*cos(angulo);
//
//    DesenhaLinhaSimples(c,c,rxx2,rxy2,VERMELHO);
//    DesenhaLinhaSimples(c,c,ryx2,ryy2,VERMELHO);
//
//}

int main( int argc, char* args[] )
{

    CriaJogo("3D Tower Defense", 0);
    meuTeclado = GetTeclado();
    LerObjetosArquivo();

//    Caminho *caminhosCarroBomba = LerCaminho1(CriaAnimacaoCarroBomba());
    //LerCaminho1(CriaAnimacaoCarroBombaHD());
    int mapa = CriaObjeto("..//imagens//terreno_s.png", 1, 255);
    int torre = CriaObjeto("..//imagens//carrobomba.png", 1, 255);
    SetDimensoesObjeto(mapa,ALT_TELA,LARG_TELA);

    int castelo = CriaObjeto("..//imagens//castle.png");
    MoveObjeto(castelo,1,500);
    //CriaFrameAnimacao(castelo, 0, 1425, 0, 384, 475);
    int fogo = CriaAnimacaoFogo();
    //int carroBomba = CriaAnimacaoCarroBomba();
    int c1 = 0;
    int cX=0, cY=0;
    int timer = CriaTimer();
    int o = 0;
    int m = CriaObjeto("..//imagens//muro1s.png",1,255);
    int m2 = CriaObjeto("..//imagens//muro2s.png",1,255);
    int mAtual=m;
    int timerFogo = CriaTimer();
    int timerCaminho1 = CriaTimer();
    int timerAnimacaoCaminho1 = CriaTimer();
    int cbHD = CriaAnimacaoCarroBombaHD();



    int timerNivel = CriaTimer();
    Nivel nivel1 = CriaNivel(1, 10, 3);

    while(JogoRodando()){
        evento = GetEvento();
        IniciaDesenho();

        DesenhaObjeto(mapa);
        //DesenhaObjeto(torre);
        DesenhaAnimacao(cbHD);
        DesenhaMuros();

        DesenhaObjeto(castelo);
        //DesenhaReferenciais();


        int posX, posY, varx, vary;



        varx = evento.mouse.posX/54;
        vary = evento.mouse.posY/27;
        posX = varx*54;
        posY = vary*27;

        MoveObjeto(mAtual,posX,posY);
        DesenhaObjeto(mAtual);
        if (evento.teclado.acao == TECLA_PRESSIONADA && TempoDecorrido(timer)>0.2)
        {
            ReiniciaTimer(timer);
            if (evento.teclado.tecla == TECLA_ESQUERDA) MudaModoAnimacao(cbHD, ESQUERDA, 1);
            else if (evento.teclado.tecla == TECLA_DIREITA) MudaModoAnimacao(cbHD, DIREITA, 1);

            if (evento.teclado.tecla == TECLA_CIMA) MudaModoAnimacao(cbHD, CIMA, 1);
            else if (evento.teclado.tecla == TECLA_BAIXO) MudaModoAnimacao(cbHD, BAIXO, 1);

            if (evento.teclado.tecla == TECLA_CIMA)
            {

            }

            if (angulo<0) angulo=0;
            printf("angulo: %f, var: %d\n", angulo, var);
        }
        if (evento.mouse.acao == MOUSE_PRESSIONADO && TempoDecorrido(timer)>0.2)
        {
            if (evento.mouse.botao == MOUSE_ESQUERDO)
            {
                int mP;
                if (mAtual==m) mP = CriaObjeto("..//imagens//muro1s.png",1,255);
                else mP = CriaObjeto("..//imagens//muro2s.png",1,255);
                MoveObjeto(mP,posX,posY);
                ReiniciaTimer(timer);
                printf("X: %d, Y: %d\n", posX, posY);

                if (mAtual==m) SetObjetosArquivo(1,mP);
                else SetObjetosArquivo(2,mP);

                InsereMuroOrdenado(mP);

            }
            if (evento.mouse.botao == MOUSE_DIREITO)
            {
                if (mAtual==m2) mAtual=m;
                else mAtual=m2;
            }
        }
        //DesenhaAnimacao(carroBomba);
        DesenhaAnimacao(fogo);

        //printf ("Tropas no nivel %d: %d\n", nivel1.level, nivel1.tropas1.size());
        DesenhaNivel(&nivel1);

        EncerraDesenho();
    }
    FinalizaJogo();

    return 0;
}


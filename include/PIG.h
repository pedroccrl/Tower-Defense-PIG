/********************************
Vers�o 0.5.1 da Biblioteca Pig.h
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Tipos_PIG.h"
#include "CPoolNumeros.h"
#include "CAssetLoader.h"
#include "CMapaCaracteres.h"
#include "CGerenciadorObjetos.h"
#include "CGerenciadorTimers.h"
#include "CGerenciadorParticulas.h"
#include "CGerenciadorAnimacoes.h"
#include "CMouse.h"
#include "CJogo.h"

/********************************
/ Vari�veis Globais
/********************************/
Jogo jogo=NULL;

/********************************
A fun��o CriaJogo() � respons�vel pela cria��o da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra fun��o da biblioetac PIG.h. N�o � poss�vel criar dois
jogos no mesmo progama. Logo, somente a primeira chamada ter� efeito.
Par�metros:
nome_Janela (entrada, passagem por refer�ncia*): indica o nome que a janela do jogo mostrar� no seu t�tulo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
cursor_Proprio (entrada, passagem por valor): indica se o jogo utilizar� cursores (ponteiros) pr�prios para o mouse ou utilizar� o cursor padr�o.
********************************/
void CriaJogo(char *nome_Janela,int cursor_Proprio=0)
{
    if (jogo==NULL){
        jogo = new CJogo(nome_Janela,cursor_Proprio);
        CAssetLoader::Inicia();
        if (cursor_Proprio!=0)
            CMouse::Inicia(jogo->renderer);
        CGerenciadorTimers::Inicia();
        CGerenciadorObjetos::Inicia(jogo->renderer);
        CGerenciadorParticulas::Inicia(jogo->renderer);
        CGerenciadorAnimacoes::Inicia(jogo->renderer);
    }
}

/********************************
A fun��o GetEstadoJogo() indica o estado do jogo. Este estado � apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Retorno:
inteiro indicando o valor do estado do jogo.
********************************/
int GetEstadoJogo()
{
    return jogo->GetEstado();
}

/********************************
A fun��o SetEstadoJogo() atribui um novo valor ao estado do jogo. Este estado � apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Par�metro:
estado (entrada, passagem por valor): indica o novo estado do jogo;
********************************/
void SetEstadoJogo(int estado)
{
    jogo->SetEstado(estado);
}

/********************************
A fun��o DefineFundo() permite escolher um arquivo de imagem como fundo (background) do jogo que ser� automaticamente desenhado a cada nova etapa de desenho na tela.
Par�metros:
nome_ArquivoImagem (entrada, passagem por refer�ncia*): indica o caminho relativo ou absoluto do arquivo de imagem que ser� utilizado como fundo do jogo.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void DefineFundo(char *nome_ArquivoImagem)
{
    jogo->DefineFundo(nome_ArquivoImagem);
}

/********************************
A fun��o GetTeclado() faz um mapeamento entre o teclado f�sico a uma vari�vel do tipo PIG_Teclado que funciona como um vetor de vari�veis l�gicas,
sendo cada posi��o do vetor relativo a uma tecla f�sica.
Uma lista das poss�veis teclas e seus c�digo pode ser vista no arquivo Tipos_PIG.h.
Retorno:
O valor de retorno da fun��o � um vetor de n�meros inteiros que indicam se uma determinada tecla (�ndice do vetor) foi
pressionada (valor diferente de 0,zero) ou n�o (valor igual a zero).
********************************/
PIG_Teclado GetTeclado()
{
    return jogo->PegaTeclado();
}

/********************************
A fun��o GetEvento() indica se houve algum tipo de evento desde a �ltima vez que a fun��o foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada � tela do jogo.
Maiores informa��e podem ser vistas no arquivo Tipo_PIG.h
Retorno:
O valor de retorno � um struct contendo o tipo de evento ocorrido e v�rios outros structs com informa��es espec�ficas.
********************************/
PIG_Evento GetEvento()
{
    return jogo->PegaEvento();
}

/********************************
A fun��o IniciaDesenho() � respons�vel por preparar a janela do jogo para que os objetos gr�ficos
possam ser mostrados, al�m de desenhar a imagem de fundo do jogo, caso tenha sido definida.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
********************************/
void IniciaDesenho()
{
    jogo->IniciaDesenho();
}

/********************************
A fun��o EncerraDesenho() � respons�vel por encerrar o desenho que foi criado, mostrando na tela do jogo.
Deve ser chamado sempre ao final do loop principal do jogo.
********************************/
void EncerraDesenho()
{
    if (jogo->cursorPadrao!=0)
        CMouse::Desenha();
    jogo->EncerraDesenho();
}

/********************************
A fun��o SalvaTela() � respons�vel por criar um arquivo Bitmap, contendo uma c�pia da tela do jogo naquele momento.
Par�metros:
nomeArquivoBMP (entrada, passagem por refer�ncia*): indica o nome do arquivo Bitmap que ser� salvo. O valor do par�metro deve conter a extens�o ".bmp".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void SalvaTela(char *nomeArquivoBMP)
{
    jogo->SaveScreenshotBMP(nomeArquivoBMP);
}

/********************************
A fun��o JogoRodando() � repons�vel por retornar se o jogo ainda est� ativo ou n�o.
O jogo ser� encerrado se a janela do jogo for fechada, por exemplo.
Retorno:
inteiro que indica se o jogo ainda est� sendo executado (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int JogoRodando()
{
    return jogo->GetRodando();
}

/********************************
A fun��o Espera() "congela" a tela do jogo por alguns milisegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Par�metros:
tempo (entrada, passagem por valor): indica a quantidade de milisegundos durante a qual o jogo ser� pausado.
********************************/
void Espera(int tempo)
{
    SDL_Delay(tempo);
}

/********************************
A fun��o FinalizaJogo() � respons�vel por encerrar com a PIG. Ap�s tudo o jogo ser executado
a fun��o deve ser chamada e ela ir� realizar a libera��o de mem�ria dos elementos criados pela PIG.
********************************/
void FinalizaJogo()
{
    CGerenciadorAnimacoes::Encerra();
    CGerenciadorParticulas::Encerra();
    CGerenciadorObjetos::Encerra();
    CGerenciadorTimers::Encerra();
    if (jogo->cursorPadrao==0)
        CMouse::Encerra();
    CAssetLoader::Encerra();
    delete jogo;
}

/********************************
A fun��o GetFPS() � respons�vel por calcular o valor do Frames Per Seconds (FPS), que representa a quantidade de
frames (quadros) desenhados por segundo pela PIG.
Retorno:
float que indica a m�dia de quadros desenhados por segundo.
********************************/
float GetFPS()
{
    return jogo->GetFPS();
}

/********************************
A fun��o CarregaCursor() � respons�vel por armazenar um novo cursor para o mouse, dado pelo arquivo de imagem indicado.
O arquivo deve ser uma imagem com 32 pixels de altura orbigatoriamente.
Par�metro:
indice (entrada, passagem por valor): informa um �ndice para este novo cursor. Se o �ndice j� estiver sendo utilizado,
o cursor antigo � removido. O valor deve estar entre 0..MAX_CURSORES-1.
nomeArquivoCursor (entrada, passagem por refer�ncia*): indica o nome do arquivo de imagem que ser� utilziado como cursor do mouse.
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void CarregaCursor(int indice,char *nomeArquivoCursor)
{
    CMouse::CarregaCursor(indice,nomeArquivoCursor);
}

/********************************
A fun��o MudaCursor() � respons�vel por alterar o cursor atual do mouse por outro j� carregado.
Par�metro:
indice (entrada, passagem por valor): informa um �ndice para este novo cursor que j� deve ter sido
carregado anteriormente e deve estar no intervalo 0..MAX_CURSORES-1.
********************************/
void MudaCursor(int indice)
{
    CMouse::MudaCursor(indice);
}


/********************************
Se��o de elementos geom�tricos
********************************/

/********************************
A fun��o Desenha_LinhasSimples() � respons�vel por desenhar uma �nica linha, cujo in�cio � o ponto (x1,y1) e o fim � o ponto (x2,y2).
Par�metros:
pontoX1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho da linha;
********************************/
void DesenhaLinhaSimples(int pontoX1,int pontoY1,int pontoX2,int pontoY2, PIG_Cor cor)
{
    jogo->DesenhaLinhaSimples(pontoX1,pontoY1,pontoX2,pontoY2,cor);
}

/********************************
A fun��o DesenhaLinhasDisjuntas() � respons�vel por desenhar linhas separadamente, ou seja, os ponto iniciais de cada linha est�o nas posi��es pares e
os pontos finais est�o nas posi��es �mpares. Assim, os vetores precisam ter tamanho qtd*2.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd*2, contendo os valores X (inicias e finais) de cada linha.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd*2, contendo os valores Y (inicias e finais) de cada linha.
qtd (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
********************************/
void DesenhaLinhasDisjuntas(int *pontosX,int *pontosY,int qtd, PIG_Cor cor)
{
    jogo->DesenhaLinhasDisjuntas(pontosX,pontosY,qtd,cor);
}

/********************************
A fun��o DesenhaLinhasSequencia() � respons�vel por desenhar linhas em sequ�ncia, ou seja, o ponto final da primeira linha
corresponde ao ponto inicial da segunda linha.
Par�metros:
pontosX (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd+1, contendo os valores X de cada linha da sequ�ncia.
pontosY (entrada, passagem por refer�ncia): vetor de inteiros, de tamanho qtd+1, contendo os valores Y de cada linha da sequ�ncia.
qtd (entrada, passagem por valor): quantidade de linhas a serem desenhadas.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
********************************/
void DesenhaLinhasSequencia(int *pontosX,int *pontosY,int qtd, PIG_Cor cor)
{
    jogo->DesenhaLinhasSequencia(pontosX,pontosY,qtd,cor);
}

/********************************
A fun��o DesenhaRetangulo() � respons�vel por desenhar um ret�ngulo com preenchimento s�lido na tela em uma posi��o desejada pelo usu�rio.
O mesmo pode ser colocado em qualquer lugar do campo de vis�o da tela.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do ret�ngulo;
********************************/
void DesenhaRetangulo(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor)
{
    jogo->DesenhaRetangulo(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
A fun��o DesenhaRetanguloVazado() � respons�vel por desenhar um ret�ngulo sem preenchimento na tela em uma posi��o desejada pelo usu�rio.
O mesmo pode ser colocado em qualquer lugar do campo de vis�o da tela.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do ret�ngulo;
********************************/
void DesenhaRetanguloVazado(int posicaoX, int posicaoY, int altura, int largura, PIG_Cor cor)
{
    jogo->DesenhaRetanguloVazado(posicaoX,posicaoY,altura,largura,cor);
}

/********************************
Se��o de desenho Offscreen
********************************/

/********************************
A fun��o PreparaOffScreenRenderer() serve para criar um novo bitmap offscreen que servir� de �rea
de desenho para outras fun��es que utilizem este bitmap.
Par�metros:
altura (entrada, passagem por valor): indica a altura em pixels do novo bitmap.
largura (entrada, passagem por valor): indica a largura em pixels do novo bitmap.
********************************/
void PreparaOffScreenRenderer(int altura,int largura)
{
    jogo->PreparaOffScreenRenderer(altura,largura);
}

/********************************
A fun��o SalvaOffScreenBMP() serve para efetivamente salvar o bitmap offscreen como um arquivo do sistema operacional.
O bitmap offscreen continuar� existindo em mem�ria e a��es subsequentes ainda poder�o ser feitas. Para "limpar" o bitmap
deve-se utilizar a fun��o PintaFundoOffScreen().
Par�metros:
nomeArquivoBMP (entrada, passagem por refer�ncia*): indica com que nome o bitmap offscreen ser� salvo. O valor do par�metro deve conter a extens�o ".bmp".
� utilizado o operador * apenas por se tratar de um par�metro string. O valor do par�metro n�o � alterado dentro da fun��o.
********************************/
void SalvaOffScreenBMP(char *nomeArquivoBMP)
{
    jogo->SalvaOffScreenBMP(nomeArquivoBMP);
}

/********************************
A fun��o PintaAreaOffScreen() serve para mudar a cor de uma �rea cont�gua de pixels da mesma cor.
A funcionalidade � semelhante � ferramenta "balde" dos editores de imagem. A �rea ser� pintada a partir do
ponto (posicaoX,posicaoY) de acordo com o sistema de coordenadas da PIG.
Par�metros:
posicaoX (entrada, passagem por valor): indica o ponto no eixo X para come�ar a pintar a �rea cont�gua de pixels.
posicaoY (entrada, passagem por valor): indica o ponto no eixo Y para come�ar a pintar a �rea cont�gua de pixels.
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura da �rea cont�gua de pixels.
********************************/
void PintaAreaOffScreen(int posicaoX,int posicaoY,PIG_Cor cor)
{
    jogo->PintaAreaOffScreen(posicaoX,posicaoY,cor);
}

/********************************
A fun��o PintaFundoOffScreen() serve para "limpar" o bitmap offscreen, mudando completamente para cor indicada.
Par�metros:
cor (entrada, passagem por valor): indica a cor que deve ser usada durante a pintura completa do bitmap offscreen.
********************************/
void PintaFundoOffScreen(PIG_Cor cor)
{
    jogo->PintaFundoOffScreen(cor);
}

/********************************
A fun��o DesenhaRetanguloOffScreen() � respons�vel por desenhar um ret�ngulo cem preenchimento s�lido no bitmap offscreen em uma posi��o desejada pelo usu�rio.
O sistema de coordenadas � o mesmo da tela, com o eixo Y aumentando para cima.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o preenchimento do ret�ngulo;
********************************/
void DesenhaRetanguloOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor)
{
    jogo->DesenhaRetanguloOffScreen(x1,y1,altura,largura,cor);
}

/********************************
A fun��o DesenhaRetanguloVazadoOffScreen() � respons�vel por desenhar um ret�ngulo sem preenchimento no bitmap offscreen em uma posi��o desejada pelo usu�rio.
O sistema de coordenadas � o mesmo da tela, com o eixo Y aumentando para cima.
Par�metros:
posicaoX (entrada, passagem por valor): Valor da coordenada X onde o usu�rio deseja colocar o ret�ngulo.
posicaoY (entrada, passagem por valor): Valor da coordenada Y onde o usu�rio deseja colocar o ret�ngulo.
altura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � altura desse ret�ngulo.
largura (entrada, passagem por valor): Valor onde o usu�rio ir� fornecer o n�mero correspondente em pixels � largura desse ret�ngulo.
cor (entrada, passagem por valor): indica a cor no sistema RGB para a borda do ret�ngulo;
********************************/
void DesenhaRetanguloVazadoOffScreen(int x1,int y1,int altura,int largura,PIG_Cor cor)
{
    jogo->DesenhaRetanguloVazadoOffScreen(x1,y1,altura,largura,cor);
}

/********************************
A fun��o DesenhaLinhasSimplesOffScreen() � respons�vel por desenhar no bitmap offscreen uma �nica linha, cuja in�cio � o ponto (x1,y1) e o fim � o ponto (x2,y2).
Par�metros:
pontoX1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo X.
pontoY1 (entrada, passagem por valor): inteiro que indica o in�cio da linha no eixo Y.
pontoX2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo X.
pontoY2 (entrada, passagem por valor): inteiro que indica o fim da linha no eixo Y.
cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho das linhas;
********************************/
void DesenhaLinhaSimplesOffScreen(int x1,int y1,int x2,int y2,PIG_Cor cor)
{
    jogo->DesenhaLinhaOffScreen(x1,y1,x2,y2,cor);
}

/********************************
Se��o de fontes
********************************/

/********************************
A fun��o CriaFonteNormal() � respons�vel por disponibilizar uma nova fonte com preenchimento s�lido.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
corLetra (entrada, passagem por valor): representa a cor de preenchimento da fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para it�lico;
ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteNormal(char *nome,int tamanho,PIG_Cor corLetra,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=ESTILO_NORMAL)
{
    return jogo->CriaFonteNormal(nome,tamanho,estilo,corLetra,contorno,corContorno);
}

/********************************
A fun��o CriaFonteFundo() � respons�vel por disponibilizar uma nova fonte com preenchimento de um bitmap espec�fico.
Par�metros:
nome (entrada, passagem por refer�ncia): nome do arquivo que cont�m a fonte (normalmente com extens�o ttf).
tamanho (entrada, passagem por valor): tamanho da fonte, que normalmente representa a altura m�dia (em pixels) dos caracteres da fonte.
arquivoFundo (entrada, passagem por refer�ncia): indica o nome do arquivo de imagem que servir� de fundo para a fonte.
contorno (entrada, passagem por valor): representa a espessura do contorno que fonte ter�. Caso n�o seja desejado um contorno, basta utilizar um valor 0.
corContorno (entrada, passagem por valor): representa a cor do contorno da fonte.
estilo (entrada, passagem por valor): representa o estilo da fonte. Pode ser uma combina��o bin�ria de: ESTILO_NEGRITO, para negrito; ESTILO_SUBLINHADO, para sublinhado; ESTILO_ITALICO, para it�lico;
ESTILO_CORTADO, para uma linha horizontal � meia-altura. Caso nenhum estilo seja desejado, pode ser omitido ou usado ESTILO_NORMAL.
retono:
inteiro que representa a ideintifica��o �nica da fonte. Futuras refer�ncia a esta fonte devem idenitific�-las pelo n�mero.
********************************/
int CriaFonteFundo(char *nome,int tamanho,char *arquivoFundo,int contorno,PIG_Cor corContorno,PIG_Estilo estilo=ESTILO_NORMAL)
{
    return jogo->CriaFonteFundo(nome,tamanho,estilo,arquivoFundo,contorno,corContorno);
}

/********************************
A fun��o CalculaLarguraPixels() por realizar a soma das larguras de cada letra da string informada.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
retorno:
inteiro que representa o total de pixels (no eixo x) necess�rios para escrever a string.
********************************/
int CalculaLarguraPixels(char *str,int numFonte=0)
{
    return jogo->GetLarguraPixels(str);
}

/********************************
A fun��o EscreverDireita() � respons�vel por exibir uma string na tela de jogo, com alinhamento � direita do valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
********************************/
void EscreverDireita(char *str,int posicaoX,int posicaoY,int numFonte=0)
{
    jogo->EscreverDireita(str,posicaoX,posicaoY,numFonte);
}

/********************************
A fun��o EscreverEsquerda() � respons�vel por exibir uma string na tela de jogo, com alinhamento � esquerda do valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
********************************/
void EscreverEsquerda(char *str,int posicaoX,int posicaoY,int numFonte=0)
{
    jogo->EscreverEsquerda(str,posicaoX,posicaoY,numFonte);
}

/********************************
A fun��o EscreverCentralizada() � respons�vel por exibir uma string na tela de jogo, com alinhamento em rela��o ao valor de X.
Par�metros:
str (entrada, passagem por refer�ncia): string a ser escrita na tela.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja come�ar a escrever a string.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja come�ar a escrever a string.
numFonte (entrada, passagem por valor): n�mero da fonte a ser utilizada. Caso o usu�rio n�o deseje uma fonte especial, ser� utilizada a fonte padr�o (numeroFonte=0, tipo=Arial, tamanho=36, cor = Branco).
********************************/
void EscreverCentralizada(char *str,int posicaoX,int posicaoY,int numFonte=0)
{
    jogo->EscreverCentralizada(str,posicaoX,posicaoY,numFonte);
}

/********************************
Se��o de objetos
********************************/

/********************************
A fun��o CriaObjeto() � respons�vel por criar um objeto. Qualquer objeto que for necess�rio,
pode ser criado atrav�s dessa fun��o. O objeto ainda n�o ser� desenhado, apenas criado dentro do jogo.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo da imagem do objeto a ser criado.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255. O valor padr�o � 255, indicando n�vel m�ximo de opacidade.
Retorno:
inteiro que representa o identificador �nico do objeto. Todas as opera��es subsequentes com este objeto dever�o receber este identificador como par�metro.
********************************/
int CriaObjeto(char* nomeArquivo,int retiraFundo=1,int opacidade=255)
{
    return CGerenciadorObjetos::CriaObjeto(0,0,nomeArquivo,retiraFundo,opacidade);
}

/********************************
A fun��o DestroiObjeto() � respons�vel por eliminar o objeto em quest�o do jogo.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser exclu�do.
********************************/
void DestroiObjeto(int id_objeto)
{
    CGerenciadorObjetos::DestroiObjeto(id_objeto);
}

/********************************
A fun��o SetValorIntObjeto() � respons�vel incorporar a um objeto um atributo inteiro.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorIntObjeto(int id_objeto,int indice,int valor)
{
    CGerenciadorObjetos::SetValorIntObjeto(id_objeto,indice,valor);
}

/********************************
A fun��o SetValorFloatObjeto() � respons�vel incorporar a um objeto um atributo float.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloatObjeto(int id_objeto,int indice,int valor)
{
    CGerenciadorObjetos::SetValorFloatObjeto(id_objeto,indice,valor);
}

/********************************
A fun��o GetValorIntObjeto() � respons�vel recuperar o valor de um atributo int relacionado a um objeto.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
Retorno:
Retorna o valor do atributo int solicitado pelo usu�rio.
********************************/
int GetValorIntObjeto(int id_objeto,int indice)
{
    return CGerenciadorObjetos::GetValorIntObjeto(id_objeto,indice);
}

/********************************
A fun��o GetValorFloatObjeto() � respons�vel recuperar o valor de um atributo float relacionado a um objeto.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
Retorno:
Retorna o valor do atributo float solicitado pelo usu�rio.
********************************/
float GetValorFloatObjeto(int id_objeto,int indice)
{
    return CGerenciadorObjetos::GetValorFloatObjeto(id_objeto,indice);
}

/********************************
A fun��o GetXYObjeto() � respons�vel recuperar o valor da posi��o (X,Y) do objeto de acordo com o sistema de coordenadas do jogo.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X do objeto.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y do objeto.
********************************/
void GetXYObjeto(int id_objeto,int *posicaoX,int *posicaoY)
{
    CGerenciadorObjetos::GetPosicaoXY(id_objeto,posicaoX,posicaoY);
}

/********************************
A fun��o MoveObjeto() � respons�vel por movimentar um determinado obeto para uma nova posi��o informada.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser movido.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar o objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar o objeto.
********************************/
void MoveObjeto(int id_objeto,int posicaoX,int posicaoY)
{
    CGerenciadorObjetos::Move(id_objeto,posicaoX,posicaoY);
}

/********************************
A fun��o SetAnguloObjetoo() � respons�vel pela angula��o de determinado objeto. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O objeto ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaObjeto(). A detec��o de colis�o n�o funciona com objetos fora da angula��o padr�o (0 graus).
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
angulo (entrada, passagem por valor): valor para indicar a angula��o do objeto em graus.
********************************/
void SetAnguloObjeto(int id_objeto, float angulo)
{
    CGerenciadorObjetos::SetAngulo(id_objeto,angulo);
}

/********************************
A fun��o GetAnguloObjeto() � respons�vel por recuperar o �ngulo de rota��o de determinado objeto. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). O objeto ser� desenhado com a angula��o informada no pr�ximo comando
DesenhaObjeto(). A detec��o de colis�o n�o funciona com objetos fora da angula��o padr�o (0 graus).
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
float GetAnguloObjeto(int id_objeto)
{
    return CGerenciadorObjetos::GetAngulo(id_objeto);
}

/********************************
A fun��o SetPivoObjeto() define um ponto (X,Y) em rela��o ao ponto (0,0) do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do objeto.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do objeto.
********************************/
void SetPivoObjeto(int id_objeto,int posicaoX,int posicaoY)
{
    CGerenciadorObjetos::SetPivo(id_objeto,posicaoX,posicaoY);
}

/********************************
A fun��o GetPivoObjeto() define um ponto (X,Y) em rela��o ao ponto (0,0) do objeto, sobre o qual o objeto ser�
rotacionado quando a fun��o SetAnguloObjeto() for executada.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) do objeto.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) do objeto.
********************************/
void GetPivoObjeto(int id_objeto,int *posicaoX,int *posicaoY)
{
    CGerenciadorObjetos::GetPivo(id_objeto,posicaoX,posicaoY);
}

/********************************
A fun��o SetFlipObjeto() � respons�vel por virar o objeto, invertendo-o em alguma dire��o. O objeto somente ser�
desenhado na nova orienta��o no pr�ximo comando DesenhaObjeto().
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de invers�o),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void SetFlipObjeto(int id_objeto,PIG_Flip valor)
{
    CGerenciadorObjetos::SetFlip(id_objeto,valor);
}

/********************************
A fun��o GetFlipObjeto() � respons�vel por recuperar o valor da manipula��o causada pela fun��o SetFlipObjeto().
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser virado.
Retorno:
inteiro que indica o tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de invers�o),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
PIG_Flip GetFlipObjeto(int id_objeto)
{
    return CGerenciadorObjetos::GetFlip(id_objeto);
}

/********************************
A fun��o SetDimensoesObjeto() � respons�vel por delimitar a altura e a largura do objeto que ser� desenhado na tela,
independentemente do tamanho original do arquivo de imagem.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesObjeto(int id_objeto, int altura, int largura)
{
    CGerenciadorObjetos::SetDimensoes(id_objeto,altura,largura);
}

/********************************
A fun��o GetDimensoesObjeto() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar o objeto na tela. Em outras palavras, representa o tamanho atual do objeto.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
altura (sa�da, passagem por refer�ncia): altura atual em pixels do objeto.
largura (sa�da, passagem por refer�ncia): largura atual em pixels do objeto.
********************************/
void GetDimensoesObjeto(int id_objeto, int *altura, int *largura)
{
    CGerenciadorObjetos::GetDimensoes(id_objeto,altura,largura);
}

/********************************
A fun��o GetDimensoesOriginaisObjeto() � respons�vel por recuperar a altura e a largura originais da imagem
que foi usada para criar o objeto. Qualquer utiliza��o da fun��o SetDimensoesObjeto � ignorada para
o c�lculo desta fun��o.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
altura (sa�da, passagem por refer�ncia): altura original em pixels do objeto.
largura (sa�da, passagem por refer�ncia): largura original em pixels do objeto.
********************************/
void GetDimensoesOriginaisObjeto(int id_objeto, int *altura, int *largura)
{
    CGerenciadorObjetos::GetDimensoesOriginais(id_objeto,altura,largura);
}

/********************************
A fun��o DefineFrameObjeto() � respons�vel por delimitar o posicionamento dos pixels do arquivo de imagem que ser�o
utilizados para representar o objeto na tela. Desta forma, nem toda a imagem ser� automaticamente utilizada para
representar o objeto. O sistema de coordenadas deve ser o padr�o dos arquivos de imagem, com o eixo Y aumentando para baixo.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void DefineFrameObjeto(int id_objeto,int xBitmap, int yBitmap,int altura,int largura)
{
    CGerenciadorObjetos::CriaFrame(id_objeto,xBitmap,yBitmap,altura,largura);
}

/********************************
A fun��o SetColoracaoObjeto() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem.
Ap�s a modifica��o, todos os desenhos deste objeto ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoObjeto(int id_objeto,PIG_Cor cor)
{
    CGerenciadorObjetos::SetColoracao(id_objeto,cor);
}

/********************************
A fun��o SetOpacidadeObjeto() � respons�vel por modificar o n�vel de opacidade do objeto.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
valor (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255.
********************************/
void SetOpacidadeObjeto(int id_objeto,int valor)
{
    CGerenciadorObjetos::SetOpacidade(id_objeto,valor);
}

/********************************
A fun��o DesenhaObjeto() � respons�vel por desenhar um objeto na tela ou no Renderizador Offscreen. O objeto ser� desenhado de acordo com todas as defini��es
de posi��o e �ngulo informado at� o momento. Al�m disso, se o objeto estiver virado (flipping), isso tamb�m ser� levado em considera��o.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
offScreen (entrada, passagem por valor): indica se o objeto deve ser desenhado no Renderizador Offscreen.
********************************/
void DesenhaObjeto(int id_objeto,int offScreen=0)
{
    if (offScreen==0)
    CGerenciadorObjetos::Desenha(id_objeto,NULL);
    else CGerenciadorObjetos::Desenha(id_objeto,jogo->offRenderer);
}

/********************************
A fun��o TestaColisaoObjetos() � respons�vel por testar se dois objetos se colidiram ou n�o, ao passar
os identificadores dos objetos por par�metro.
Par�metros:
id_objeto1 (entrada, passagem por valor): identificador do primeiro objeto.
id_objeto2 (entrada, passagem por valor): identificador do segundo objeto.
Retorno:
Inteiro indicando se houve colis�o (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int TestaColisaoObjetos(int id_objeto1,int id_objeto2)
{
    return CGerenciadorObjetos::TestaColisao(id_objeto1,id_objeto2);
}

/********************************
A fun��o GetPixelsObjeto() � respons�vel por extrair os pixels da imagem que originou o objeto, devolvendo-os como
uma matriz de pixels (PIG_Cor). Mudan�as nessa matriz s� ser�o validadas ap�s a chamada da fun��o AtualizaPixelsObjeto().
O linha 0 corresponde � primeira linha da imagem, ou seja, � linha superior, pois o sistema de coordenadas
das imagens tem o eixo Y aumentando para baixo.
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
Retorno:
matriz de pixels (PIG_Cor) da imagem que gerou o objeto. O total de linhas da matriz � dado pela altura original do objeto e o
total de colunas � dado pela largura original do objeto. Ambos os valores podem ser obtidos pela fun��o GetDimensoesOriginaisObjeto().
********************************/
PIG_Cor **GetPixelsObjeto(int id_objeto)
{
    return CGerenciadorObjetos::GetPixels(id_objeto);
}

/********************************
A fun��o AtualizaPixelsObjeto() � respons�vel por efetivar quaisquer mudan�as nos pixels do objeto obtidos pela fun��o GetPixelsObjeto().
Par�metros:
id_objeto (entrada, passagem por valor): identificador do objeto.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255. O valor padr�o � 255, indicando n�vel m�ximo de opacidade.
********************************/
void AtualizaPixelsObjeto(int id_objeto,int retiraFundo=1,int opacidade=255)
{
    CGerenciadorObjetos::AtualizaPixels(id_objeto,retiraFundo,opacidade);
}

/********************************
Se��o de gerador de part�culas
********************************/

/********************************
A fun��o CriaGeradorParticulas() cria um novo gerador de part�culas (GDP). As part�culas em si precisam ser criadas
posteriormente atrav�s da fun��o Cria_Particula(), passando o identificador do GDP como par�metro.
Par�metros:
maxParticulas (entrada, passagem por valor): informa o maior n�mero de part�culas que o gerador ter� simultaneamente. O maior valor aceito � 1000 part�culas.
nomeArquivo (entrada, passagem por refer�ncia): indica o caminho relativo ou absoluto do arquivo de imagem,
 que ser� utilizado para cada part�cula do GDP.
********************************/
int CriaGeradorParticulas(int maxParticulas,char* nomeArquivo)
{
    return CGerenciadorParticulas::CriaGeradorParticulas(maxParticulas,nomeArquivo);
}

/********************************
A fun��o DestroiGeradorParticulas() encerra um gerador de part�culas (GDP). Todas as part�culas relacionadas a ele tamb�m s�o finalizadas
neste momento.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
********************************/
void DestroiGeradorParticulas(int id_gerador)
{
    CGerenciadorParticulas::DestroiGeradorParticulas(id_gerador);
}

/********************************
A fun��o MoveGeradorParticulas() reposiciona um gerador de part�culas (GDP). Na pr�tica, isto significa que as novas part�culas que
forem criadas posteriormente ter�o esse ponto de origem.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
posicaoX (entrada, passagem por valor): informa a nova posi��o X do GDP, em rela��o ao sistema de coordenadas do jogo.
posicaoY (entrada, passagem por valor): informa a nova posi��o Y do GDP, em rela��o ao sistema de coordenadas do jogo.
********************************/
void MoveGeradorParticulas(int id_gerador,int posicaoX,int posicaoY)
{
    CGerenciadorParticulas::Move(id_gerador,posicaoX,posicaoY);
}

/********************************
A fun��o MudaDirecao_Particulas() modifica a dire��o na qual as part�culas se movimentar�o ap�s serem criadas.
Somente as part�culas criadas posteriormente seguir�o a dire��o especificada.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
valorX (entrada, passagem por valor): informa a componente X da dire��o a ser definida para as part�culas.
valorY (entrada, passagem por valor): informa a componente Y da dire��o a ser definida para as part�culas.
********************************/
void MudaDirecaoParticulas(int id_gerador,int valorX,int valorY)
{
    CGerenciadorParticulas::MudaDirecaoParticulas(id_gerador,valorX,valorY);
}

/********************************
A fun��o CriaParticula() adiciona uma nova part�cula ao jogo relacionada com o GDP passado como par�metro.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
fadingOut (entrada, passagem por valor): valor l�gico que indica se a part�cula deve esmaecer ao longo do tempo.
minX (entrada, passagem por valor): valor m�nimo de X para que a part�cula seja considerada ativa
minY (entrada, passagem por valor): valor m�nimo de Y para que a part�cula seja considerada ativa
maxX (entrada, passagem por valor): valor m�ximo de X para que a part�cula seja considerada ativa
maxY (entrada, passagem por valor): valor m�ximo de Y para que a part�cula seja considerada ativa
maxTempo (entrada, passagem por valor): tempo de vida da part�cula
Retorno:
inteiro indicando se a part�cula foi criada (valor maior ou igual a zero) ou n�o (valor menor do que zero).
A part�cula n�o ser� criada se j� houver o n�mero m�ximo de part�culas ativas.
********************************/
int CriaParticula(int id_gerador,int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=999999.9)
{
    return CGerenciadorParticulas::CriaParticula(id_gerador,fadingOut,minX,minY,maxX,maxY,maxTempo);
}

/********************************
A fun��o MoveParticulas() faz com que todas as part�cula ativas do GDP em quest�o se movimentem de acordo com as componentes
X e Y passadas na fun��o MudaDirecao_Particulas(). As part�culas que sa�rem da tela de jogo ou aqueles que j� existerm a mais de 10000 segundos
ser�o consideradas inativas e deixar�o de existir.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
********************************/
void MoveParticulas(int id_gerador)
{
    CGerenciadorParticulas::MoveParticulas(id_gerador);
}

/********************************
A fun��o QuantidadeParticulasAtivas() indica quantas part�culas do GDP em quest�o ainda est�o ativas. As part�culas deixam de
ser ativas quando saem da tela do jogo, quando colidem com algum objeto ou depois de 10000 segundos de vida.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
Retorno:
inteiro que indica o n�mero de part�culas ativas.
********************************/
int QuantidadeParticulasAtivas(int id_gerador)
{
    return CGerenciadorParticulas::GetQtdAtivas(id_gerador);
}

/********************************
A fun��o DesenhaParticulas() desenha todas as part�culas ativas do GDP na posi��o que estiverem.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
********************************/
void DesenhaParticulas(int id_gerador)
{
    CGerenciadorParticulas::Desenha(id_gerador);
}

/********************************
A fun��o ColisaoParticulasObjeto() indica se houve colis�o de alguma part�cula ativa do GDP com um outro objeto espec�fico, atrav�s do seu identificador.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
id_objeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com as part�culas do GDP.
Retorno:
inteiro que indica se houve colis�o de alguma part�cula ativa do GDP (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int ColisaoParticulasObjeto(int id_gerador,int id_objeto)
{
    Objeto obj = CGerenciadorObjetos::GetObjeto(id_objeto);
    return CGerenciadorParticulas::Colisao(id_gerador,obj);
}

/********************************
A fun��o ColisaoParticulasAnimacao() indica se houve colis�o de alguma part�cula ativa do GDP com uma outra anim��o espec�fica, atrav�s do seu identificador.
Par�metros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da fun��o Cria_GeradorParticulas().
id_animacao (entrada, passagem por valor): identificador da anima��o que pode ter colidido com as part�culas do GDP.
Retorno:
inteiro que indica se houve colis�o de alguma part�cula ativa do GDP (valor diferente de zero) ou n�o (valor igual a 0, zero).
********************************/
int ColisaoParticulasAnimacao(int id_gerador,int id_animacao)
{
    Animacao anima = CGerenciadorAnimacoes::GetAnimacao(id_animacao);
    return CGerenciadorParticulas::Colisao(id_gerador,anima);
}

/********************************
Se��o dos temporizadores
********************************/

/********************************
A fun��o CriaTimer() � respons�vel por criar um timer (temporizador). Ap�s a cria��o o tempo decorrido
poder� ser obtido a partir da fun��o Tempo_Decorrido(), informando o identificador que � passado na resposta.
Retorno:
inteiro que identifica o timer criado.
********************************/
int CriaTimer()
{
    return CGerenciadorTimers::CriaTimer();
}

/********************************
A fun��o TempoDecorrido() � respons�vel por informar o tempo decorrido desde a cria��o do timer
at� a hora em que a fun��o for chamada.
Par�metros:
id_timer (entrada, passagem por valor): identificador do timer.
Retorno:
n�mero real indicando o tempo (em segundos) desde a cria��o do timer.
********************************/
float TempoDecorrido(int id_timer)
{
    return CGerenciadorTimers::GetTempoDecorrido(id_timer);
}

/********************************
A fun��o PausaTimer() � respons�vel por realizar uma pausa na contagem do tempo de um timer. Ap�s a despausa,
o timer continuar� a contar o tempo normalmente.
Par�metros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void PausaTimer(int id_timer)
{
    CGerenciadorTimers::PausaTimer(id_timer);
}

/********************************
A fun��o PausaTudo() � respons�vel por realizar uma pausa na contagem do tempo de todos os timers
criados pela fun��o CriaTimer();
********************************/
void PausaTudo()
{
    CGerenciadorTimers::PausaTodos();
}

/********************************
A fun��o DespausaTimer() � respons�vel por retomar a contagem do tempo de um timer ap�s uma pausa.
Par�metros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void DespausaTimer(int id_timer)
{
    CGerenciadorTimers::DespausaTimer(id_timer);
}

/********************************
A fun��o DespausaTudo() � respons�vel por retomar a contagem do tempo de todos os timers
criados pela fun��o CriaTimer();
********************************/
void DespausaTudo()
{
    CGerenciadorTimers::DespausaTodos();
}

/********************************
A fun��o ReiniciaTimer() � respons�vel por zerar a contagem do tempo de um timer, idependente do tempo j� decorrido.
Na pr�tica, � equivalente a encerrer um temporizador e recri�-lo em seguida.
Par�metros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void ReiniciaTimer(int id_timer)
{
    CGerenciadorTimers::ReiniciaTimer(id_timer);
}

/********************************
A fun��o DestroiTimer() � respons�vel por encerrar a utiliza��o de timer.
Seu identificador n�o poder� ser utilizado ap�s a fun��o ser executada.
Par�metros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void DestroiTimer(int id_timer)
{
    CGerenciadorTimers::DestroiTimer(id_timer);
}

/********************************
Se��o das anima��es
********************************/

/********************************
A fun��o CriaAnimacao() � respons�vel por criar uma animacao. A anima��o pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequ�ncia completa de
sprites � chamada de modo. Uma mesma anim��o pode apresentar v�rios modos diferentes.
Para que a anima��o funcione corretamente, ser� necess�rio: definir cada frame (peda�o do arquivo bitmap que cont�m o sprite desejado),
criar um ou mais modos, inserir os frames criados no modo correspondente e dizer qual modo dever� ser exibido inicialmente.
Tudo isso pode ser feito por outras fun��es que manipulam as anima��es.
Par�metros:
nomeArquivo (entrada, passagem por refer�ncia): string que informa o nome do arquivo da imagem (spritesheet) da anima��o.
retiraFundo (entrada, passagem por valor): inteiro que indica se o fundo da imagem deve ser retirado ou n�o ao ler o arquivo em quest�o. O valor padr�o � 1, indicando que o fundo deve ser retirado.
opacidade (entrada,passagem por valor): n�vel de opacidade do objeto na faixa 0-255. O valor padr�o � 255, indicando n�vel m�ximo de opacidade.
Retorno:
inteiro que representa o identificador �nico da anima��o. Todas as opera��es subsequentes com esta anima��o dever�o receber este identificador como par�metro.
********************************/
int CriaAnimacao(char* nomeArquivo,int retiraFundo=1,int opacidade=255)
{
    return CGerenciadorAnimacoes::CriaAnimacao(nomeArquivo,retiraFundo,opacidade);
}

/********************************
A fun��o CriaAnimacao() � respons�vel por criar uma animacao. A anima��o pode ser considerada um tipo especial
de objeto, capaz de mudar de figura (sprite) dentro de um tempo determinado. Uma sequ�ncia completa de
sprites � chamada de modo. Uma mesma anim��o pode apresentar v�rios modos diferentes.
Esta forma de criar uma anima��o, copia todos os frames e modos de outra anima��o j� existente, evitando assim
que toda esta prepara��o precise ser feita novamente. O usu�rio deve ter cuidado de n�o destruir a anima��o
original enquanto as c�pias estiverem ativas ou haver� erros de execu��o. Da mesma forma, n�o se deve alterar os
frames ou os modos da c�pia, pois pode provocar erros na anima��o original.
Par�metros:
id_animacao (entrada, passagem por valor): indica o identificador da anima��o original que ser� copiada.
Retorno:
inteiro que representa o identificador �nico da anima��o. Todas as opera��es subsequentes com esta anima��o dever�o receber este identificador como par�metro.
********************************/
int CriaAnimacao(int id_animacao)
{
    return CGerenciadorAnimacoes::CriaAnimacao(id_animacao);
}

/********************************
A fun��o DestroiAnimacao() � respons�vel por eliminar a anima��o em quest�o do jogo.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o a ser exclu�da.
********************************/
void DestroiAnimacao(int id_animacao)
{
    CGerenciadorAnimacoes::DestroiAnimacao(id_animacao);
}

/********************************
A fun��o CriaFrameAnimacao() � respons�vel por estabelecar uma parte do sprisheet da anima��o que cont�m um sprite espec�fico.
O frame criado deve ser posteriormente inserido em um ou mais modos da anima��o. O posicionamento do frame
respeita o sistema de coordenadas dos arquivos de imagem, com o eixo Y aumentando para baixo.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o a ter um novo frame.
codigo_frame (entrada, passagem por valor): numero do frame a ser criado. Pode ser usado qualquer n�mero de 0..MAX_FRAMES-1.
xBitmap (entrada, passagem por valor): indica a posi��o de eixo X onde come�a o frame.
yBitmap (entrada, passagem por valor): indica a posi��o de eixo Y onde come�a o frame. Neste caso, o eixo Y aumenta para baixo.
altura (entrada, passagem por valor): altura em pixels do frame.
largura (entrada, passagem por valor): largura em pixels do frame.
********************************/
void CriaFrameAnimacao(int id_animacao,int codigo_frame,int xBitmap,int yBitmap,int altura,int largura)
{
    CGerenciadorAnimacoes::CriaFrame(id_animacao,codigo_frame,xBitmap,yBitmap,altura,largura);
}

/********************************
A fun��o CriaModoAnimacao() � respons�vel por criar um modo, ou seja, uma sequ�ncia de sprites.
Ap�s a cria��o do modo, os frames deve ser inseridos um a um. O modo pode ser criado antes dos frames
e vice-versa, mas os frames s� podem ser associados ao modo, ap�s as respectivas cria��es.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o a ter um novo modo.
codigo_modo (entrada, passagem por valor): numero do modo a ser criado. Pode ser usado qualquer n�mero de 0..MAX_MODOS-1.
loop (entrada, passagem por valor): valor l�gico que indica se este modo deve recome�ar do primeiro frame ap�s a execu��o do �ltimo.
********************************/
void CriaModoAnimacao(int id_animacao,int codigo_modo,int loop)
{
    CGerenciadorAnimacoes::CriaModo(id_animacao,codigo_modo,loop);
}

/********************************
A fun��o InsereFrameAnimacao() � respons�vel por associar os frames aos modos correspondentes. Um mesmo
frame pode fazer parte de diversos modos, mas cada modo deve ter no m�ximo MAX_FRAMES_MODO-1 frames.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o em quest�o.
codigo_modo (entrada, passagem por valor): numero do modo a ter um frame inserido.
codigo_frame (entrada, passagem por valor): numero do frame a ser inserido no modo.
tempo (entrada, passagem por valor): dura��o (em segundos) da exibi��o autom�tica do frame neste modo espec�fico.
********************************/
void InsereFrameAnimacao(int id_animacao,int codigo_modo, int codigo_frame, float tempo)
{
    CGerenciadorAnimacoes::InsereFrame(id_animacao,codigo_modo,codigo_frame,tempo);
}

/********************************
A fun��o MudaModoAnimacao() � respons�vel por alterar a anima��o para um outro modo.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o em quest�o.
codigo_modo (entrada, passagem por valor): numero do novo modo.
inicia (entrada, passagem por valor): valor l�gico que indica se a novo modo deve come�ar do primeiro sprite (valor 1) ou do �ltimo sprite (valor 0).
********************************/
void MudaModoAnimacao(int id_animacao,int codigo_modo,int inicia)
{
    CGerenciadorAnimacoes::MudaModo(id_animacao,codigo_modo,inicia);
}

/********************************
A fun��o ColisaoAnimacoes() indica se houve colis�o entre duas anima��es, de forma semelhante aos objetos.
Par�metros:
id_animacao1 (entrada, passagem por valor): identificador da primeira anima��o.
id_animacao2 (entrada, passagem por valor): identificador da segunda anima��o.
Retorno:
inteiro que indica se houve colis�o entre as anima��es.
********************************/
int ColisaoAnimacoes(int id_animacao1,int id_animacao2)
{
    return CGerenciadorAnimacoes::ColisaoAnimacoes(id_animacao1,id_animacao2);
}

/********************************
A fun��o ColisaoAnimacaoObjeto() indica se houve colis�o de alguma animacao com algum outro objeto espec�fico, atrav�s do seu identificador.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o que pode ter colidido com o objeto.
id_objeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com a anima��o.
Retorno:
inteiro que indica se houve colis�o da anima��o com o objeto.
********************************/
int ColisaoAnimacaoObjeto(int id_animacao,int id_objeto)
{
    Objeto obj = CGerenciadorObjetos::GetObjeto(id_objeto);
    return CGerenciadorAnimacoes::ColisaoObjeto(id_animacao,obj);
}

/********************************
A fun��o DesenhaAnima��o() � respons�vel por desenhar uma anima��o na tela. A anima��o ser� desenhada de acordo com o modo atual da anima��o,
fazendo com que os frames sejam automaticamente ajustados de acordo com o tempo estipulado. Caso o modo atual esteja em loop, o primeiro frame ser�
desenhado novamente logo ap�s o t�rmino do �ltimo frame.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o a ser desenhada.
Retorno:
inteiro que indica se a anima��o encerrou ou n�o. O valor s� ser� diferente de zero, se o modo atual tamb�m n�o estiver em loop.
********************************/
int DesenhaAnimacao(int id_animacao)
{
    return CGerenciadorAnimacoes::Desenha(id_animacao);
}

/********************************
A fun��o MoveAnimacao() � respons�vel por movimentar uma determinada anima��o para uma nova posi��o informada.
Par�metros:
id_anima��o (entrada, passagem por valor): identificador da anima��o a ser movida.
posicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usu�rio deseja reposicionar a anima��o.
posicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usu�rio deseja reposicionar a anima��o.
********************************/
void MoveAnimacao(int id_animacao,int x,int y)
{
    CGerenciadorAnimacoes::Move(id_animacao,x,y);
}

/********************************
A fun��o SetOpacidadeAnimacao() � respons�vel por modificar o n�vel de opacidade da anima��o.
O n�vel de opacidade varia de 0-255, sendo 0 totalmente transparente e 255 totalmente opaco.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
valor (entrada,passagem por valor): n�vel de opacidade da anima��o na faixa 0-255.
********************************/
void SetOpacidadeAnimacao(int id_animacao,int valor)
{
    CGerenciadorAnimacoes::SetOpacidade(id_animacao,valor);
}

/********************************
A fun��o SetColoracaoAnimacao() � respons�vel por mesclar uma determinada cor com os pixels do arquivo de imagem.
Ap�s a modifica��o, todos os desenhos desta anima��o ser�o mostrados j� com a mesclagem definida.
Para voltar ao padr�o original de pixels, deve-se chamar a fun��o, passando a cor branca (255,255,255).
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void SetColoracaoAnimacao(int id_animacao,PIG_Cor cor)
{
    CGerenciadorAnimacoes::SetColoracao(id_animacao,cor);
}

/********************************
A fun��o SetAnguloAnimacao() � respons�vel pela angula��o de determinada animacao. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). A anima��o ser� desenhada com a angula��o informada no pr�ximo comando
DesenhaAnimcao(). A detec��o de colis�o n�o funciona com anima��es fora da angula��o padr�o (0 graus).
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
angulo (entrada, passagem por valor): valor para indicar a angula��o da anima��o em graus.
********************************/
void SetAnguloAnimacao(int id_animacao, float angulo)
{
    CGerenciadorAnimacoes::SetAngulo(id_animacao,angulo);
}

/********************************
A fun��o GetAnguloAnimacao() � respons�vel por recuperar o �ngulo de rota��o de determinada anima��o. A angula��o � calculada em sentido
hor�rio a partir do eixo X (0 graus). A anima��o ser� desenhada com a angula��o informada no pr�ximo comando
DesenhaAnimacao(). A detec��o de colis�o n�o funciona com anima��es fora da angula��o padr�o (0 graus).
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
Retorno:
Retorna o valor do �ngulo em graus.
********************************/
float GetAnguloAnimacao(int id_animacao)
{
    return CGerenciadorAnimacoes::GetAngulo(id_animacao);
}

/********************************
A fun��o SetPivoAnimacao() define um ponto (X,Y) em rela��o ao ponto (0,0) da anima��o, sobre o qual a anima��o ser�
rotacionado quando a fun��o SetAnguloAnimacao() for executada.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (entrada, passagem por valor): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da anima��o.
posicaoY (entrada, passagem por valor): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da anima��o.
********************************/
void SetPivoAnimacao(int id_animacao,int posicaoX,int posicaoY)
{
    CGerenciadorAnimacoes::SetPivo(id_animacao,posicaoX,posicaoY);
}

/********************************
A fun��o GetPivoAnimacao() define um ponto (X,Y) em rela��o ao ponto (0,0) da animacao, sobre o qual a anima��o ser�
rotacionado quando a fun��o SetAnguloAnimacao() for executada.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (sa�da, passagem por refer�ncia): Valor da coordenada X do piv� em rela��o ao ponto (0,0) da anima��o.
posicaoY (sa�da, passagem por refer�ncia): Valor da coordenada Y do piv� em rela��o ao ponto (0,0) da anima��o.
********************************/
void GetPivoAnimacao(int id_animacao,int *posicaoX,int *posicaoY)
{
    CGerenciadorAnimacoes::GetPivo(id_animacao,posicaoX,posicaoY);
}

/********************************
A fun��o SetDimensoesAnimacao() � respons�vel por delimitar a altura e a largura da anima��o que ser� desenhada na tela,
independentemente do tamanho original do arquivo de imagem.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
altura (entrada, passagem por valor): altura em pixels.
largura (entrada, passagem por valor): largura em pixels.
********************************/
void SetDimensoesAnimacao(int id_animacao, int altura, int largura)
{
    CGerenciadorAnimacoes::SetDimensoes(id_animacao,altura,largura);
}

/********************************
A fun��o GetDimensoesAnimacao() � respons�vel por recuperar a altura e a largura da �rea a ser usada
para desenhar a anima��o na tela. Em outras palavras, representa o tamanho atual da anima��o.
Par�metros:
id_objeto (entrada, passagem por valor): identificador da anima��o.
altura (sa�da, passagem por refer�ncia): altura atual em pixels da anima��o.
largura (sa�da, passagem por refer�ncia): largura atual em pixels da anima��o.
********************************/
void GetDimensoesAnimacao(int id_animacao, int *altura, int *largura)
{
    CGerenciadorAnimacoes::GetDimensoes(id_animacao,altura,largura);
}

/********************************
A fun��o SetValorIntAnimacao() � respons�vel incorporar a uma anima��o um atributo int.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo int a ser associado � anima��o.
********************************/
void SetValorIntAnimacao(int id_animacao,int indice,int valor)
{
    CGerenciadorAnimacoes::SetValorInt(id_animacao,indice,valor);
}

/********************************
A fun��o GetValorIntAnimacao() � respons�vel recuperar o valor de um atributo int relacionado a uma anima��o.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
Retorno:
Retorna o valor do atributo int solicitado pelo usu�rio.
********************************/
int GetValorIntAnimacao(int id_animacao,int indice)
{
    return CGerenciadorAnimacoes::GetValorInt(id_animacao,indice);
}

/********************************
A fun��o SetValorFloatAnimacao() � respons�vel incorporar a uma anima��o um atributo float.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): relaciona um n�mero inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado � anima��o.
********************************/
void SetValorFloatAnimacao(int id_animacao,int indice,float valor)
{
    CGerenciadorAnimacoes::SetValorFloat(id_animacao,indice,valor);
}

/********************************
A fun��o GetValorFloatAnimacao() � respons�vel recuperar o valor de um atributo float relacionado a uma anima��o.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
indice (entrada, passagem por valor): indica o n�mero do atributo que se deseja recuperar.
Retorno:
Retorna o valor do atributo float solicitado pelo usu�rio.
********************************/
float GetValorFloatAnimacao(int id_animacao,int indice)
{
    return CGerenciadorAnimacoes::GetValorFloat(id_animacao,indice);
}

/********************************
A fun��o GetXYAnimacao() � respons�vel recuperar o valor da posi��o (X,Y) da animacao de acordo com o sistema de coordenadas do jogo.
Par�metros:
id_animacao (entrada, passagem por valor): identificador da anima��o.
posicaoX (sa�da, passagem por referencia): indica a posicao no eixo X da anima��o.
posicaoY (sa�da, passagem por referencia): indica a posicao no eixo Y da anima��o.
********************************/
void GetXYAnimacao(int id_animacao,int *posicaoX,int *posicaoY)
{
    return CGerenciadorAnimacoes::GetPosicaoXY(id_animacao,posicaoX,posicaoY);
}

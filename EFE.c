#include "tela.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include <allegro5/allegro_primitives.h>

#define WIDTH_SCREEN 1920.0
#define HEIGHT_SCREEN 1080.0
#define TAMANHO_CELULA 144.0
#define turquesa 10
#define rosinha 11
#define coral 12
#define magenta 13
#define violeta 14
#define laranja_escuro 15
#define azul_ardosia 16
#define chocolate 17

typedef struct
{
    char matriz[5][5];
    int tecla;
    bool jogo_ativo;
    bool perdeu;
    bool ganhou;
    bool jogada_valida;
    bool quero_jogar;
    int linha;
    int coluna;
    char armazenado;
    int pontos;
} estado;

typedef struct
{
    char nomes[5][10];
    int pontos[10];
}top;

int randomiza_escolha(estado *jogo)
{
    jogo->linha = rand() % 5;
    jogo->coluna = rand() % 5;
    int cond = rand() % 4;
    while (jogo->matriz[jogo->linha][jogo->coluna] != ' ')
    {
        jogo->coluna = rand() % 5;
        jogo->linha = rand() % 5;
    }
    return cond;
}

void inicializa_matriz(char matriz[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matriz[i][j] = ' ';
        }
    }
}

void inicializa_cor()
{
    int fundo_turquesa = tela_cria_cor(0.25, 0.88, 0.82);
    int linha_rosa = tela_cria_cor(1.0, 0.41, 0.71);
    int A = tela_cria_cor(0.941, 0.502, 0.502);
    int B = tela_cria_cor(1.0, 0.0, 1.0);
    int C = tela_cria_cor(0.580, 0.000, 0.827);
    int D = tela_cria_cor(1.0, 0.549, 0.0);
    int E = tela_cria_cor(0.482, 0.408, 0.933);
    int F = tela_cria_cor(0.824, 0.412, 0.118);
}

void gera_letra(estado *jogo)
{
    int cond = randomiza_escolha(jogo);
    if (cond > 0) jogo->matriz[jogo->linha][jogo->coluna] = 'A';
    else if (cond == 0) jogo->matriz[jogo->linha][jogo->coluna] = 'B';
}

void inicializa_tabuleiro(estado *jogo)
{
    inicializa_matriz(jogo->matriz);
    for (int i = 0; i < 2; i++)
    {
        gera_letra(jogo);
    }
}

void inicializa_jogo(estado* jogo)
{
    jogo->ganhou = false;
    jogo->perdeu = false;
    jogo->jogo_ativo = true;
    jogo->tecla = c_none;
    jogo->pontos = 0;
    inicializa_tabuleiro(jogo);
}

void desenha_pontos(int pontuacao)
{
    char txtpontos[10];
    snprintf(txtpontos, 10, "%d", pontuacao);
    tela_texto(WIDTH_SCREEN /2, 100, 100, preto, txtpontos);
    

}

void desenha_fundo(int cor)
{
    tela_retangulo(0,0,WIDTH_SCREEN, HEIGHT_SCREEN, 5, preto, cor); 
}

void desenha_top5_telaFULL(top tp5)
{
    double ini = relogio() + 3;
    double tempo_tela = ini - relogio();
    do
    {
        tempo_tela = ini - relogio();
        desenha_fundo(coral);
        char txt[6];
        snprintf(txt,6,"TOP 5");
        tela_texto(WIDTH_SCREEN / 2, 100, 70, preto, txt);
        char tempo[5];
        snprintf(tempo, 5, "%.1f", tempo_tela);
        tela_texto(WIDTH_SCREEN / 2, 150, 30, preto, tempo);
        for (int i = 0; i < 5; i++)
        {
            char pontos[10];
            snprintf(pontos, 10, "%d", tp5.pontos[i]);
            tela_texto_esq(WIDTH_SCREEN / 2, 300 + 100 * i, 30, preto, tp5.nomes[i]);
            tela_texto_dir(WIDTH_SCREEN / 2 + 100, 300 + 100 * i, 30, preto, pontos);
        }
        tela_atualiza(); 
    } while (tempo_tela > 0);
}

void desenha_janela_top5(top tp5)
{
    tela_retangulo(WIDTH_SCREEN*3/4, HEIGHT_SCREEN/2, WIDTH_SCREEN, HEIGHT_SCREEN, 10, preto, rosinha);
    for (int i = 0; i < 5; i++)
    {
        char pontos[10];
        snprintf(pontos,10,"%d",tp5.pontos[i]);
        tela_texto_esq(WIDTH_SCREEN * 5 / 6 + 100,30 + HEIGHT_SCREEN / 2 + 100 * i, 30, preto, tp5.nomes[i]);
        tela_texto_dir(WIDTH_SCREEN * 5 / 6 + 160,30 + HEIGHT_SCREEN / 2 + 100 * i, 30, preto, pontos);
    }
}

void desenha_tela_final()
{
    desenha_fundo(magenta);
    char txt[25];
    char txt2[17];
    char o[2];
    char txt3[15];
    char x[2];
    snprintf(txt,25,"DESEJA JOGAR NOVAMENTE?");
    snprintf(o,2,"O");
    snprintf(txt2, 17, "PRESSIONE ENTER");
    snprintf(x, 2, "X");
    snprintf(txt3, 15, "PRESSIONE ESC");
    tela_texto(WIDTH_SCREEN/2,HEIGHT_SCREEN/2, 50, preto, txt);
    tela_texto(WIDTH_SCREEN / 2 - 220, HEIGHT_SCREEN / 2 + 70, 30, verde, o);
    tela_texto(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2 + 70, 30, preto, txt2);
    tela_texto(WIDTH_SCREEN / 2 - 190, HEIGHT_SCREEN / 2 + 110, 30, vermelho, x);
    tela_texto(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2 + 110, 30, preto, txt3);
    tela_atualiza();
}

void desenha_nome_na_tela(char nome[])
{
    desenha_fundo(laranja_escuro);
    char txt[20];
    snprintf(txt, 20, "DIGITE SEU NOME:");
    tela_texto(WIDTH_SCREEN / 2, 100, 50, preto,txt);
    tela_retangulo(WIDTH_SCREEN/3, HEIGHT_SCREEN/2 - 50, WIDTH_SCREEN*3/4 - 200, HEIGHT_SCREEN/2 + 50, 3, preto, chocolate);
    tela_texto(WIDTH_SCREEN/2, HEIGHT_SCREEN / 2, 50, preto, nome);
    tela_atualiza();
}

void desenha_letra(int x, int y, int j, int i, char txt[])
{
    tela_texto(x + (TAMANHO_CELULA / 2 + TAMANHO_CELULA * j),y + (TAMANHO_CELULA / 2 + TAMANHO_CELULA * i ), 30, (int)txt[0] - 53, txt);
}

void desenha_tabuleiro(char matriz[5][5])
{
    int posx = (WIDTH_SCREEN - TAMANHO_CELULA*5) / 2;
    int posy = (HEIGHT_SCREEN - TAMANHO_CELULA*5) / 2;
    char txt[2];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            snprintf(txt,2,"%c", matriz[i][j]);
            tela_retangulo(posx + (j * TAMANHO_CELULA), posy + (i * TAMANHO_CELULA),posx + ((j + 1) * TAMANHO_CELULA),posy + ((i + 1) * TAMANHO_CELULA), 5, rosinha, turquesa);
            desenha_letra(posx, posy, j, i, txt);
        }

    }

}

void desenha_mouse()
{
    tela_circulo(tela_rato_x(), tela_rato_y(), 5, 0.5, preto, preto);
}

void desenha_vitoria()
{
    char txt[20];
    snprintf(txt, 20, "VOCE GANHOU");
    tela_texto(WIDTH_SCREEN/2, HEIGHT_SCREEN/2, 100, verde, txt);
}

void desenha_derrota()
{
    char txt[20];
    snprintf(txt, 20, "VOCE PERDEU");
    tela_texto(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 100, vermelho, txt);
}

void desenha_jogo(estado jogo, top tp5)
{
    desenha_fundo(azul_ardosia);
    desenha_tabuleiro(jogo.matriz);
    desenha_pontos(jogo.pontos);
    if (jogo.ganhou == true)
    {
        desenha_vitoria(tp5);
    }
    else if (jogo.perdeu == true)
    {
        desenha_derrota();
    }
    desenha_janela_top5(tp5);
    desenha_mouse();
    tela_atualiza();
}

bool para_tras(int tecla)
{
    if (tecla == c_up || tecla == c_left)
        return true;
    else
        return false;
}

bool para_frente(int tecla)
{
    if (tecla == c_down || tecla == c_right)
        return true;
    return false;
}

bool para_cima_baixo(int tecla)
{
    if (tecla == c_up || tecla == c_down)
        return true;
    return false;
}

bool para_lado(int tecla)
{
    if (tecla == c_left || tecla == c_right)
        return true;
    return false;
}

bool vazio(estado jogo)
{
    if (jogo.matriz[jogo.linha][jogo.coluna] == ' ') return true;
    else return false;
}

bool iguais(estado jogo)
{
    if (jogo.armazenado == jogo.matriz[jogo.linha][jogo.coluna])
        return true;
    return false;
}

bool ganhou(int letra)
{
    if (letra == 'F')
        return true;
    return false;
}

bool dentro_do_tabuleiro(int linha)
{
    if (linha <= 4 && linha >= 0)
        return true;
    return false;
}

bool ocorre_jogada(int aux, int linha)
{
    if (aux > 0 && dentro_do_tabuleiro(linha))
        return true;
    return false;
}

bool pode_juntar(estado jogo, int aux)
{
    if (aux == 3 && jogo.armazenado >= 65)
        return true;
    return false;
}

bool tela_final()
{
    int tecla = c_none;
    while (tecla != c_enter && tecla != c_esc)
    {
        tecla = tela_tecla();
        desenha_tela_final();
    }
    if (tecla == c_enter)
        return true;
    return false;
}

bool quero_jogar()
{
    return tela_final();
}

bool ainda_jogando(estado jogo)
{
    if (jogo.ganhou == true || jogo.perdeu == true)
        return false;
    return true;
}

void modifica_celula(estado *jogo, int aux, int dir)
{
    jogo->matriz[jogo->linha - (aux * dir)][jogo->coluna] = jogo->matriz[jogo->linha][jogo->coluna];
    jogo->matriz[jogo->linha][jogo->coluna] = ' ';
}

void valida_jogada(estado *jogo)
{
    jogo->jogada_valida = true; 
}

void incrementa_ponto(estado *jogo)
{
    jogo->pontos++; 
}

void move_coluna(estado* jogo)
{
    for (jogo->coluna = 0; jogo->coluna < 5; jogo->coluna++)
    {
        for (int i = 0; i < 4; i++)
        {
            int dir = 0;
            int ini = 0;
            if (para_tras(jogo->tecla))
            {
                dir = 1;
                ini = 0;
            }
            else
            {
                dir = -1;
                ini = 4;
            }
            jogo->linha = ini + (i*dir);
            int AUX = 0;
            while (vazio(*jogo) && dentro_do_tabuleiro(jogo->linha))
            {
                jogo->linha += dir;
                AUX++;
            }
            if (ocorre_jogada(AUX, jogo->linha))
            {
                modifica_celula(jogo, AUX, dir);
                valida_jogada(jogo);
                incrementa_ponto(jogo);
            }
        }
    }
}

void tranpoe(char matriz[5][5])
{
    char matriz_aux[5][5];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matriz_aux[j][i] = matriz[i][j];
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matriz[i][j] = matriz_aux[i][j];
        }
    }
}

void move_linha(estado* jogo)
{
    tranpoe(jogo->matriz);
    move_coluna(jogo);
    tranpoe(jogo->matriz);
}

void condicao_de_mov(estado* jogo)
{
    if (para_cima_baixo(jogo->tecla))
        move_coluna(jogo);
    else
        move_linha(jogo);
}

void pontua_juncao(estado *jogo)
{
    jogo->pontos = jogo->pontos + (jogo->armazenado - 64) * 10;
}

void junta_letra(estado* jogo)
{   
    int i = jogo->linha;
    while (i >= jogo->linha - 2 && i <= jogo->linha + 2)
    {
        if (i != jogo->linha - 2 && i != jogo->linha + 2)
            jogo->matriz[i][jogo->coluna] = ' ';
        else
            jogo->matriz[i][jogo->coluna] = jogo->armazenado + 1;
        if (para_tras(jogo->tecla))
            i--;
        else
            i++;
    }
    pontua_juncao(jogo);
    if (jogo->ganhou == false)
        jogo->ganhou = ganhou(jogo->armazenado +1);
}

int verifica_juncao(estado *jogo)
{   
    int aux = 1;
    int ini = 0;
    int dir = 0;
    if (para_tras(jogo->tecla))
    {
        ini = 0;
        dir = 1;
    }
    else
    {
        ini = 4;
        dir = -1;
    }
    jogo->armazenado = jogo->matriz[ini][jogo->coluna];
    jogo->linha = ini + dir;
    while (dentro_do_tabuleiro(jogo->linha))
    {
        if (iguais(*jogo))
            aux++;
        else if (!vazio(*jogo))
        {
            aux = 1;
            jogo->armazenado = jogo->matriz[jogo->linha][jogo->coluna];
        }
        if (pode_juntar(*jogo, aux))
            break;
        jogo->linha+=dir;

    }
    return aux;
}

void juncao(estado* jogo)
{
    if (para_lado(jogo->tecla))
        tranpoe(jogo->matriz);
    for ( jogo->coluna = 0; jogo->coluna < 5; jogo->coluna++)
    {
        int aux = verifica_juncao(jogo);
        if (aux == 3)
            junta_letra(jogo);
    }
    if (para_lado(jogo->tecla))
        tranpoe(jogo->matriz);
}

void verifica_se_perde(estado* jogo)
{
    int aux = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (jogo->matriz[i][j] == ' ')
            {
                aux++; 
            }
        }
    }
    if (aux == 0) 
    {
        jogo->perdeu = true;
        for (int i = 0; i < 2; i++)
        {
            if (i == 0)
                jogo->tecla = c_down;
            else
                jogo->tecla = c_right;
            int aux2 = verifica_juncao(jogo);
            if (aux2 == 3)
                jogo->perdeu = false;
        }
    }

}

void move_tabuleiro(estado* jogo)
{
    jogo->jogada_valida = false;
    for (int i = 0; i < 2; i++)
    {
        condicao_de_mov(jogo);
        juncao(jogo);
    }
    condicao_de_mov(jogo);

}

void inicializa_top5(top *tp5)
{
    for (int i = 0; i < 5; i++)
    {
        tp5->nomes[i][0] = '_';
        tp5->nomes[i][1] = '\0';
        tp5->pontos[i] = 0;
    }
}

void pegar_nome(char nome[])
{
    int i = 0;
    int tecla = c_none;
    while (tecla != c_enter)
    {
        desenha_nome_na_tela(nome);
        tecla = tela_tecla();

        if (tecla >= 'a' && tecla <= 'z' || tecla >= 'A' && tecla >= 'Z' || tecla >= '0' && tecla <= '9')
        {
            if (i <= 8)
            {
                nome[i] = tecla;
                i++;
            }
        }
        else if (tecla == c_back && i > 0)
        {
            nome[i-1] = '\0';
            i--;
        }
    }
}

void escreve_top5(top tp5)
{
    FILE* arq;
    arq = fopen("top5.txt", "w");
    for (int i = 0; i < 5; i++)
    {
        fprintf(arq, "%s %d\n", tp5.nomes[i], tp5.pontos[i]);
    }
    fclose(arq);
}

void cria_arq(top tp5)
{
    escreve_top5(tp5);
}

void le_top5(top *tp5)
{
    FILE* arq;
    int i=0;
    arq = fopen("top5.txt", "r");
    if (arq == NULL)
    {
        cria_arq(*tp5);
    }


    else
    {
        while (!feof(arq))
        {
            fscanf(arq, " %s", tp5->nomes[i]);
            if (fscanf(arq, " %d", &tp5->pontos[i]) == 1)
                i++;
        }
        fclose(arq);
    }
}

void coloca_no_top5(char nome[], int pontos, top *tp5, int i2)
{
    for (int i = 4; i >= i2; i--)
    {
        if (i == i2)
        {
            strcpy(tp5->nomes[i], nome);
            tp5->pontos[i] = pontos;
        }
        else
        {
            strcpy(tp5->nomes[i], tp5->nomes[i - 1]);
            tp5->pontos[i] = tp5->pontos[i-1];
        }
    }
}

bool dentro_top5(int ponto, top *tp5)
{
    char nome[10] = {" "};
    int i2 = 5;
    for (int i = 4; i >= 0; i--)
    {
        if (ponto > tp5->pontos[i])
            i2--;
        else
            break;
    }
    if (i2 != 5)
    {
        pegar_nome(nome);
        coloca_no_top5(nome,ponto,tp5,i2);
        return true;
    }
    else
        return false;
}

void processa_top5(top *tp5,int pontos)
{
    inicializa_top5(tp5);
    le_top5(tp5);
    if (dentro_top5(pontos, tp5))
        escreve_top5(*tp5);
}

void processa_partida(estado *jogo, top tp5)
{
    while (jogo->tecla != c_esc && jogo->jogo_ativo == true)
    {
        jogo->tecla = tela_tecla();
        desenha_jogo(*jogo, tp5);
        if (para_cima_baixo(jogo->tecla) || para_lado(jogo->tecla))
        {
            move_tabuleiro(jogo);
            if (jogo->jogada_valida)
                gera_letra(jogo);
            verifica_se_perde(jogo);
        }
        jogo->jogo_ativo = ainda_jogando(*jogo);
    }
}

void fim_partida(estado *jogo, top *tp5)
{
    if (!jogo->jogo_ativo)
    {
        desenha_jogo(*jogo, *tp5);
        al_rest(1.0);
        processa_top5(tp5, jogo->pontos);
        desenha_top5_telaFULL(*tp5);
    }
}

void partida()
{
    srand(time(0));
    estado jogo;
    top tp5;
    inicializa_cor();
    inicializa_jogo(&jogo);
    processa_top5(&tp5, jogo.pontos);
    processa_partida(&jogo, tp5);
    fim_partida(&jogo,&tp5);
}


int main()
{
    tela_inicio(WIDTH_SCREEN, HEIGHT_SCREEN, "EFE");
    do
    {
        partida();
    } while (quero_jogar());
    tela_fim();
    return 0;
}

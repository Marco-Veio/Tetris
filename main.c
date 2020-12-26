#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "rlutil.h"

#define l 25
#define c 14
#define p 4
#define nome "recordes.sav"

typedef struct quadradorado{
    int cor,movimento;
}quadrado;

int menu(int tam,char frase[],char opcoes[],int frasenum,char simbolo1,char simbolo2,int cor_padrao,int cor_selecionada,int cor_simbolos){
    setCursorVisibility(0);
    int i,j,e=0;
    char escolha[tam][2],mov;
    do{
        system("cls");
        for (i=0;i<tam;i++){
            escolha[i][0]=' ';
            escolha[i][1]=' ';
        }
        escolha[e][0]=simbolo1;
        escolha[e][1]=simbolo2;
        setColor(cor_padrao);
        printf("%s\n",frase);
        if(!frasenum){
            for(i=0,j=0;opcoes[i]!=0;i++,j++){
                setColor(cor_simbolos);
                printf("%c ",escolha[j][0]);
                if(escolha[j][0]!=' ')
                    setColor(cor_selecionada);
                else
                    setColor(cor_padrao);
                for(;opcoes[i]!='|';i++)
                    printf("%c",opcoes[i]);
                setColor(cor_simbolos);
                printf(" %c \n",escolha[j][1]);
            }
        }else{
            for(i=0;i<tam;i++){
                setColor(cor_simbolos);
                printf("%c ",escolha[i][0]);
                if(escolha[i][0]!=' ')
                    setColor(cor_selecionada);
                else
                    setColor(cor_padrao);
                printf("%d ",i+1);
                setColor(cor_simbolos);
                printf("%c\n",escolha[i][1]);
            }
        }
        setColor(cor_padrao);
        do{
            do{
                mov=getch();
            }while(mov!=-32 && mov!='w' && mov!='s' && mov!=13 && mov!=27 && mov!=8 &&(mov<'1' && mov>tam+48));
            if(mov==-32)
                mov=getch();
        }while(mov!='H' && mov!='P' && mov!='w' && mov!='s' && mov!=13 && mov!=27 && mov!=8 &&(mov<'1' && mov>tam+48));
        if(tam<10 && mov>='1' && mov<=tam+48)
            e=mov-49;
        switch(mov){
            case 'w':
            case 'H':if(e>0) e--;else e=tam-1;break;
            case 's':
            case 'P':if(e<tam-1) e++;else e=0;break;
            case 27:return -1;break;
            case 8:return -2;break;
        }
    }while(mov!=13);
    system("cls");
    return e;
}

void listar_recordes(int r[]){
    FILE *fp=fopen(nome,"rb");
    fread(r,sizeof(int),10,fp);
    int i;
    for(i=0;i<10;i++)
        printf("%d - %d\n",i+1,r[i]);
    fclose(fp);
}
void resetar_recordes(int r[]){
    FILE *fp=fopen(nome,"wb");
    int i;
    for(i=0;i<10;i++)
        r[i]=0;
    fwrite(r,sizeof(int),10,fp);
    fclose(fp);
}
void adicionar_recorde(int r[],int novo){
    listar_recordes(r);
    FILE *fp=fopen(nome,"wb");
    r[10]=novo;
    int j,temp=r[10];
    for(j=9;j>=0 && temp>r[j];j--)
        r[j+1]=r[j];
    r[j+1]=temp;
    fwrite(r,sizeof(int),10,fp);
    fclose(fp);
}

void iniciar_campo(quadrado campo[l][c]){
    int i,j;
    for(i=0;i<l-1;i++)
        for(j=0;j<c;j++)
            if(j==0 || j==c-1){
                campo[i][j].cor=BLACK;
                campo[i][j].movimento=0;
            }else{
                campo[i][j].cor=WHITE;
                campo[i][j].movimento=0;
            }
    for(j=0;j<c;j++){
        campo[l-1][j].cor=BLACK;
        campo[l-1][j].movimento=0;
    }
}
void mostrar_campo(quadrado campo[l][c],quadrado proximapeca[p][p],int pontos){
    int i,j;
    printf("Pr%cxima pe%ca:\n",-94,-121);
    for(i=0;i<p;i++){
        printf("\t");
        for(j=0;j<p;j++){
            setColor(proximapeca[i][j].cor);
            printf("%c%c",219,219);
        }
        printf("\n");
    }
    setColor(BLACK);
    printf("%c",201);
    for(j=1;j<c-1;j++)
        printf("%c%c",205,205);
    printf("%c\n",187);
    for(i=3;i<l-1;i++){
        for(j=0;j<c;j++){
            setColor(BLACK);
            if(j==0 || j==c-1)
                printf("%c",186);
            else{
                setColor(campo[i][j].cor);
                printf("%c%c",219,219);
            }
        }
        printf("\n");
    }
    setColor(BLACK);
    printf("%c",200);
    for(j=1;j<c-1;j++)
        printf("%c%c",205,205);
    printf("%c\n",188);
    setColor(BLACK);
    printf("Pontos: %d\n",pontos);
}

void criar_peca(quadrado peca[p][p]){
    int i,j;
    switch(rand()%7){
        case 0:
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    if(i==1)
                        peca[i][j].cor=LIGHTCYAN;
                    else
                        peca[i][j].cor=WHITE;
            break;
        case 1:
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    if((i==1 && !j) || (i==2 && j!=3))
                        peca[i][j].cor=LIGHTBLUE;
                    else
                        peca[i][j].cor=WHITE;
            break;
        case 2:
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    if((i==1 && j==2) || (i==2 && j!=3))
                        peca[i][j].cor=DARKGREY;
                    else
                        peca[i][j].cor=WHITE;
            break;
        case 3:
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    if((i==1 || i==2) && (j==1 || j==2))
                        peca[i][j].cor=YELLOW;
                    else
                        peca[i][j].cor=WHITE;
            break;
        case 4:
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    if((i==1 && (j==2 || j==3)) || (i==2 && (j==1 || j==2)))
                        peca[i][j].cor=LIGHTGREEN;
                    else
                        peca[i][j].cor=WHITE;
            break;
        case 5:
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    if((i==1 && j==1) || (i==2 && j!=3))
                        peca[i][j].cor=MAGENTA;
                    else
                        peca[i][j].cor=WHITE;
            break;
        case 6:
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    if((i==1 && (j==0 || j==1)) || (i==2 && (j==1 || j==2)))
                        peca[i][j].cor=LIGHTRED;
                    else
                        peca[i][j].cor=WHITE;
            break;
    }
    for(i=0;i<p;i++)
        for(j=0;j<p;j++)
            if(peca[i][j].cor!=WHITE)
                peca[i][j].movimento=1;
            else
                peca[i][j].movimento=0;
}
void colocar_peca(quadrado campo[l][c],quadrado peca[p][p],int linha,int coluna){
    int i,j;
    for(i=0;i<p;i++)
        for(j=0;j<p;j++)
            if(peca[i][j].cor!=WHITE)
                campo[i+linha][j+coluna]=peca[i][j];
}
void remover_peca(quadrado campo[l][c]){
    int i,j;
    for(i=0;i<l;i++)
        for(j=0;j<c;j++)
            if(campo[i][j].movimento==1){
                campo[i][j].cor=WHITE;
                campo[i][j].movimento=0;
            }
}
void parar_peca(quadrado campo[l][c]){
    int i,j;
    for(i=0;i<l;i++)
        for(j=0;j<c;j++)
            if(campo[i][j].movimento==1)
                campo[i][j].movimento=0;
}
void girar_peca(quadrado peca[p][p]){
    int i,j;
    quadrado auxiliar[p][p];
    for(i=0;i<p;i++)
        for(j=0;j<p;j++)
            auxiliar[j][3-i]=peca[i][j];
    for(i=0;i<p;i++)
        for(j=0;j<p;j++)
            peca[i][j]=auxiliar[i][j];
}

int detectar_parada(quadrado campo[l][c]){
    int i,j;
    for(i=0;i<l;i++)
        for(j=0;j<c;j++)
            if(campo[i][j].movimento==1 && campo[i+1][j].movimento==0 && campo[i+1][j].cor!=WHITE)
                return 1;
    return 0;
}
int detectar_lados(quadrado campo[l][c],int lado){
    int i,j;
    for(i=0;i<l;i++)
        for(j=0;j<c;j++)
            if(campo[i][j].movimento==1 && campo[i][j+lado].movimento==0 && campo[i][j+lado].cor!=WHITE)
                return 0;
    return 1;
}
int detectar_linha(quadrado campo[l][c],int linha){
    int i,j,cont=0;
    for(j=0;j<c;j++)
        if(campo[linha][j].cor!=WHITE)
            cont++;
    if(cont==c){
        for(i=linha;i>1;i--)
            for(j=1;j<c-1;j++)
                campo[i][j]=campo[i-1][j];
        for(j=1;j<c-1;j++){
            campo[0][j].cor=WHITE;
            campo[0][j].movimento=0;
        }
        return 1000;
    }
    return 0;
}
int detectar_fim(quadrado campo[l][c]){
    int j;
    for(j=1;j<c-1;j++)
        if(campo[3][j].cor!=WHITE && campo[3][j].movimento==0)
            return 1;
    return 0;
}
int detectar_giro(quadrado peca[p][p],quadrado campo[l][c],int linha,int coluna){
    int i,j;
    quadrado aux[p][p];
    for(i=0;i<p;i++)
        for(j=0;j<p;j++)
            aux[j][3-i]=peca[i][j];
    for(i=0;i<p;i++)
        for(j=0;j<p;j++)
            if(aux[i][j].cor!=WHITE && campo[i+linha][j+coluna].cor!=WHITE && !campo[i+linha][j+coluna].movimento)
                return 0;
    return 1;
}

int descer(quadrado campo[l][c],quadrado peca[p][p],quadrado proximapeca[p][p],int *pontos,int *linha,int *coluna){
    int i,j,sair=0;
    if(detectar_parada(campo)){
        parar_peca(campo);
        for(i=0;i<l-1;i++)
            (*pontos)+=detectar_linha(campo,i);
        sair=detectar_fim(campo);
        if(!sair){
            for(i=0;i<p;i++)
                for(j=0;j<p;j++)
                    peca[i][j]=proximapeca[i][j];
            criar_peca(proximapeca);
            *linha=-1;
            *coluna=(c/2-2);
        }
    }else
        remover_peca(campo);
    if(!sair){
        colocar_peca(campo,peca,++(*linha),*coluna);
        system("cls");
        mostrar_campo(campo,proximapeca,*pontos);
    }
    return sair;
}

int main()
{
    system("color f0");
    system("title Tetris");
    srand((time(NULL)));
    quadrado campo[l][c],peca[p][p],proximapeca[p][p];
    char op;
    while(1){
        int linha=0,coluna=c/2-2,pontos=0,sair=0,r[11];
        switch(menu(3,"Tetris","Jogar|Recordes|Sair|",0,175,0,0,12,10)){
            case 0:
                iniciar_campo(campo);
                criar_peca(peca);
                criar_peca(proximapeca);
                colocar_peca(campo,peca,linha,coluna);
                mostrar_campo(campo,proximapeca,pontos);
                while(!sair){
                    if(kbhit()){
                        op=getch();
                        if(op==13){
                            system("cls");
                            printf("PAUSE\n");
                            system("pause");
                        }
                        if(op==27)
                            return 0;
                        if(op==8)
                            sair=1;
                        if(op==-32){
                            op=getch();
                            switch(op){
                                case 'H':
                                    if(detectar_giro(peca,campo,linha,coluna))
                                        girar_peca(peca);
                                    break;
                                case 'K':
                                    if(detectar_lados(campo,-1))
                                        coluna--;
                                    break;
                                case 'M':
                                    if(detectar_lados(campo,1))
                                        coluna++;
                                    break;
                            }
                            if(op!='P'){
                                remover_peca(campo);
                                colocar_peca(campo,peca,linha,coluna);
                                system("cls");
                                mostrar_campo(campo,proximapeca,pontos);
                            }
                            sair=descer(campo,peca,proximapeca,&pontos,&linha,&coluna);
                            if(op!='P')
                                Sleep(250-pontos/200);
                        }
                    }else{
                        sair=descer(campo,peca,proximapeca,&pontos,&linha,&coluna);
                        Sleep(250-pontos/200);
                    }
                }
                system("cls");
                printf("Fim de jogo!\nPontua%c%co: %d\nPressione enter para continuar...\n",-121,-58,pontos);
                while(getch()!=13){}
                adicionar_recorde(r,pontos);
                break;
            case 1:
                listar_recordes(r);
                system("pause");
                int op=menu(3,"Recordes","Voltar|Limpar recordes|Sair|",0,175,0,0,12,10);
                if(op==-1 || op==2)
                    return 0;
                if(op==1)
                    resetar_recordes(r);
                break;
            case -1:
            case 2:
                return 0;
        }
    }
}

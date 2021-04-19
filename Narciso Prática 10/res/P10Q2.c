/**     Pratica 10 - Questao 2: Calcula vector interseccao entre outros dois vectores
    *           Narciso Filho
    */


#include <stdio.h>
#include "graficos.h"

#define TAMMAX 20
#define MAXALGs 8

#define ENTRADA 1
#define IMPRIMIR 0

///Prototipos
void calc_intersec( int* , int , int* , int , int* , int* );
void MontaArranjoDeInt( int *vet , int qtd , int x , int y , unsigned oper );

int xatual( void );      //wherex()
int yatual( void );
void ir( int x , int y );        //gotoxy


int main()
{
        int n[ 3 ] = { 0 };
        int Vet[ 3 ][ TAMMAX ] = { 0 };
        int i;

        defJanela("Quest 2 - Vector Intercessao");

        do{
                limpaTela();
                moldura(BROWN);

                for( i = 0 ; i <= 1 ; i++)
                {
                        ir( 3 , yatual() );
                        printf("Quantidade de elementos do vetor %c: " , 65 + i);
                        scanf("%d" , n + i );
                        ir( 7 , yatual() );
                        printf("Entrada vetor %c:" , 65 + i);
                        MontaArranjoDeInt( Vet[ i ] , n[ i ] , 10 , yatual() + 1 , ENTRADA );
                }


                calc_intersec( Vet[ 0 ] , n[ 0 ] , Vet[ 1 ] , n[ 1 ] , Vet[ 2 ] , &n[ 2 ] );

                ir( 3 , yatual() + 3 );
                printf("Vetor Intercec\207\306o:");
                MontaArranjoDeInt( Vet[ 2 ] , n[ 2 ] , 10 , yatual() + 1 , IMPRIMIR );
        }while( repetir_S_N() );

        limpaTela();
        return 0;
}

///
void calc_intersec( veta , na , vetb , nb , vetc , nc )
int *veta , na , *vetb , nb , *vetc , *nc;
{
        int i , j;

        *nc = 0;
        for( i = 0 ; i < na ; i++)
                for( j = 0 ; j < nb ; j++)
                        if( veta[ i ] == vetb[ j ] )
                        {
                                vetc[ *nc ] = veta[ i ];
                                *nc += 1;
                        }
}



///-----------------------------------------------------------------------------------------------------conio2.h
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>

#define cv textcolor(10) //Cor Verde
#define cb textcolor(15) //Cor Branca
#define cvm textcolor(4) //Cor Vermelha

///MontaArranjoDeInt : Recebe endereço do elemento zero de um arranjo de Int e  aplica entradas de uma forma mais legal
void MontaArranjoDeInt( int *vet , int qtd , int x , int y , unsigned oper)
{
        int tamanhoNum =  0 ;
        int copy;
        int i ;
        int comprimento = 0;

        cv;
        cputsxy( x , y , "{ " );

        for( i = 0 ; i < qtd ; i++)
        {
                if( oper == ENTRADA )
                        scanf("%d" , &vet[ i ] );
                else
                        if( !oper )
                                printf("%d" , vet[ i ] );

                copy = vet[ i ];

                do                                               //Mede tamanho ( quantidade de algorismos ) do numero inserido
                {
                        tamanhoNum++;
                        copy /= 10;
                }
                while( copy );
                if( vet[ i ] < 0 ) tamanhoNum++;

                comprimento += tamanhoNum;

                if( i < qtd - 1 )
                {
                        cputsxy( x + comprimento + 2 , y , " , ");      //Insere a virgula
                        comprimento += 3;
                }

                gotoxy( x + comprimento + 2 , y);      //Posiciona cursor corretamente

                tamanhoNum = 0;
       }

        puts(" }");
        cb;

        gotoxy( 1 , y + 1);
        return;
}

int xatual( void )      //wherex()
{
        return wherex();
}

int yatual( void )      //wherey()
{
        return wherey();
}

void ir( int x , int y )        //gotoxy()
{
        gotoxy( x , y);
}

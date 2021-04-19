/**     Pratica 10 - Questao 3: Recebe algumas notas e determina media e conceito final do aluno
    *           Narciso Filho
    */


#include <stdio.h>
#include "graficos.h"

///Prototipos
void coletarx( float *a , float *b , float *c , float *d , float *F , int x );
void resultado( float a , float b, float c , float d , float F );
void info( void );
float Med( float a , float b , float c , float d , float F );
char Conc( float nota );


///Funcao Principal
int main()
{
        float a , b , c , d , F;        //Lados do triangulo
        float area;
        char tipo;

        defJanela("QUEST. 3: NOTAS");

        do{
                limpaTela();
                moldura( LIGHTCYAN );
                titulo("NOTAS : PRAT 10 - QT 3");
                info();
                printf("Informe as notas do aluno:");
                coletarx( &a , &b , &c , &d , &F , 17 );


                resultado( a , b , c , d ,  F );

        }while( repetir_S_N() );

        limpaTela();
        return 0;
}




///-------------------------------------------------------------------------------------------conio2.h
#include <conio2.h>
#include <string.h>
#include <math.h>
#define LARG 50
#define ALT 25
void resultado(float a , float b, float c , float d , float F )     ///
{
        float media = Med( a , b , c , d , F );
        char conceito = Conc( media );
        int cor;

        cor = ( conceito < 68)  ? LIGHTGREEN  :  RED;
        textcolor( cor );

        gotoxy( 19 , 16 );
        printf("Media = %.2f" , media );
        gotoxy( 19 , 17 );
        printf("Conceito = %c " , conceito );

        textcolor( WHITE );
}

float Med( float a , float b , float c , float d , float F )
{
        float notas[ ] = { a , b , c , d , F };
        int menor = 0;
        float media = 0;
        int i;


        for( i =  1 ; i <= 3 ; i++)
                menor = ( notas[ i ] < notas[ menor ] )  ?  i : menor;

        for( i =  0 ; i <= 4 ; i++)
                if( i != menor )
                        media += notas[ i ];

        return media;
}

char Conc( float nota )
{
        return 68 - (int)floor( nota / 50 ) - (int)floor( nota / 70 ) - (int)floor( nota / 85 ) + (int)floor( nota / 100 );
}

void info( void )
{
        textcolor( BROWN );

        gotoxy( 3 , 5 );
        putchar('\332');
        gotoxy( 3 , 6 );
        puts("\263  Nota 1  =  \?");
        gotoxy( 3 , 7 );
        puts("\263  Nota 2  =  \?");
        gotoxy( 3 , 8 );
        puts("\263  Nota 3  =  \?");
        gotoxy( 3 , 9 );
        puts("\263  Nota 4  =  \?");
        gotoxy( 3 , 10 );
        puts("\263  Nt Fin  =  \?");
        gotoxy( 3 , 11 );
        putchar('\300');
        textcolor( WHITE );
        gotoxy( 3 , 4 );
}
void coletarx( float *a , float *b , float *c , float *d , float *F , int x )
{
        textcolor( GREEN );
        _setcursortype( _SOLIDCURSOR);
        gotoxy( x , 6 );
        scanf("%f" , a );

        gotoxy( x , 7 );
        scanf("%f" , b );

        gotoxy( x , 8 );
        scanf("%f" , c );

        gotoxy( x , 9 );
        scanf("%f" , d );

        gotoxy( x , 10 );
        scanf("%f" , F );

        _setcursortype( _NORMALCURSOR);
        textcolor( WHITE );


}


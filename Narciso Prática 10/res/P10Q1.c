/**     Pratica 10 - Questao 1: Determina area e tipo de triangulo a partir dos lados
    *           Narciso Filho
    */
#include <stdio.h>
#include "graficos.h"

///Prototipos
char triangulo( float a , float b, float c , float *area);
unsigned TestTriang( float a , float b, float c );
float AreaTriang( float a , float b, float c );
float SemiPer( float a , float b , float c );

void resultado(float a , float b, float c , float area , char tipo);
static char *nomeTipo( char tipo );
void info( void );


///Funcao Principal
int main()
{
        float a , b , c;        //Lados do triangulo
        float area;
        char tipo;

        defJanela("QUEST. 1: TRIANGULOS");

        do{
                limpaTela();
                moldura( LIGHTGREEN );
                titulo("TRI\266NGULOS : PRAT 10 - QT 1");
                info();
                printf("Informe os lados do tri\203ngulo:");
                coletar( &a , &b , &c );

                tipo = triangulo( a , b , c , &area );

                resultado( a , b , c , area , tipo);

        }while( repetir_S_N() );

        limpaTela();
        return 0;
}


enum { equilatero = 'q' , isosceles = 'i' , escaleno = 'e' , ntriang = 'n' };

char triangulo( float a , float b, float c , float *area )      ///
{
        if( TestTriang( a , b , c ) )
        {
             *area =  AreaTriang( a , b , c );
             return ( a == b  &&  b == c  ? equilatero : ( a != b  &&  b != c  &&  a != c  ? escaleno : isosceles ) );
        }
        else
                return ntriang;
// 'q' -> Equilátero  ,  'i' -> Isósceles , 'e' -> Escaleno , 'n' -> Não-Triângulo
}

unsigned TestTriang( float a , float b, float c )       ///
{
        if( a > 0  &&  b > 0  &&  c > 0 )
                if( a + b > c  &&  a + c > b  && b + c > a)
                        return 1;

        return 0;
}

#include <math.h>
float AreaTriang( float a , float b, float c )          ///----------------------------------
{
        float T = SemiPer( a , b , c);

        return sqrt( T * ( T - a ) * ( T - b ) * ( T - c ) );
}

float SemiPer( float a , float b, float c )
{
        return ( a + b + c ) / 2;
}


///-------------------------------------------------------------------------------------------conio2.h
#include <string.h>
#include "conio\conio2.h"
#define LARG 50
#define ALT 25
void resultado(float a , float b, float c , float area , char tipo)     ///
{
        if( tipo != ntriang)
        {
                textcolor( BLUE );
                gotoxy( 20 , 6 );
                printf("Tri\203ngulo tipo %s" , nomeTipo( tipo) );
                gotoxy( 20 , 7 );
                printf("\265rea = %.2f m\375" , area );
        }
        else
        {
                textcolor( RED );
                gotoxy( 6 , 13 );
                printf("\a\255\255Problemas!!");
                gotoxy( 6 , 14 );
                printf("Isso n\306o \202 um tri\203ngulo...");
        }

        textcolor( WHITE );
}

static char *nomeTipo( char tipo )     ///
{
        switch( tipo )
        {
                case equilatero: return "Equil\240tero";
                case isosceles: return "Is\242sceles";
                case escaleno: return "Escaleno";
                default: return "\?\?!!!!!\?\?";
        }
}

void info( void )
{
        textcolor( BROWN );

        gotoxy( 3 , 5 );
        putchar('\332');
        gotoxy( 3 , 6 );
        puts("\263  a  =  \?");
        gotoxy( 3 , 7 );
        puts("\263  b  =  \?");
        gotoxy( 3 , 8 );
        puts("\263  c  =  \?");
        gotoxy( 3 , 9 );
        putchar('\300');
        textcolor( WHITE );
        gotoxy( 3 , 4 );
}
///FIM DO CODIGO



























//


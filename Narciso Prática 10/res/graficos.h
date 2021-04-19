#ifndef __GRAFICOS_H_
#define __GRAFICOS_H_

#include <string.h>
#include "conio\conio2.h"
#include "graficos.h"

#define LARG 50
#define ALT 25

///Prototipos
void moldura( int cor );
void titulo( char *argv0 );
void coletar( float *a , float *b , float *c );
int centraTexto( char *str );
unsigned repetir_S_N( void );
void pause( void );
void limpaTela( void );
void Fim( void );

void defJanela( char *argv0 );




void moldura( int cor )            ///----------------------------------------------
{
        int i ;


        textcolor( cor );
        for( i = 0 ; i < LARG * ALT ; i++)
                if( !( i % LARG ) ||  !( (i + 1) / LARG )  ||  !( (LARG * (ALT - 1) / (i + 1) ) )  ||  !( (i % LARG + 1) % LARG ))
                        putchxy( i % LARG + 1 , i / LARG + 1 , '#' );
        textcolor( WHITE );

        gotoxy( 3 , 4 );
}

void coletar( float *a , float *b , float *c )
{
        textcolor( GREEN );
        _setcursortype( _SOLIDCURSOR);
        gotoxy( 12 , 6 );
        scanf("%f" , a );

        gotoxy( 12 , 7 );
        scanf("%f" , b );

        gotoxy( 12 , 8 );
        scanf("%f" , c );

        _setcursortype( _NORMALCURSOR);
        textcolor( WHITE );


}
#include <ctype.h>
unsigned repetir_S_N( void )            ///----------------------------------------------
{
        char msg[] = "Deseja repetir?( S / N )";
        int leitura;

        for( ; ; )
        {
                cputsxy( centraTexto( msg ) , ALT - 1 , msg );
                leitura = toupper( getch() );
                if( leitura == 'S' )
                        return 1;
                else
                        if( leitura == 'N' )
                                return 0;
                        else
                        {
                                printf("\a");
                                cputsxy( centraTexto( "ENTRADA INVALIDA!" ) , ALT - 2 , "ENTRADA INVALIDA!" );
                        }

        }
}

int centraTexto( char *str )
{
        return ( LARG - strlen( str ) ) / 2 ;
}


void pause( void )              ///
{
        _setcursortype( _NOCURSOR );
        getch();
        _setcursortype( _NORMALCURSOR );
}

void limpaTela( void )          ///
{
        ScreenClear();
}

void Fim( void )                ///
{
        limpaTela();
        printf("\n\n\t\tThe End");
}

#include <stdlib.h>
#include <windows.h>

void defJanela( char *argv0 )
{
        {
                char comando[100] = "\"title " ;

                strcat( comando , argv0 );
                comando[ strlen(comando) ] = '\"';      //Inserindo as aspas do final
                comando[ strlen(comando) + 1 ] = '\0';      //Inserindo o


                system(comando);
        }

        {
                char comando[] = "mode con: cols=XX lines=XX";
                comando[ 15 ] = '0' + LARG/10;          //'0' == 48
                comando[ 16 ] = '0' + LARG%10;
                comando[ 24 ] = '0' + ALT/10;
                comando[ 25 ] = '0' + ALT%10;

                system(comando);
        }


}


///
void titulo( char *argv0 )
 {
        char padrao[ LARG - 2] = "PROGRAMA";
//        char padrao[ LARG - 2] = "TRI\266NGULOS : PRAT 10 - QT 1";
        ( argv0  &&  strlen( argv0 ) < LARG - 2 )  ?  strcpy( padrao , argv0 )  :  "não altere nada, compilador";

        highvideo();

        textbackground( BROWN );
        textcolor( BLUE );
        gotoxy( centraTexto( padrao ) , 2 );
        puts( padrao );
        textcolor( WHITE );
        textbackground( BLACK );
        gotoxy( 3 , 4 );
}



#endif // __GRAFICOS_H_

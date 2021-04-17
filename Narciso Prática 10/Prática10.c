///PRATICA 10 - NARCISO FILHO
#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>

#define FPS 70

//Struct para o menu
typedef struct
{
        int item;
        int subitem;
        unsigned entrar : 1;
        unsigned alterou : 1;
        unsigned sair : 1;
}Selection;

void iniciaJanela( void );
void compilatudo( void );
void escondeCursor( void );
void exibeCod( int );
void rodaProg(int );

void AtualizaMenu( Selection *sel );
int deveSair( Selection *sel );
int teclaPress( int tecla );

void Moldura( int cor )  ;
void DesenhaMenu( Selection sel );
void SubItens( Selection sel );
void Titulo( void );
void QuadradoD( int x , int y , int L , int cor , int fundo );
void Retang( int x , int y , int Lx , int Ly , int cor , int fundo );
void RetangM( int x , int y , int Lx , int Ly , int caractere , int cor ,  int fundo );
void limpaTela( void );
int TelaEmFoco( void );
void carregando( void );

int main()
{
        Selection sel = ( Selection ){ 1 , 0 , 0 , 1 , 0 };
        void (*func[2] )( int ) = { exibeCod , rodaProg };


        iniciaJanela();
        escondeCursor();
        carregando();
        compilatudo();
        limpaTela();

        do{
                AtualizaMenu( &sel );
                if( sel.alterou ){
                        DesenhaMenu( sel ) ;
                        sel.alterou = 0;
                }
                if( sel.entrar ) ( *func[ sel.subitem - 1] )(sel.item);

                sel.entrar = 0;
        }while( !deveSair( &sel )  &&  !sel.sair );

        return 0;
}



///
void iniciaJanela( void )
{
        system("mode con cols=1366 lines=768");
        system("title PRATICA 10 ___ NARCISO FILHO ___ 17-04-2021");

        //Definindo tela cheia
        keybd_event( VK_MENU , 0x36 , 0 , 0 );                                         //Pressiona Alt
        keybd_event( VK_RETURN , 0x1C , 0 , 0 );                                     //Pressiona Enter
        keybd_event( VK_MENU , 0x1C , KEYEVENTF_KEYUP , 0 );             //Solta alt
        keybd_event( VK_RETURN , 0x38 , KEYEVENTF_KEYUP , 0 );          //Solta enter

        //Definindo Tela Maximizada
        HWND consoleWindow = GetConsoleWindow();                 // Pega o codigo da tela
        ShowWindow( consoleWindow , SW_MAXIMIZE );               // Simula click em maximizar janela
}

///
void compilatudo( void )
{
        system("gcc -o res\\P10Q1.exe  res\\P10Q1.c res\\conio\\libconio.a res\\conio\\conio2.h");
        system("gcc -o res\\P10Q2.exe  res\\P10Q2.c res\\conio\\libconio.a res\\conio\\conio2.h");
        system("gcc -o res\\P10Q3.exe  res\\P10Q3.c res\\conio\\libconio.a res\\conio\\conio2.h");
}

///
void exibeCod( int item )
{
        char cmds[][40] = {
                "start type res\\p10q1.c",
                "start type res\\p10q2.c",
                "start type res\\p10q3.c"
        };

        system( cmds[ item - 1] );
}

///
void rodaProg(int item )
{
        char cmds[][40] = {
                "start res\\p10q1",
                "start res\\p10q2",
                "start res\\p10q3"
        };

        system( cmds[ item - 1] );
}

///
#define QTDITEMS 4

void AtualizaMenu( Selection *sel )
{
        if( ( teclaPress( VK_DOWN )  ||  teclaPress( VK_RETURN ) )  )
                if( sel->item < QTDITEMS ){

                        if( !sel->subitem ){
                                sel->subitem = 1;
                                sel->alterou = 1;
                                return;
                        }else{
                                sel->entrar = 1;
                                sel->alterou = 1;
                        }
                }else{
                        sel->sair = 1 ;
                        return;
                }

        if( teclaPress( VK_UP )  ||  teclaPress( VK_ESCAPE ) )
                if( sel->subitem ){
                        sel->subitem = 0;
                        sel->alterou = 1;
                        return;
                }

        if( teclaPress( VK_RIGHT ) )
                if( !sel->subitem  &&  sel->item < QTDITEMS ){
                                sel->item++;
                                sel->alterou = 1;
                                return;
                        }
                else
                        if( sel->subitem )
                                if( sel->subitem == 1 ){
                                        sel->subitem = 2;
                                        sel->alterou = 1;
                                        return;
                                }

        if( teclaPress( VK_LEFT ) )
                if( !sel->subitem  &&  sel->item > 1 ){
                        sel->item--;
                        sel->alterou = 1;
                        return;
                }
                else
                        if( sel->subitem )
                                if( sel->subitem == 2 ){
                                        sel->subitem = 1;
                                        sel->alterou = 1;
                                        return;
                                }

}

///
int teclaPress( int tecla )
{
        if( GetAsyncKeyState( tecla)  & 0x8000 )
                return 1;
        else
                return 0;
}

int deveSair( Selection *sel )
{
        if( GetAsyncKeyState( VK_HOME )  )
                        return 1;
        return 0;
}



///------------------------------------------------------------------conio2.h
#include <conio2.h>

void DesenhaMenu( Selection sel )
{
        int i;
        static int first = 1;
        const int xsair = 146 , ysair = 45;

        if( first ){
                first = 0;
//                Moldura( LIGHTGRAY );
                Titulo( );
        //        Itens();
        }

        for( i = 0 ; i < 3 ; i++ )
                QuadradoD( 10 + 50 * i , 17 , 20 , WHITE , BLACK );

        if( !sel.subitem  &&  sel.item < 4 ) QuadradoD( 10 + 50 * ( sel.item - 1 ) , 17 , 20 , WHITE , GRAY_BRUSH );

        ( sel.item == 4 ) ? Retang( xsair , ysair , 20 , 3 , LIGHTGRAY , GRAY_BRUSH ) : Retang( xsair , ysair , 20 , 3 , LIGHTGRAY , BLACK );

        SubItens( sel );

        Sleep( FPS );
}

///
void SubItens( Selection sel )
{
        if( sel.subitem )
        {
                int xpp = ( sel.item - 1 ) * ( 50 );
                int cor1 , cor2;
                ( sel.subitem == 1 )  ?  (cor1 = GRAY_BRUSH , cor2 = BLACK ) : ( cor1 = BLACK , cor2 = GRAY_BRUSH);

                Retang( xpp + 10 , 37 , 20 , 3 , WHITE , cor1 );
                cputsxy( xpp+ 15 , 38 , "VER CODIGO");

                Retang( xpp + 30 , 37 , 20 , 3 , WHITE , cor2 );
                cputsxy( xpp + 31 , 38 , "EXECUTAR PROGRAMA");
        }
        else
        {
                RetangM( 10 , 37 , 140 , 3 , ' ' , BLACK , BLACK );
        }

}

///
void QuadradoD( int x , int y , int L , int cor , int fundo )
{
        int i , j;
        const int Lx = 2 * L;       //Por causa da diferenca entre a largura e a altura do pixel

        //Cores
        textcolor( cor );
        textbackground( fundo );

        //Topo e Base
        for( i = 0 ; i < L ; i += L - 1)
                for( j = 1 ; j < Lx - 1 ; j++)
                {
                        gotoxy(x + j , y + i );
                        putchar( 205 );
                }

        //Laterais
        for( i = 1 ; i < L - 1 ; i ++ )
                for( j = 0 ; j < Lx ; j += Lx - 1)
                {
                        gotoxy( x + j , y + i );
                        putchar( 186 );
                }

        //Quinas
        gotoxy( x + 0 , y + 0 );    putchar( 201 );     //SUP. ESQ.
        gotoxy( x + Lx - 1 , y + 0 );    putchar( 187 );     //SUP. DIR.
        gotoxy( x + 0 , y + L - 1 );    putchar( 200 );     //INF. ESQ.
        gotoxy( x + Lx - 1 , y + L - 1 );    putchar( 188 );     //INF. DIR.


        textcolor( WHITE );
        textbackground( BLACK );
}


///
void Retang( int x , int y , int Lx , int Ly , int cor , int fundo )
{
        int i , j;

        //Cores
        textcolor( cor );
        textbackground( fundo );

        //Topo e Base
        for( i = 0 ; i < Ly ; i += Ly - 1)
                for( j = 1 ; j < Lx - 1 ; j++)
                {
                        gotoxy(x + j , y + i );
                        putchar( 205 );
                }

        //Laterais
        for( i = 1 ; i < Ly - 1 ; i ++ )
                for( j = 0 ; j < Lx ; j += Lx - 1)
                {
                        gotoxy( x + j , y + i );
                        putchar( 186 );
                }

        //Quinas
        gotoxy( x + 0 , y + 0 );    putchar( 201 );     //SUP. ESQ.
        gotoxy( x + Lx - 1 , y + 0 );    putchar( 187 );     //SUP. DIR.
        gotoxy( x + 0 , y + Ly - 1 );    putchar( 200 );     //INF. ESQ.
        gotoxy( x + Lx - 1 , y + Ly - 1 );    putchar( 188 );     //INF. DIR.


        textcolor( WHITE );
        textbackground( BLACK );
}


///
void RetangM( int x , int y , int Lx , int Ly , int caractere , int cor ,  int fundo )
{
        int i , j;

        //Cores
        textcolor( cor );
        textbackground( fundo );

        for( i = y ; i < y + Ly ; i++)
                for( j = x ; j < x + Lx ; j++)
                {
                        gotoxy( j , i );
                        printf("%c" , caractere );
                }

        textcolor( WHITE );
        textbackground( BLACK );
}

///
void escondeCursor( void )
{
//        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//        CONSOLE_CURSOR_INFO info;
//        info.dwSize = 100;
//        info.bVisible = FALSE;
//        SetConsoleCursorInfo(consoleHandle, &info);

//        _setcursortype( _NOCURSOR );

        printf("\e[?25l");

}
///
void Titulo( void )
{
        int i , j;
        const int x0 = 55 , y0 = 5;
        char nome[ 8 ][ 100 ] = {
                {"         (   (                  (                       "},
                {" )\\ ))\\ )   (          ))\\ )  (    (          )    )"},
                {"(()/(()/(   )\\     )  /(()/(  )\\   )\\      ( /( ( /("},
                {" /(_))(_))(((_)(  ( )(_))(_))((_)(((_)(    )\\()))\\())"},
                {"(_))(_))  )\\ _ )\\(_(_())_)) )\\___)\\ _ )\\  ((_)\\((_)\\"},
                {"| _ \\ _ \\   /_\\  |_   _|_ _| / __|  _\\    /  | /  \\"},
                {"|  _/   /  / _ \\   | |  | | | |__ / _ \\    | || () |"},
                {"|_| |_|_\\ /_/ \\_\\  |_| |___| \\___/_/ \\_\\   |_| \\__/"}
        };

        for( i = 0 ; i < 8 ; i++ )
                for( j = 0 ; j < strlen( nome[ i ] ) ; j++ )
                {
                        if( i < 5 )
                                switch( nome[ i ][ j ] )
                                {
                                        case '(':       textcolor( RED );        break;
                                        case ')':       textcolor( BROWN );     break;
                                        case '\\':      textcolor( BROWN );     break;
                                        case '_':       textcolor( BROWN );     break;
                                        case '/':       textcolor( RED );     break;
                                        default:        textcolor( WHITE );
                                }
                        else
                                textcolor( WHITE );
                putchxy( x0 + j , y0 + i , nome[ i ][ j ] );
                }

        textcolor( WHITE );
}

///
#define LARG 167
#define ALT 45
void Moldura( int cor )
{
        int i ;


        textcolor( cor );
        textbackground( cor );
        for( i = 0 ; i < LARG * ALT ; i++)
                if( !( i % LARG ) ||  !( (i + 1) / LARG )  ||  !( (LARG * (ALT - 1) / (i + 1) ) )  ||  !( (i % LARG + 1) % LARG ))
                        putchxy( i % LARG + 1 , i / LARG + 1 , '#' );
        textcolor( WHITE );
        textbackground( BLACK );

        gotoxy( 3 , 4 );
}

void limpaTela( void )
{
        clrscr();
}

int TelaEmFoco( void )
{
//        IntPtr hWnd = GetForegroundWindow();


}

void carregando( void )
{
        char *msg = "CARREGANDO >>>";
//                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tCARREGANDO>>>>");
        cputsxy( (LARG - strlen( msg ) ) / 2 , ALT / 2  , msg );
}

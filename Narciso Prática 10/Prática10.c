///PRATICA 10 - NARCISO FILHO
#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0501
#include <windows.h>

#define DELAY 70

#define REF_Y 768       //Referencia de altura do monitor em pixels( minha resolucao )
#define REF_X 1366     //Referencia de largura do monitor em pixels( minha resolucao )

//Struct para o menu
typedef struct
{
        int item;
        int subitem;
        unsigned entrar : 1;
        unsigned alterou : 1;
        unsigned sair : 1;
        HWND janela;
        COORD tamanhoMonitor;
        COORD casasMonitor;

        COORD posQ[ 5 ];
        int tamLQ;

        COORD posS;
        int tamLS;

        float escalaX;
        float escalaY;

        POINT posMouse;
}Selecao;

void iniciaJanela( Selecao *sel );
void compilatudo( void );
void escondeCursor( void );
void exibeCod( int );
void rodaProg(int );

void AtualizaMenuTeclado( Selecao *sel );
void AtualizaMenuMouse( Selecao *sel );
int ColisMouseRetang( int x0 , int xf , int y0 , int yf , Selecao sel);
int AlteraItemMouse( Selecao *sel , int nmrItem );
int EnrarItemMouse( Selecao *sel );
int deveSair( Selecao *sel );
int teclaPress( int tecla );

void Moldura( int cor ) ;
void DesenhaMenu( Selecao sel );
void Itens( Selecao sel );
void SubItens( Selecao sel );
void Titulo( void );
void QuadradoD( int x , int y , int L , int cor , int fundo );
void Retang( int x , int y , int Lx , int Ly , int cor , int fundo );
void RetangM( int x , int y , int Lx , int Ly , int caractere , int cor ,  int fundo );
void limpaTela( void );
int TelaEmFoco( Selecao sel );
void carregando( Selecao sel );
COORD TamConsole( void );
void ResoluMonitor( COORD *tamanho );
void desenhosItem1( Selecao sel );
void desenhosItem2( Selecao sel );
void desenhosItem3( Selecao sel );
void Hasta( Selecao sel );




int main()
{
        Selecao sel = ( Selecao ){ 1 , 0 , 0 , 0 , 0 , 0 };
        void (*func[2] )( int ) = { exibeCod , rodaProg };


        iniciaJanela( &sel );
        escondeCursor();
        carregando( sel );
        compilatudo();
        limpaTela();
        DesenhaMenu( sel );

        do{
                if( TelaEmFoco( sel ) ){
                        AtualizaMenuTeclado( &sel );          // Caso o usuario esteja focando na janela do menu ativa interacao pelo teclado
                        AtualizaMenuMouse( &sel );           // "  " pelo mouse
                }

                if( sel.alterou ){                                                         //Caso houve alteracao no desenho redesenha
                        DesenhaMenu( sel ) ;
                        sel.alterou = 0;
                        Beep( 1000 , DELAY );
                }
                if( sel.entrar ) ( *func[ sel.subitem - 1] )(sel.item);

                sel.entrar = 0;
        }while( !deveSair( &sel )  &&  !sel.sair );

        Hasta( sel );

        return 0;
}



///
void iniciaJanela( Selecao *sel )
{
        int colsR = 172;
        int linesR = 47;

        //Tamanho do Monitor
        ResoluMonitor( &sel->tamanhoMonitor );

        //Escala do Tamanho da Janela
        sel->escalaX = sel->tamanhoMonitor.X / (float)REF_X;
        sel->escalaY = sel->tamanhoMonitor.Y / (float)REF_Y;
        #define ESCX sel->escalaX
        #define ESCY sel->escalaY

        {
                int colunas = colsR *  sel->escalaX;
                int linhas = linesR * sel->escalaY;
                char cmd[] = "mode con cols=XXX lines=XXX";
                cmd[ 14 ] = colunas / 100 + '0';
                cmd[ 15 ] = ( colunas % 100 ) / 10 + '0';
                cmd[ 16 ] =  colunas % 10  + '0';

                cmd[ 24 ] = linhas / 100 + '0';
                cmd[ 25 ] = ( linhas % 100 ) / 10 + '0';
                cmd[ 26 ] =  linhas % 10  + '0';


                system( cmd );
                sel->casasMonitor.X = colunas;
                sel->casasMonitor.Y = linhas;
        }

        //Titulo
        system("title PRATICA 10 ___ NARCISO FILHO ___ 17-04-2021");

        //Definindo tela cheia
        keybd_event( VK_MENU , 0x36 , 0 , 0 );                                         //Pressiona Alt
        keybd_event( VK_RETURN , 0x1C , 0 , 0 );                                     //Pressiona Enter
        keybd_event( VK_MENU , 0x1C , KEYEVENTF_KEYUP , 0 );             //Solta alt
        keybd_event( VK_RETURN , 0x38 , KEYEVENTF_KEYUP , 0 );          //Solta enter

        //Codigo da Janela
        sel->janela = GetConsoleWindow();                                       // Pega o codigo da tela

        //Definindo Tela Maximizada
        ShowWindow( sel->janela , SW_MAXIMIZE );               // Simula click em maximizar janela

        //Posicao dos Items
        sel->tamLQ = 20 * sel->escalaX;
        {
                const int yQ = 17 * sel->escalaY;
                const int space = (int)( ( ( colsR - 3 * sel->tamLQ * 2 ) / 5 ) * sel->escalaX);            //Multiplicar o tamLQ por 2 devido a escala para o lado X aplicada em RetangD
                const int x0Q = space * 1.5;
                register int i ;

                for( i = 1 ; i < 4 ; i++)
                        sel->posQ[ i ].X = x0Q + sel->tamLQ * ( i - 1 ) * 2 + space * ( i - 1 );        //Multiplicar o tamLQ por 2 devido a escala para o lado X aplicada em RetangD

                for( i = 1 ; i < 4 ; i++)
                        sel->posQ[ i ].Y = yQ;

        }

        //Posicao 'Sair'
        sel->tamLS = 20 * sel->escalaX;
        sel->tamLS = ( sel->tamLS > 7) ? sel->tamLS : 8;

        sel->posS.X = sel->casasMonitor.X - 3 - sel->tamLS;
        sel->posS.Y = sel->casasMonitor.Y - 4;

        //Desabilitar Modo de Edicao Rapida para nao atrapalhar iteracao do mouse
        {
                HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
                DWORD prev_mode;

                GetConsoleMode(hInput, &prev_mode);
                SetConsoleMode(hInput, prev_mode & ENABLE_EXTENDED_FLAGS);
        }
}

///
COORD TamConsole( void )
{
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD tam;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        tam.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        tam.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return tam;
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
        static int aviso = 1;
        char cmds[][80] = {
                "start \"Codigo da Questao 1\" more res\\p10q1.c",
                "start \"Codigo da Questao 2\" more res\\p10q2.c",
                "start \"Codigo da Questao 3\" more res\\p10q3.c"
        };

        system( cmds[ item - 1] );




        if( aviso )
        {
                char avisoCriar[150] = {"(echo MsgBox \"-Tecla ENTER para descer uma linha\" ^& vbCrLf ^& \"-Tecla SPACE para descer uma pagina\",262192, \"Tutorial\")> res\\aviso.vbs "};
                char avisoExibir[80] = {"start res\\aviso.vbs"};
                char avisoDeletar[80] = {"del res\\aviso.vbs"};

                system( avisoCriar );
                system( avisoExibir );

                Sleep( 1000 );
                system( avisoDeletar );
                aviso = 0;
        }
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

void AtualizaMenuTeclado( Selecao *sel )
{
        //Caso esteja focando no menu
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

int deveSair( Selecao *sel )
{
        if( !GetAsyncKeyState( VK_HOME )  )
//                if( GetConsoleDisplayMode( (LPDWORD)CONSOLE_FULLSCREEN_MODE  ) )
                        return 0;
        return 1;
}



///------------------------------------------------------------------conio2.h
#include "res\conio\conio2.h"

void DesenhaMenu( Selecao sel )
{
        int i;
        static int first = 1;
        const int xsair = 146 * sel.escalaX, ysair = 45 * sel.escalaY;


        if( first ){
                first = 0;
//                Moldura( LIGHTGRAY );
                Titulo( );
                Itens( sel );
        }

        for( i = 1 ; i < 4 ; i++ )
                QuadradoD( sel.posQ[ i ].X , sel.posQ[ i ].Y , sel.tamLQ , WHITE , BLACK );

        if( !sel.subitem  &&  sel.item < 4 ) QuadradoD( sel.posQ[ sel.item ].X , sel.posQ[ sel.item ].Y , sel.tamLQ , WHITE , GRAY_BRUSH );

        ( sel.item == 4 ) ? Retang( sel.posS.X , sel.posS.Y , sel.tamLS , 3 , LIGHTGRAY , GRAY_BRUSH ) : Retang( sel.posS.X , sel.posS.Y , sel.tamLS , 3 , LIGHTGRAY , BLACK );

        SubItens( sel );

//        Sleep( DELAY );       // O beep ja causa um delay.Nao precisa mais.
}
///
void Itens( Selecao sel )
{
        int i , j;
        int corN[3] ={ GREEN , BROWN , CYAN } , fund[3] = { WHITE , WHITE , WHITE };
        char *nomes[ 3 ] = {
                "Tri\203ngulos",
                "Vector Intercec\207\306o",
                "Notas"
        };

        //Nomes do Itens e descricao
        for( i = 1 ; i < 4 ; i++)
        {
                textcolor( BLACK );
                textbackground( WHITE );

                //Fundo branco do item
                for( j = 1 ; j < 2 * sel.tamLQ - 1 ; j++)
                        putchxy(  sel.posQ[ i ].X + j  , sel.posQ[ i ].Y + 1 , ' ' );

                //Numero do item
                gotoxy( 1+ sel.posQ[ i ].X + ( 2 * sel.tamLQ - 2 - strlen("QUEST\307O X") ) / 2 , sel.posQ[ i ].Y + 1 );
                printf("QUEST\307O %d" , i );
                textbackground( BLACK );

                //Descricao
                textcolor( corN[ i - 1] );
                gotoxy( 1 + sel.posQ[ i ].X + ( 2 * sel.tamLQ - 2 - strlen( nomes[ i - 1 ] ) ) / 2 , sel.posQ[ i ].Y + 2 );
                printf( nomes[ i - 1] );

                textcolor( WHITE );
                textbackground( BLACK );
        }

        //Item Sair
        gotoxy( sel.posS.X + 1 + ( sel.tamLS - 2 - strlen("SAIR") ) / 2 , sel.posS.Y + 1 );

        textcolor( BROWN );
        printf("SAIR");
        textcolor( WHITE );

        //Desenhos
        desenhosItem1( sel );
        desenhosItem2( sel );
        desenhosItem3( sel );

}
///
void SubItens( Selecao sel )
{
        if( sel.subitem )
        {
                int xpp = sel.posQ[ sel.item ].X;
                int ypp = sel.posQ[ sel.item ].Y + sel.tamLQ;

                int cor1 , cor2;
                ( sel.subitem == 1 )  ?  (cor1 = GRAY_BRUSH , cor2 = BLACK ) : ( cor1 = BLACK , cor2 = GRAY_BRUSH);

                Retang( xpp , ypp , sel.tamLQ , 3 , WHITE , cor1 );
                cputsxy( xpp + 1 + ( sel.tamLQ - 2 - strlen("VER CODIGO") ) / 2 , ypp + 1 , "VER CODIGO");

                Retang( xpp + sel.tamLQ , ypp , sel.tamLQ , 3 , WHITE , cor2 );
                cputsxy( xpp + 1 + sel.tamLQ + ( sel.tamLQ - 2 - strlen("EXECUTAR") ) / 2 , ypp + 1 , "EXECUTAR");
        }
        else
        {
                int y = sel.posQ[ 1 ].Y + sel.tamLQ;

                RetangM( 3 , y , sel.casasMonitor.X - 3  , 3 , ' ' , BLACK , BLACK );
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
                {"| _ \\ _ \\   /_\\  |_   _|_ _| / __| /_\\    /  | /  \\"},
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

///
void limpaTela( void )
{
        clrscr();
}

///
int TelaEmFoco( Selecao sel )
{
        if( sel.janela == GetForegroundWindow() )       //Se a janela mais em destaque for a salva na inicializacao do programa (que e a janela do programa), entao retorna 1
                return 1;
        else
                return 0;

}

///
void carregando( Selecao sel )
{
        char *msg = "CARREGANDO >>>";
        cputsxy( ( sel.casasMonitor.X - strlen( msg ) ) / 2 , sel.casasMonitor.Y / 2  , msg );

        char *msg2 = "(Dica: Utilize as setas do teclado ou o mouse no menu)";
        cputsxy( ( sel.casasMonitor.X - strlen( msg2 ) ) / 2 , sel.casasMonitor.Y / 2 + 9  , msg2 );


}

///
void ResoluMonitor( COORD *tamanho )
{
        tamanho->X = GetSystemMetrics(SM_CXSCREEN);
        tamanho->Y = GetSystemMetrics(SM_CYSCREEN);
}

///
void desenhosItem1( Selecao sel )
{
        #define QY1 14
        char des1[QY1][ 40 ] = {
                " \302",
                " \263 \263\134",
                " \263 \263 \134",
                " \263 \263  \134",
                " \263 \263   \134",
                " \263 \263    \134  c       TIPO=?",
                "b\263 \263     \134         \265REA=?",
                " \263 \263      \134",
                " \263 \263       \134",
                " \263 \263        \134",
                " \263 \263         \134",
                " \301 \300\304\304\304\304\304\304\304\304\304\304",
                "   \303\304\304\304\304\304\304\304\304\304\304\264",
                "        a"
        };

        int i , j;
        int x0 = sel.posQ[ 1 ].X + 7  * sel.escalaX;
        int y0 = sel.posQ[ 1 ].Y + 1 + ( sel.tamLQ - QY1 ) / 2;

        textcolor( GREEN );

        for( i = 0 ; i < QY1 ; i++ )
                for( j = 0 ; j < strlen( des1[ i ] ) ; j++ )
                {
                        gotoxy( x0 + j , y0 + i );
                        printf("%c" , des1[ i ][ j ]);
                }

        textcolor( WHITE );

}

void desenhosItem2( Selecao sel )
{
        #define QY2 5
        char des1[QY2][ 20 ] = {
                "  A: \304\304\304\304\304\304\304\304>",
                "",
                "  B:     \304\304\304\304\304\304\304\304\304>",
                "",
                "INT:     \304\304\304\304>"
        };

        int i , j;
        int cor;
        int x0 = sel.posQ[ 2 ].X + 12  * sel.escalaX;
        int y0 = sel.posQ[ 2 ].Y + sel.tamLQ / 2 - 2;


        for( i = 0 ; i < QY2 ; i++ )
                for( j = 0 ; j < strlen( des1[ i ] ) ; j++ )
                {
                        cor = ( i == 0 ) ? BROWN : ( ( i == 2 ) ? BLUE : GREEN );
                        textcolor( cor );
                        gotoxy( x0 + j , y0 + i );
                        printf("%c" , des1[ i ][ j ]);
                }

        textcolor( WHITE );

}

void desenhosItem3( Selecao sel )
{
        #define QY3 14
        //Item 1
        char des1[QY3][ 20 ] = {
                "\332\304\304\304\304\304\304\304\304\304\304\304\277",
                "\263  ARAUJO   \263",
                "\263           \263",
                "\263 Nota1...  \263",
                "\263 Nota2...  \263",
                "\263 Nota3...  \263",
                "\263 Nota4...  \263",
                "\263 NotaF...  \263",
                "\263           \263",
                "\263  100: A   \263",
                "\300\304\304\304\304\304\304\304\304\304\304\304\331",

        };
        char des2[QY3][ 20 ] = {
                "\332\304\304\304\304\304\304\304\304\304\304\304\277",
                "\263  OJUARA   \263",
                "\263           \263",
                "\263 Nota1...  \263",
                "\263 Nota2...  \263",
                "\263 Nota3...  \263",
                "\263 Nota4...  \263",
                "\263 NotaF...  \263",
                "\263           \263",
                "\263   49: F   \263",
                "\300\304\304\304\304\304\304\304\304\304\304\304\331",

        };

        int i , j;
        int cor;
        int x0 = sel.posQ[ 3 ].X + 1;
        int y0 = sel.posQ[ 3 ].Y + sel.tamLQ / 2 - 4;
        int space = (2 * sel.tamLQ - 2 - 2 * 13) / 3;


        for( i = 0 ; i < QY3 ; i++ )
                for( j = 0 ; j < strlen( des1[ i ] ) ; j++ )
                        {
                                cor = YELLOW;
                                if( i == 9  &&  j > 1  &&  j <12 )      cor = GREEN;
                                textcolor( cor );
                                gotoxy( x0 + space + j , y0 + i );
                                printf("%c" , des1[ i ][ j ]);
                        }

        for( i = 0 ; i < QY3 ; i++ )
                for( j = 0 ; j < strlen( des2[ i ] ) ; j++ )
                        {
                                cor = YELLOW;
                                if( i == 9  &&  j > 1  &&  j <12 )      cor = RED;
                                textcolor( cor );
                                gotoxy( x0 + 13 + 2 * space + j , y0 + i );
                                printf("%c" , des2[ i ][ j ]);
                        }


        textcolor( WHITE );

};

///
void Hasta( Selecao sel )
{
        char *msg = "\255HASTA LA VISTA!";

        clrscr();
        gotoxy( ( sel.casasMonitor.X - strlen( msg ) ) / 2 , sel.casasMonitor.Y / 2 ) ;
        printf( msg );
        Sleep( 1300 );

        //Sair logo
        keybd_event( VK_RETURN , 0 , 0 , 0 );
        Sleep( 200 );
        keybd_event( VK_RETURN , 0 , KEYEVENTF_KEYUP , 0 );
}


///
void AtualizaMenuMouse( Selecao *sel )
{

        GetCursorPos( &sel->posMouse );
        ScreenToClient( sel->janela , &sel->posMouse);

        int i , j;
        //Inicializacao das coordenadas dos retangulos dos itens e sub itens
        const int x0[] =  { 111 * ESCX , 513 * ESCX , 913 * ESCX } , xf[] = { 431 * ESCY , 830 * ESCX , 1230 * ESCX };
        int  y0[3] , yf[3];
        const int x0S = 1186 * ESCX , xfS= 1343 * ESCX , y0S = 678 * ESCY , yfS = 714 * ESCY;
        int y0s[ 2 ] , yfs[ 2 ];
        y0[ 0 ] = y0[ 1 ] = y0[ 2 ] =  255 * sel->escalaY;  //Alturas iniciais iguais dos itens principais
        yf[ 0 ]  = yf[ 1 ] = yf[ 2 ] =  573 * sel->escalaY;    //Alturas finais iguais dos itens principais
        y0s[ 0 ] = y0s[ 1 ] = 581 * sel-> escalaY;
        yfs[ 0 ] = yfs[ 1 ] = 622 * sel->escalaY;

        //Quadrados questoes 1 , 2 , 3
        for( i = 0 ; i < 3 ; i++ )
                if( ColisMouseRetang( x0[ i ] , xf[ i ] , y0[ i ] , yf[ i ] , *sel ) ){
                        AlteraItemMouse( sel , i + 1 );
                       if( GetAsyncKeyState( VK_LBUTTON ) )
                        {
                                sel->subitem = 1;
                                sel->alterou = 1;
                        }
                }


        //Retangulo sair
        if( ColisMouseRetang( x0S , xfS , y0S , yfS , *sel) ){
                AlteraItemMouse( sel , 4);
                if( GetAsyncKeyState( VK_LBUTTON ) )
                {
                        sel->sair = 1;
                        sel->alterou = 1;
                }
        }


        //Retangulos Subitens
        if( sel->subitem ){
                if( ( ( sel->posMouse.x >= 112 * sel->escalaX  &&  sel->posMouse.x < 270 * sel->escalaX )  ||  ( sel->posMouse.x >= 512 * sel->escalaX  &&  sel->posMouse.x < 670 * sel->escalaX )  ||  ( sel->posMouse.x >= 913 * sel->escalaX  &&  sel->posMouse.x < 1070 * sel->escalaX ) )  &&  sel->posMouse.y >= 581 * sel->escalaY  &&  sel->posMouse.y < 622 * sel->escalaY )
                {
                        if( sel->subitem != 1 )
                        {
                                sel->subitem = 1;
                                sel->alterou = 1;
                        }

                        if( GetAsyncKeyState( VK_LBUTTON ) ){
                                sel->entrar = 1;
                                sel->alterou = 1;
                        }

                }

                if( ( ( sel->posMouse.x >= 270 * sel->escalaX  &&  sel->posMouse.x < 429 * sel->escalaX )  ||  ( sel->posMouse.x >= 670 * sel->escalaX  &&  sel->posMouse.x < 831 * sel->escalaX )  ||  ( sel->posMouse.x >= 1070 * sel->escalaX  &&  sel->posMouse.x < 1232 * sel->escalaX ) )  &&  sel->posMouse.y >= 581 * sel->escalaY  &&  sel->posMouse.y < 622 * sel->escalaY )
                {
                        if( sel->subitem != 2 )
                        {
                                sel->subitem = 2;
                                sel->alterou = 1;
                        }

                        if( GetAsyncKeyState( VK_LBUTTON ) ){
                                sel->entrar = 1;
                                sel->alterou = 1;
                        }

                }
        }
}


int ColisMouseRetang( int x0 , int xf , int y0 , int yf , Selecao sel)
{
        if( sel.posMouse.x >= x0   &&  sel.posMouse.x < xf   &&  sel.posMouse.y >= y0   &&  sel.posMouse.y < yf  )
                return 1;

        return 0;
}

int AlteraItemMouse( Selecao *sel , int nmrItem )
{
        if( sel->item != nmrItem )
        {
                sel->item = nmrItem;
                sel->subitem = 0;
                sel->alterou = 1;
        }
}


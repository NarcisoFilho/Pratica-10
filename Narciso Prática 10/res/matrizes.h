/// MATRIZES.h
///Narciso Filho
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <conio2.h>
#include <windows.h>

#define ESP 10

#define CRIAR 2
#define ALTERAR 1
#define CONSULTAR 0
#define ATIVA 1
#define DESATIVADA 0

//#define COR_L 10
//#define COR_ML 6
//#define COR_MD 1
//#define COR_COORD 4

///Estruturas
struct matriz
{
        int **ptr;
        int lins;
        int cols;
        int POSX;
        int POSY;
};

struct comando
{
        int i;
        int IMAX;
        int j;
        int JMAX;
        int Sair;
        int Alterar;
};

struct cor
{
        int texto;
        int fundo;
};


///Protótipos
struct matriz *Matrizes( int identificador );
void RegistraMatriz( /*int *dados , int lins , int cols , int identificador*/ );
//void DestroiMatriz( int identificador );
struct matriz MontaTabela( int lins , int cols);
int tamLT( int lins );
int tamCT( int cols );
void PrintMatrizXY( int identificador , int x , int y);
void PrintTabela( int identificador , int x , int y );
void PrintDados( int identificador , int x , int y );
void RandMatriz( int identificador , int LimInf , int LimSup  );
int status( int tecla );
int StatusTeclaNumerica( void );
void AcoesNaMatriz( struct comando *anterior);
void InicializarComando(struct comando *comd , int identificador );
void ColetarElemento( int identificador , struct comando atual);
void PreencherMatriz( int identificador);
void ApagarElemento( int identificador , int i , int j );
void ReescreverElemento( int identificador , int i , int j );
void ColorirElemento( int identificador , int i , int j , int CorTexto , int CorFundo );
int tamN( int num );
void Backspace( int identificador , struct comando atual);
void NegativarElemento( int identificador , struct comando atual);
void Delete( int identificador , struct comando atual);
float Media( int identificador );
int SomaTotal( int identificador );
void limpaBuffer( void );
int registro( int identificador , int operacao , int entrada );
struct cor registroCores( int identificador , int operacao , int i , int j , int texto , int fundo);
void restauraCoresSaida( void );
void esconderCursor( void );
void exibirCursor( void );
int totalVertical( int identificador , int coluna );


///teste
//int main()
//{
//        int dados[ 3 ][ 5 ] = { {1 , 2 , 3 , 4 , 5} ,{ 6 , 7 , 8 , 9 , 10} ,{ 11 , 12 , 13 , 14 , 15} };
//
//        RegistraMatriz( dados , 3 , 5 , 1 );
//
//        RandMatriz( 1 , 5 , 77);
//
//        PrintMatrizXY( 1 , 15 , 7);
//        getch();
////        registroCores( 1 , ALTERAR , -1 , 0 , 14 , 3 );
//        PreencherMatriz(1);
//
////        printf("\n\n> %d <\n" , SomaTotal(1) );
////        printf("\n> %f <\n" , Media(1) );
//
//        getch();
//
//        registroCores( 1 , ALTERAR , 1 , 3 , 0 , 15);
//        registroCores( 1 , ALTERAR , -2 , 3 , 0 , 15);
//        PrintMatrizXY( 1 , 15 , 7);
//        PreencherMatriz(1);
//
//
//        return 0;
//}
//###################################################################







/**     Matrizes : Mantém salva as matriz para uso das funções da biblioteca.
    *                           identificador -> Número da matriz. De 1 a QTDMATRIZES
    *
    *                           RETORNO: Ponteiro para struct matriz da matriz 'identificador'
    */
#define QTDMATRIZES 5
struct matriz *Matrizes( int identificador )
{
        static struct matriz Mat[ QTDMATRIZES ];

        return &Mat[ identificador ];
}
//###################################################################



/**     RegistraMatriz : Grava uma matriz em Matrizes() para uso das funções da biblioteca.
    *                           **ptr -> Matriz de dados a ser gravada
    *                           lins -> Quantidade de linhas de dados
    *                           cols -> Quantidade de colunas de dados
    *                           identificador -> Número da matriz. De 1 a @QTDMATRIZES
    */
void RegistraMatriz( int *dados , int lins , int cols , int identificador )
{
        struct matriz *Mat;
        int **ptr;

        ptr = (int **)dados;        Mat = Matrizes( identificador );
        Mat->ptr = ptr;
        Mat->lins = lins;
        (*Mat).cols = cols;

        registro( identificador , ALTERAR , ATIVA);
        registroCores( identificador , CRIAR , 0 , 0 , 0 , 0);
}

//###################################################################



///**     DestroiMatriz : Destroi uma matriz em Matrizes() para liberar memória.
//    *                           identificador -> Número da matriz a ser destruída. De 1 a @QTDMATRIZES.
//    */
//#define CLRALL -1
void DestroiMatriz( int identificador )
{
        registro( identificador , ALTERAR , DESATIVADA );
//        struct matriz *Mat;
//        int i , k , fim = identificador + 1;
//
//        //Caso CLRALL
//        if( identificador == CLRALL)
//        {
//                identificador = 0;
//                fim = QTDMATRIZES;
//        }
//
//        for( k = identificador ; k < fim ; k++ )
//        {
//                //Recebe matriz Mat de Matrizes
//                Mat = Matrizes( identificador );
//
//                //Libera ponteiro para colunas
//                for( i = 0 ; i < Mat->lins ; i++)
//                        free( Mat->ptr[ i ] );
//
//                //Libera ponteiro de ponteiro
//                free(Mat->ptr);
//        }
//
}
//###################################################################



/**     MontaTabela : Monta o desenho de uma tabela com espaços para 'lins' linhas e 'cols' colunas de dados
    *                           lins -> Quantidade de linhas de dados
    *                           cols -> Quantidade de colunas de dados
    */
struct matriz MontaTabela( int lins , int cols)
{
        //  179 : │   180 : ┤  191: ┐   192 :  └     193 : ┴       194 :  ┬    195 : ├      196 : ─     197 : ┼     217 :  ┘    218 :  ┌
        int QtdLins = tamLT( lins ) , QtdCols = tamCT( cols );
        int **tabela;
        int i , j;
        struct matriz retorno;

        tabela = (int **) malloc( QtdLins * sizeof( int * ) );
        for(i = 0 ; i < QtdLins ; i++)
                tabela[ i ] = (int *) malloc( QtdCols * sizeof( int ) );

        //Meio da Tabela
        for(i = 1 ; i < QtdLins - 1; i++)
                for(j = 1 ; j < QtdCols - 1 ; j++)
                        if(i % 2)
                                tabela[ i ][ j ] = ( j % (ESP + 1) ) ? 32 : 179 ;
                        else
                                tabela[ i ][ j ] = ( j % (ESP + 1) ) ? 196 : 197 ;

        // Top + Bottom
        for(j = 1 ; j < QtdCols - 1 ; j++){
                        tabela[ 0 ][ j ] = ( j % (ESP + 1) ) ? 196 : 194 ;
                        tabela[ QtdLins - 1 ][ j ] = ( j % ( ESP + 1 ) ) ? 196 : 193 ;
                }

        // Left + Right
        for(i = 1 ; i < QtdLins - 1 ; i++){
                tabela[ i ][ 0 ] = (i % 2) ? 179 : 195 ;
                tabela[ i ][ QtdCols - 1 ] = ( i % 2 ) ? 179 : 180 ;
        }

        // Squares
        tabela[ 0 ][ 0 ] = 218;    //TL
        tabela[ 0 ][ QtdCols - 1 ] = 191;   //TR
        tabela[ QtdLins - 1 ][ 0 ] = 192;   //BL
        tabela[ QtdLins - 1 ][ QtdCols - 1 ] = 217;   //BR

        retorno.ptr = tabela;
        retorno.lins = QtdLins;
        retorno.cols = QtdCols;

        return retorno;
}
//###################################################################



/**     PrintMatrizXY : Combinação de PrintTabela com PrintDados
    *                           ptr*-> Posição de memória do elemento [ 0 ][ 0 ] da matriz de dados
    *                           lins -> Quantidade de linhas da matriz dos dados
    *                           cols -> Quantidade de colunas da matriz dos dados
    *                           x -> Coordenada x do ponto superior esquerdo da tabela
    *                           y -> Coordenada y do ponto superior esquerdo da tabela
    */
void PrintMatrizXY( int identificador , int x , int y)
{
        struct matriz *ptr ;

        ptr =Matrizes( identificador );
        ptr->POSX = x;
        ptr->POSY = y;

        PrintTabela( identificador ,  x ,  y);
        PrintDados( identificador , x , y);
}
//###################################################################



/**     PrintTabela : Imprime tabela
    *           ->Entrada:
    *                           lins -> Quantidade de linhas de dados
    *                           cols -> Quantidade de colunas de dados
    */
void PrintTabela( int identificador , int x , int y )
{
        struct matriz *Mat = Matrizes( identificador );
        struct matriz Tabela = MontaTabela( Mat->lins , Mat->cols );
        int i , j;
        struct cor cores;

        //Cor
        cores = registroCores( identificador , CONSULTAR , -2 , 0 , 0 , 0 );
        textcolor( cores.texto );
        textbackground( cores.fundo );

        //Tabela
        for(i = 0 ; i < Tabela.lins ; i++)
                for(j = 0 ; j < Tabela.cols ; j++)
                {
                        gotoxy( x +  j , y + i );
                        printf("%c" , Tabela.ptr[ i ][ j ] );
                }

        restauraCoresSaida();
}
//###################################################################



/**     PrintDados : Imprime matriz de dados em x,y
    *           ->Entrada:
    *                           identificador-> Identificador(number ) da matriz de dados em matrizes
    *                           x -> Coordenada x do ponto superior esquerdo da tabela
    *                           y -> Coordenada y do ponto superior esquerdo da tabela
    */
void PrintDados( int identificador , int x , int y )
{
        struct matriz *Mat;
        int k;
        struct cor cores;

        //Chamando Matrizes
        Mat = Matrizes( identificador );

        //Dados
        for( k = 0 ; k < Mat->lins * Mat->cols ; k++)
        {
                //Cor
                cores = registroCores( identificador , CONSULTAR , k / Mat->cols , k % Mat->cols , 0 , 0 );
                textcolor( cores.texto );
                textbackground( cores.fundo );

                gotoxy( x +  (ESP + 1) *  (  k % Mat->cols) + (ESP - 1) / 2  + 1  , y + ( k / Mat->cols) * 2  + 1 );
                printf("%d" , *( (int *)Mat->ptr + k ) );
        }
        restauraCoresSaida();
}
//###################################################################



/**     tamLT :
    *           ->Entrada: Quantidade de linhas da matriz dos dados
    *           ->Saída: Quantidade de linhas da matriz completa com tabela
    */
int tamLT( int lins )
{
        return 2 * lins + 1;
}
//###################################################################



/**     tamCT :
    *           ->Entrada: Quantidade de colunas da matriz dos dados
    *           ->Saída: Quantidade de colunas da matriz completa com tabela
    */

int tamCT( int cols )
{
        return  (ESP + 1) * cols + 1 ;
}
//###################################################################



/**    RandMatriz : Prennche randômicamente matriz
    *           ->Entrada: Identificador da Matriz , Limite Inferior dos valores , Limite Superiror dos valores
    *
    *
    */

void RandMatriz( int identificador , int LimInf , int LimSup  )
{
        int i , j;
        struct matriz *Mat;
//        int *ponteiro;

        //Alterando SEED
        srand( time( NULL) );

        //Recebendo Matriz
        Mat = Matrizes( identificador );

//                ponteiro = (int *)Mat->ptr;
        //Atribuindo Valores Aleatórios por referência
                for(i = 0 ; i < Mat->lins ; i++)
                        for(j = 0 ; j < Mat->cols ; j++)
//                                *ponteiro[ i ][ j ] = LimInf + rand() % ( LimSup + 1 - LimInf);
                                *( (int *)Mat->ptr + Mat->cols * i +  j ) = LimInf + rand() % ( LimSup + 1 - LimInf);

//        int k;
//        for( k = 0 ; k < Mat->lins * Mat->cols ; k++)
//                        *( (int *)Mat->ptr + k) = LimInf + rand() % ( LimSup + 1 - LimInf);

}
//###################################################################



/**     PreencherMatriz : Permite o usuário preencher manualmente matriz
    *           ->Entrada: Identificador da Matriz
    *
    *
    */

void PreencherMatriz( int identificador)
{
        struct comando atual;
        struct cor selecao , elementoCor;
        int iAnt , jAnt;

        selecao = registroCores( identificador , CONSULTAR , -1 , 0 , 0 , 0);

        InicializarComando( &atual , identificador);

        ColorirElemento( identificador , atual.i , atual.j , selecao.texto , selecao.fundo );
        do
        {

                iAnt = atual.i;
                jAnt = atual.j;

                AcoesNaMatriz( &atual );


                if( atual.i - iAnt + atual.j - jAnt )
                {
                        esconderCursor();
                        elementoCor = registroCores( identificador , CONSULTAR , iAnt , jAnt , 0 , 0);
                        ColorirElemento( identificador , atual.i , atual.j , selecao.texto , selecao.fundo );
                        ColorirElemento( identificador , iAnt , jAnt , elementoCor.texto , elementoCor.fundo );
                }

                //Inserir número
                if( atual.Alterar >= 0  && atual.Alterar <= 9 )
                {
                        ColetarElemento( identificador , atual );
                        atual.Alterar = -1;
                }

                //Backspace
                if( atual.Alterar == 10)
                {
                        Backspace( identificador , atual );
                        atual.Alterar = -1;
                }

                //Delete
                if( atual.Alterar == 12)
                {
                        Delete( identificador , atual );
                        atual.Alterar = -1;
                }

                //Negativar
                if( atual.Alterar == 11)
                {
                        NegativarElemento( identificador , atual );
                        atual.Alterar = -1;
                }

                Sleep(50);
        }
        while( atual.Sair != 1 );


        limpaBuffer();

        //Reimprimir para sumir fundo cinza e contornar problema do getchar() de limpa
        //              Buffer() exibindo caracteres no meio da tabela depois do enter  .
        PrintMatrizXY( identificador , Matrizes(identificador)->POSX , Matrizes(identificador)->POSY );

        getch();
        return;
}
//###################################################################



/**     status : Status de pressionamento da tecla
    *           ->Entrada: Tecla
    *
    *
    */
int status( int tecla )
{
        return ( GetAsyncKeyState( tecla ) & 0x8000 );
}
//###################################################################



/**     AcoesNaMatriz : Permite o usuário percorrer com as setas do teclado a matriz
    *                                                            e sair do loop de prenchimento com tecla 'ESC'
    *           ->Entrada: struct comando
    *
    *
    */

void AcoesNaMatriz( struct comando *anterior )
{
        if( status( VK_LEFT ) )
                if( anterior->j > 0 )
                {
                        -- anterior->j ;
                        return;
                }

        if( status( VK_RIGHT ) )
                if( (anterior->j) < (anterior->JMAX) )
                {
                        ++ anterior->j ;
                        return;
                }

        if( status( VK_UP ) )
                if( anterior->i > 0 )
                {
                        -- anterior->i ;
                        return;
                }


        if( status( VK_DOWN ) )
                if( anterior->i < anterior->IMAX )
                {
                        ++ anterior->i;
                        return;

                }

        if( status( VK_ESCAPE )  || status( VK_RETURN ) )
        {
                anterior->Sair = 1 ;
                        return;
        }


        anterior->Alterar = StatusTeclaNumerica();
        return;

}
//###################################################################



/**     StatusTeclaNumerica: Status de pressionamento de tecla numerica
    *
    */

int StatusTeclaNumerica( void )
{
        //Teclas de 0 a 9 no NUMPADe no lado esquerdo  do teclado do
        if( status( 0x30 ) || status( 0x60 ) )
                return 0;

        if( status( 0x31 ) || status( 0x61 ) )
                return 1;

        if( status( 0x32 ) || status( 0x62 ) )
                return 2;

        if( status( 0x33 ) || status( 0x63 ) )
                return 3;

        if( status( 0x34 ) || status( 0x64 ) )
                return 4;

        if( status( 0x35 ) || status( 0x65 ) )
                return 5;

        if( status( 0x36 ) || status( 0x66 ) )
                return 6;

        if( status( 0x37 ) || status( 0x67 ) )
                return 7;

        if( status( 0x38 ) || status( 0x68 ) )
                return 8;

        if( status( 0x39 ) || status( 0x69 ))
                return 9;

        //BackSpace
        if( status( VK_BACK )  )
                return 10;

        //Negativar / Desnegativar
        if( status( 0xBD )  ||  status( VK_SUBTRACT ) )
                return 11;

        //Limpar(Delete)
        if( status( VK_DELETE ) )
                return 12;

        return -1;
}


//###################################################################



/**     InicializarComando : Zera os campos da variável comd , que é um struct comando
    *           ->Entrada: *comd ; Um ponteiro para a variárivel tipo comando
    */

void InicializarComando(struct comando *comd , int identificador )
{
        comd->i = 0;
        comd->IMAX = ( Matrizes( identificador ) )->lins - 1;
        comd->j = 0;
        comd->JMAX = ( Matrizes( identificador ) )->cols - 1;
        comd->Sair = 0;
        comd->Alterar = -1;
}
//###################################################################


/**     ColetarElemento : Coleta numero para elemento Aij para matriz de dados
    *           ->Entrada: Identificador e Struct comando atual
    */
void ColetarElemento( int identificador , struct comando atual)
{
        struct matriz *Mat = Matrizes( identificador );
        int i = atual.i , j = atual.j;
        char elementoString[ 1 + tamN( *( (int *)Mat->ptr + Mat->cols * i +  j ) ) ];
        char entradaString[1];

        exibirCursor();
        entradaString[ 0 ] = atual.Alterar + 48;
        itoa( *( (int *)Mat->ptr + Mat->cols * i +  j ) , elementoString , 10 );
        strcat( elementoString , entradaString );
        *( (int *)Mat->ptr + Mat->cols * i +  j ) = atoi( elementoString );

        ApagarElemento( identificador , i , j);

        ReescreverElemento( identificador , i , j );

}
//###################################################################



/**     NegativarElemento : Negativa elemento Aij para matriz de dados
    *           ->Entrada: Identificador e Struct comando atual
    */
void NegativarElemento( int identificador , struct comando atual)
{
        struct matriz *Mat = Matrizes( identificador );
        int i = atual.i , j = atual.j;

        *( (int *)Mat->ptr + Mat->cols * i +  j ) *= -1;

        ApagarElemento( identificador , i , j);

        ReescreverElemento( identificador , i , j );
}
//###################################################################



/**     Backspace : Apaga dígito de numero do elemento Aij para matriz de dados
    *           ->Entrada: Identificador e Struct comando atual
    */
void Backspace( int identificador , struct comando atual)
{
        struct matriz *Mat = Matrizes( identificador );
        int i = atual.i , j = atual.j;
        char elementoString[ 1 + tamN( *( (int *)Mat->ptr + Mat->cols * i +  j ) ) ];

        itoa( *( (int *)Mat->ptr + Mat->cols * i +  j ) , elementoString , 10 );
        elementoString[ strlen( elementoString ) -1 ] = '\0';
        *( (int *)Mat->ptr + Mat->cols * i +  j ) = atoi( elementoString );

        ApagarElemento( identificador , i , j);

        ReescreverElemento( identificador , i , j );
}
//###################################################################



/**     Delete : Apaga primeiro dígito de numero do elemento Aij para matriz de dados
    *           ->Entrada: Identificador e Struct comando atual
    */
void Delete( int identificador , struct comando atual)
{
        struct matriz *Mat = Matrizes( identificador );
        int i = atual.i , j = atual.j;
        char elementoString[ 1 + tamN( *( (int *)Mat->ptr + Mat->cols * i +  j ) ) ];
        int k;

        itoa( *( (int *)Mat->ptr + Mat->cols * i +  j ) , elementoString , 10 );

        for( k = 0 ; k < strlen( elementoString )  ; k++)
                elementoString[ k ] = elementoString[ k + 1];

        *( (int *)Mat->ptr + Mat->cols * i +  j ) = atoi( elementoString );

        ApagarElemento( identificador , i , j);

        ReescreverElemento( identificador , i , j );
}
//###################################################################



/**     ReescreverElemento : Reescreve elemento de matriz
    *           ->Entrada: Identificador, i e j do elemento[ i ][ j ]
    */
void ReescreverElemento( int identificador , int i , int j )
{
        struct matriz *Mat = Matrizes( identificador );

        ApagarElemento( identificador , i , j );

        gotoxy( Mat->POSX + tamCT( j ) + (ESP - 1) / 2 , Mat->POSY + tamLT( i ) );
        printf("%d", *( (int *)Mat->ptr + Mat->cols * i +  j ) );
}
//###################################################################



/**     ApagarElemento : Apaga elemento de matriz
    *           ->Entrada: Identificador, i e j do elemento[ i ][ j ]
    */
void ApagarElemento( int identificador , int i , int j )
{
        struct matriz *Mat = Matrizes( identificador );
        int k;

        gotoxy( Mat->POSX + tamCT( j )  , Mat->POSY + tamLT( i ) );

        for( k = 0 ; k < ESP ; k++ )
                printf(" ");
}
//###################################################################




/**     ColorirElemento : Colore elemento 'temporiamente' de matriz
    *           ->Entrada: Identificador, i e j do elemento[ i ][ j ]
    */
void ColorirElemento( int identificador , int i , int j , int CorTexto , int CorFundo )
{
//              struct matriz *Mat = Matrizes( identificador );

        ApagarElemento( identificador , i , j );

        textcolor( CorTexto );
        textbackground( CorFundo );

        ReescreverElemento( identificador , i , j);

        restauraCoresSaida();

        return;
}
//###################################################################



/**     tamN : Tamanho de número
    *           ->Entrada: num
    */
int tamN( int num )
{
        int tam = 0;

        do
        {
                num /= 10;
                tam++;
        }
        while( num );


        return tam;
}
//###################################################################



/**     SomaTotal : Soma de todos os elementos
    *           ->Entrada: identificador
    */
int SomaTotal( int identificador )
{
        struct matriz *Mat = Matrizes( identificador );
        int i , j = 0;
        int soma = 0;

        for( i = 0 ; i < Mat->lins ; i++ )
                for( j = 0 ; j < Mat->cols ; j++ )
                        soma += *( (int *)Mat->ptr + i * Mat->cols + j);



        return soma;
}
//###################################################################



/**     Media : Media dos elementos
    *           ->Entrada: identificador
    */
float Media( int identificador )
{
        struct matriz *Mat = Matrizes( identificador );
        float media;

        media = (float)SomaTotal( identificador ) / (Mat->lins * Mat->cols);

        return media;
}
//###################################################################



/**     limparBuffer : Função para limpar buffer do teclado
    */
void limpaBuffer( void )
{
        char c;

        textcolor(0);
        while( ( c = getchar() ) != '\n'  && c != EOF );
        textcolor(15);

        return;
}
//###################################################################



/**     restauraCoresSaida : Restaura Padrão de saída
    *
    */
void restauraCoresSaida( void )
{
        textcolor( 15 );
        textbackground( 0 );
}
//###################################################################



/**     registroCores : Função que armazena cores das estruturas e elementos
    *           @caso tabela i -2,  @caso selecao i = -1
    */
#define QTDCORES 20
#define CORTEXTO 15
#define CORFUNDO 0
#define CORTABELA 15
#define CORTABFUNDO 0
#define CORSELECAO 1
#define CORSELECAOFUNDO 8

struct cor registroCores( int identificador , int operacao , int i  , int j , int texto , int fundo)
{
        static char ***coresElementos[QTDMATRIZES] = { NULL }  ;
        static char tabela[ 2 ] , selecaoLeitura[ 2 ];
        struct cor retorno;
        int kcont , icont , jcont ;
        struct matriz *Mat = Matrizes(identificador);

        //Caso de retorno para operação de consulta
        retorno.texto = -1;
        retorno.fundo = -1;

        switch( operacao)
        {
                case CRIAR :

                        coresElementos[ identificador ] = (char ***) malloc( 2 * sizeof(  char** ) ); //Matriz 3d , 2 de altura( k = 0 Cor texto , k = 1 Cor fundo)
                        printf("%d",coresElementos[ identificador ]);


                        for( kcont = 0 ; kcont <= 1 ; kcont++)
                                coresElementos[ identificador ][ kcont ] = (char **) malloc( Mat->lins * sizeof(  char* ) );  //Linhas

                        for( kcont = 0 ; kcont <= 1 ; kcont++)
                                for( i = 0 ; icont < Mat->lins ; icont++)
                                        coresElementos[ identificador ][ kcont ][ icont ] = (char *) malloc( 1 + Mat->cols * sizeof( char ) );  //Colunas(elementos)

                        //Definindo Cor Padrão do Texto
                        for( icont = 0 ; icont < Mat->lins ; icont++)
                                for( jcont = 0 ; jcont < Mat->cols ; jcont++)
                                        *( (int *)coresElementos[ identificador ] + 0 + icont * Mat->cols + jcont ) = CORTEXTO;
//                                        coresElementos[ identificador ][ 0 ][ icont ][ jcont ] = (char)CORTEXTO;

                        //Definindo Cor Padrão do Fundo
                        for( icont = 0 ; icont < Mat->lins ; icont++)
                                for( jcont = 0 ; jcont < Mat->cols ; jcont++)
                                        *( (int *)coresElementos[ identificador ] + Mat->lins * Mat->cols  + icont * Mat->cols + jcont ) = CORFUNDO;
//                                        coresElementos[ identificador ][ 1 ][ icont ][ jcont ] = CORFUNDO;

                        tabela[ 0 ] = CORTABELA;
                        tabela[ 1 ] = CORTABFUNDO;
                        selecaoLeitura[ 0 ] = CORSELECAO;
                        selecaoLeitura[ 1 ] = CORSELECAOFUNDO;
                        return retorno;

                case ALTERAR :
                        switch( i )
                        {
                                case -2 :
                                        tabela[ 0 ] = texto;
                                        tabela[ 1 ] = fundo;
                                        return retorno;
                                case -1 :
                                        selecaoLeitura[ 0 ] = texto;
                                        selecaoLeitura[ 1 ] = fundo;
                                        return retorno;
                        }
                        if( i >= 0  &&  i <= Mat->lins )
                                if( j >= 0  &&  j <= Mat->cols )
                                {
                                        *( (int *)coresElementos[ identificador ] + 0 + i * Mat->cols + j ) = texto;
                                        *( (int *)coresElementos[ identificador ] + Mat->lins * Mat->cols  + i * Mat->cols + j ) = fundo;
                                        return retorno;
                                }
                        //Retorno em caso de problemas de i ou j inválidos
                        retorno.texto = -8;
                        retorno.fundo = -8;
                        return retorno;

                case CONSULTAR :
                        switch( i )
                        {
                                case -2 :
                                        retorno.texto = tabela[ 0 ];
                                        retorno.fundo = tabela[ 1 ];
                                        return retorno;
                                case -1 :
                                        retorno.texto = selecaoLeitura[ 0 ];
                                        retorno.fundo = selecaoLeitura[ 1 ];
                                        return retorno;
                        }
                        if( i >= 0  &&  i <= Mat->lins )
                                if( j >= 0  &&  j <= Mat->cols )
                                {
                                        retorno.texto = *( (int *)coresElementos[ identificador ] + 0 + i * Mat->cols + j );
                                        retorno.fundo = *( (int *)coresElementos[ identificador ] + Mat->lins * Mat->cols  + i * Mat->cols + j );
                                        return retorno;
                                }
        }

        //Retorno em caso de problemas
        retorno.texto = -9;
        retorno.fundo = -9;
        return retorno;
}
//###################################################################



/**     registro : Função que armazena quais matrizes estão ativas
    *           ->Entrada: Identificador , operação( ALTERAR(1) ou CONSULTAR(0) ) , entrada( ATIVA(1) ou DESATIVADA(0) )
    */
int registro( int identificador , int operacao , int entrada )
{
        static char statusMatrizes[ QTDMATRIZES ] = { 0 };

        switch( operacao )
        {
                case ALTERAR :
                        statusMatrizes[ identificador ] = entrada;
                        return 2;
                case CONSULTAR :
                        return statusMatrizes[ identificador ];
        }

        return -1;
}
//###################################################################



/**     esconderCursor() : Esconde cursor
    *
    */

void esconderCursor( void )
{
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
}
//###################################################################



/**     exibirCursor() : Exibe cursor
    *
    */

void exibirCursor( void )
{
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = TRUE;
        SetConsoleCursorInfo(consoleHandle, &info);
}
//###################################################################





/**     totalVertical : Soma os elementos da coluna j
    *                           identificador -> Número da matriz. De 1 a @QTDMATRIZES
    *                           coluna -> Coluna j da matriz de dados
    */
int totalVertical( int identificador , int coluna )
{
        int i ;
        struct matriz *Mat;
        int total = 0;

        Mat = Matrizes( identificador );

        for( i = 0 ; i < Mat->lins ; i++ )
                total += *( (int *)Mat->ptr + i * Mat->cols + coluna);

        return total;
}

//###################################################################

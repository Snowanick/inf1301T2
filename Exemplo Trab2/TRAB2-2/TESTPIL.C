/***************************************************************************
*  $MCI M�dulo de implementa��o: TPIL Teste pilha gen�rica
*
*  Arquivo gerado:              TestPIL.c
*  Letras identificadoras:      TPIL
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gdl - Guido Dowsley Leme
*           jpd - Jos� Paulo Diniz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       jpd   16/abr/2016 in�cio do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Pilha.h"


static const char RESET_PILHA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_PILHA_CMD         [ ] = "=criarpilha"     ;
static const char DESTRUIR_PILHA_CMD      [ ] = "=destruirpilha"  ;
static const char ESVAZIAR_PILHA_CMD      [ ] = "=esvaziarpilha"  ;
static const char EMPILHAR_CMD			  [ ] = "=empilhar"		  ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char DESEMPILHAR_CMD         [ ] = "=desempilhar"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PILHA   10
#define DIM_VALOR     100

PIL_tppPilha   vtPilhas[ DIM_VT_PILHA ] ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

   static int ValidarInxPilha( int inxPilha , int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPIL &Testar pilha
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 pilhas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de pilhas. Provoca vazamento de mem�ria
*     =criarpilha                   inxPilha
*     =destruirpilha                inxPilha
*     =esvaziarpilha                inxPilha
*     =empilhar                     inxPilha  string  CondRetEsp
*     =obtervalorelem               inxPilha  string  CondretPonteiro
*     =excluirelem                  inxPilha  CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxPilha  = -1 ,
		  inxDado	= -1,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      PIL_tpCondRet CondRet ;

      char   StringDado [ DIM_VALOR ] ;
	  char   vetDado[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'} ;
	  char   teste = '\0' ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

	  void *EndObtido = NULL;
	  void *EndEsperado = NULL;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de pilha */

         if ( strcmp( ComandoTeste , RESET_PILHA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_PILHA ; i++ )
            {
               vtPilhas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de pilha */

      /* Testar CriarPilha */

         else if ( strcmp( ComandoTeste , CRIAR_PILHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
				&inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxPilha( inxPilha , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = PIL_CriarPilha( &vtPilhas[ inxPilha ] ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
               "Erro ao criar pilha."  ) ;

         } /* fim ativa: Testar CriarPilha */

      /* Testar Esvaziar pilha */

         else if ( strcmp( ComandoTeste , ESVAZIAR_PILHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp, PIL_EsvaziarPilha( vtPilhas[ inxPilha ] ),
					"Retorno inesperado." );

         } /* fim ativa: Testar Esvaziar pilha */

      /* Testar Destruir pilha */

         else if ( strcmp( ComandoTeste , DESTRUIR_PILHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = PIL_DestruirPilha( vtPilhas[ inxPilha ] ) ;
            vtPilhas[ inxPilha ] = NULL ;

            return TST_CompararInt( CondRetEsp , CondRet , "Retorno inesperado." ) ;

         } /* fim ativa: Testar Destruir pilha */

      /* Testar inserir elemento */

         else if ( strcmp( ComandoTeste , EMPILHAR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxPilha , &inxDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = PIL_Empilha( vtPilhas[ inxPilha ], &vetDado[inxDado]);

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento */

      /* Testar excluir elemento */

         else if ( strcmp( ComandoTeste , DESEMPILHAR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxPilha , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxPilha( inxPilha , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      PIL_Desempilha( vtPilhas[ inxPilha ] ) ,
                     "Condi��o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir elemento */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iici" ,
                       &inxPilha , &inxDado , &teste , &ValEsp ) ;

            if ( numLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = PIL_ObterValor( vtPilhas[ inxPilha ], &EndObtido );
            
			if ( CondRet != PIL_CondRetOK )
            {
               return TST_CompararInt( ValEsp , CondRet ,
                         "Erro ao obter endere�o do elemento." ) ;
            } /* if */

			EndEsperado = &vetDado[inxDado];

			if ( EndEsperado != EndObtido ) 
			{
				return TST_CompararPonteiro( EndEsperado, EndObtido, "Endere�o obtido errado." );
			} /*if*/

            return TST_CompararChar( teste , *(char*)EndObtido ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

	  return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TPIL &Testar pilha */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPIL -Validar indice de pilha
*
***********************************************************************/

   int ValidarInxPilha( int inxPilha , int Modo )
   {

      if ( ( inxPilha <  0 )
        || ( inxPilha >= DIM_VT_PILHA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtPilhas[ inxPilha ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtPilhas[ inxPilha ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TPIL -Validar indice de pilha */

/********** Fim do m�dulo de implementa��o: TPIL Teste pilha gen�rica **********/
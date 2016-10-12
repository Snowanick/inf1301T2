/***************************************************************************
*  $MCI Módulo de implementação: LISC  Lista circular
*
*  Arquivo gerado:              LISTACIRC.c
*  Letras identificadoras:      LISC
*
*  Projeto: INF 1301 Jogo de Ludo
*  Autores: vmp - Victor Meira Pinto

*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       vmp   31/set/2016 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

/***********************************************************************
*
*  $TC Tipo de dados: LISC Elemento da lista circular duplamente encadeada
*
*
***********************************************************************/

   typedef struct ListaCircElem {

         void * conteudo ;
               /* Ponteiro para o valor contido no elemento */

         struct ListaCircElem * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct ListaCircElem * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpListaCircElem;

/***********************************************************************
*
*  $TC Tipo de dados: LISC Descritor da lista circular
*
*
***********************************************************************/

   typedef struct LISC_tagListaCirc {

   		tpListaCircElem * pNoCorrente;
   			/* Ponteiro para o nó corrente da lista circular */

   		tpListaCircElem * pUltimoElem;
   			/* Ponteiro para o ultimo elemento que foi inserido na lista circular */

        int numElem ;
               /* Número de elementos da lista */

        void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } LISC_tpListaCirc ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LISC_tpListaCirc pLista ,
                                tpListaCircElem  * pElem   ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LISC  &Criar lista circular
*  ****/

LISC_tpListaCirc LISC_CriarListaCirc(void(*ExcluirValor)(void * pDado)){
   	LISC_tpListaCirc * l;

   	l = (LISC_tpListaCirc *)malloc(sizeof(LISC_tpListaCirc));
   	if(l==NULL){
   		return /* tipo enum pra faltou memoria*/
   	}

   	l->pNoCorrente = NULL;
   	l->pUltimoElem = NULL;
   	l->numElem = 0;

   	l->ExcluirValor = ExcluirValor;

   	return l;
}

/* Fim função: LISC  &Criar lista */

/***************************************************************************
*
*  Função: LISC  &Destruir lista circular
*  ****/
void LISC_DestruirListaCirc( LISC_tpListaCirc p ){

	tpListaCircElem *percorre, aux;

	percorre = p-> pNoCorrente;

	while(percorre != NULL){
		aux = percorre;
		percorre = percorre-> pProx;
		free(aux->conteudo);
		free(aux);
	}

    free( pLista ) ;
} /* Fim função: LISC  &Destruir lista circular*/

/***************************************************************************
*
*  Função: LISC  &Inserir elemento na lista
*  ****/

LISC_tpCondRet LISC_InserirElemento( LISC_tpListaCirc p,void * pConteudo){
   
         tpListaCircElem * pElem ;
   
            pElem = CriarElementoCirc( pConteudo ) ;
            if ( pElem == NULL )
            {
               return/* cond ret de faltar mem */;
            } /* if */
   
            if ( pLista->pNoCorrente == NULL ){
               /* lista circular vazia */
            	pLista->pNoCorrente = pElem;
            	pLista->pUltimoElem = pElem;
            	/* Se tiver vazio aponta para ele mesmo */
            	pElem->pProx = pElem;
            	pElem->pAnt = pElem;

            } 
            else{
            	pElem->pProx = pLista->pUltimoElem->pProx;
            	pElem->pAnt = pLista->pUltimoElem;
            	pLista->pUltimoElem->pProx= pElem;
            	pLista->pUltimoElem = pElem;
            }

   			pLista->numElem++;
   
            return /* cond ret de OK*/ ;
   
} /* Fim função: LISC  &Inserir elemento na lista circular*/

/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LISC_tpListaCirc pLista,
                               tpListaCircElem  * pElem   ) 
   {


      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */

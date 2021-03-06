/***************************************************************************
*  $MCI M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              matriz.c
*  Letras identificadoras:      MAT
*
*  Projeto: Disciplina INF 1301
*  Autores: gdl - Guido Dowsley Leme
*			jpd - Jos� Paulo Diniz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  3.0	   jpd  20/abr/2016 Revisou a documenta��o do m�dulo
*	  2.0	   jpd  19/abr/2016 Implementou o m�dulo para o uso de matriz de pilhas
*	  1.0	   gdl	13/abr/2016	In�cio do desenvolvimento 
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   "matriz.h"

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da c�lula da matriz
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o da c�lula
*
***********************************************************************/

   typedef struct MAT_tgCelulaMatriz {

         struct MAT_tgCelulaMatriz * pNorte ;
		 struct MAT_tgCelulaMatriz * pSul ;
		 struct MAT_tgCelulaMatriz * pLeste ;
		 struct MAT_tgCelulaMatriz * pOeste ;
               /* Ponteiros para as c�lulas adjacentes
                *
                *$EED Assertivas estruturais
                *   Cada ponteiro s� � NULL se n�o existir uma c�lula
                *   na dire��o correspondente
                *   Se n�o for NULL, a c�lula apontada tem um ponteiro na
                *   dire��o oposta apontando para esta c�lula
                *   Norte <-> Sul
                *   Leste <-> Oeste
                */

         PIL_tppPilha Pilha ;
               /* Estrutura de pilha contida na c�lula */

   } MAT_tpCelulaMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabe�a de uma matriz
*
*
*  $ED Descri��o do tipo
*     A cabe�a da matriz � o ponto de acesso para uma determinada matriz.
*     Por interm�dio da refer�ncia para c�lula corrente e dos ponteiros
*     para as c�lulas vizinhas pode-se navegar a matriz sem necessitar
*     de uma lista.
*     Pode-se, inclusive, operar com a matriz em forma de co-rotina.
*     Os �ndices LinhaCorr e ColCorr permitem calcular a posi��o
*     relativa entre a c�lula corrente e a desejada pelo usu�rio.
*     QuantidadeLinhas e QuantidadeColunas permitem determinar se a c�lula desejada
*     existe sem a necessidade de navegar na matriz.
*
***********************************************************************/

   typedef struct MAT_tgMatriz {

         MAT_tpCelulaMatriz * pCelRaiz ;
               /* Ponteiro para a raiz da matriz: C�lula superior esquerda,
                * Coluna 0, Linha 0 */

         MAT_tpCelulaMatriz * pCelCorr ;
               /* Ponteiro para o n� corrente da matriz */

         int LinhaCorr ;
               /* �ndice da linha de pCelCorr */

         int ColCorr ;
               /* �ndice da coluna de pCelCorr */

         int QuantidadeLinhas ;
               /* N�mero de linhas da matriz */

         int QuantidadeColunas ;
               /* N�mero de colunas da matriz */

   } MAT_tpMatriz ;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static MAT_tpCondRet ObterCelulaNasCoordenadas( MAT_tppMatriz Matriz , int Coluna , int Linha ,
                                                   MAT_tpCelulaMatriz ** Celula ) ;

   static void ExcluirCelula( MAT_tpCelulaMatriz * cel ) ;



/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: MAT Criar matriz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz * ppMatriz )
   {
		
	   MAT_tpMatriz * pMat ;

	  if ( ppMatriz == NULL )
      {
         return MAT_CondRetPonteiroRetornoNulo ;
      } /* if */
	  
	   pMat = (MAT_tpMatriz *) calloc (sizeof(MAT_tpMatriz), 1);
	   
	   if (pMat == NULL)
	   {
		   return MAT_CondRetFaltouMemoria ;
	   } /* if */
	   
	   *ppMatriz = pMat;
	   
	   return MAT_CondRetOK ;

   } /* Fim fun��o: MAT  &Criar matriz */

/***************************************************************************
*
*  Fun��o: MAT Destruir matriz
*  ****/

	MAT_tpCondRet MAT_DestruirMatriz( MAT_tppMatriz Matriz )
	{
		MAT_tpMatriz * pMatriz = (MAT_tpMatriz *) Matriz;
		MAT_tpCelulaMatriz * pCel ;
		if ( pMatriz != NULL )
		{
			if ( pMatriz->pCelRaiz != NULL )
			{
				pCel = pMatriz->pCelRaiz ;
				while ( pCel != NULL )
				{
					pCel = pCel->pSul ;
					MAT_ExcluirLinha( Matriz, 0 ) ;
				} /* while */
			} /* if */

			free( pMatriz ) ;
			pMatriz = NULL;
		} /* if */

		return MAT_CondRetOK;

	} /* Fim fun��o: MAT &Destruir matriz */

/***************************************************************************
*
*  Fun��o: MAT Inserir coluna
*  ****/

   MAT_tpCondRet MAT_InserirColuna( MAT_tppMatriz Matriz )
   {
		int linha;
		MAT_tpCelulaMatriz * cel = NULL,
						   * ultimaCriada = NULL,
						   * novaCelula = NULL;
		MAT_tpMatriz * pMatriz = ( MAT_tpMatriz * ) Matriz ;
		MAT_tpCondRet ret ;

		if ( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		/* Se a matriz estiver vazia, cria uma �nica c�lula */
		if ((pMatriz->QuantidadeColunas == 0) && (pMatriz->QuantidadeLinhas == 0))
		{
			pMatriz->pCelRaiz = (MAT_tpCelulaMatriz *) calloc(sizeof(MAT_tpCelulaMatriz),1);
			
			if (pMatriz->pCelRaiz == NULL)
			{
				return MAT_CondRetFaltouMemoria;
			} /* if */

			pMatriz->QuantidadeColunas = 1;
			pMatriz->QuantidadeLinhas = 1;
			pMatriz->pCelCorr = pMatriz->pCelRaiz;

			return MAT_CondRetOK;
		} /* if */

		/* Obt�m a c�lula na primeira linha, �ltima coluna */
		ret = ObterCelulaNasCoordenadas( Matriz, pMatriz->QuantidadeColunas - 1, 0, &cel);

		if (ret != MAT_CondRetOK)
		{
			return ret;
		} /* if */

		for (linha = 0; linha < pMatriz->QuantidadeLinhas; linha++)
		{
			if (cel == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula = (MAT_tpCelulaMatriz*) calloc(sizeof(MAT_tpCelulaMatriz), 1);

			if (novaCelula == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula->pOeste = cel;
			novaCelula->pNorte = ultimaCriada;

			if (ultimaCriada != NULL)
			{
				ultimaCriada->pSul = novaCelula;
			} /* if */

			ultimaCriada = novaCelula;
			cel->pLeste = novaCelula;
			cel = cel->pSul;
		} /* for */

		pMatriz->QuantidadeColunas++;

		return MAT_CondRetOK;
   } /* Fim fun��o: MAT &Inserir coluna */


/***************************************************************************
*
*  Fun��o: MAT Inserir linha
*  ****/
   MAT_tpCondRet MAT_InserirLinha( MAT_tppMatriz Matriz )
   {
	   int coluna;
	   MAT_tpCelulaMatriz * cel = NULL ,
						  * novaCelula = NULL ,
						  * ultimaCriada = NULL ;
	   MAT_tpMatriz *pMatriz = (MAT_tpMatriz *) Matriz;
	   MAT_tpCondRet ret;


	   if ( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		/* Se a matriz estiver vazia, cria uma �nica c�lula */
		if ((pMatriz->QuantidadeColunas == 0) && (pMatriz->QuantidadeLinhas == 0))
		{
			pMatriz->pCelRaiz = (MAT_tpCelulaMatriz *) calloc(sizeof(MAT_tpCelulaMatriz),1);
			
			if (pMatriz->pCelRaiz == NULL)
			{
				return MAT_CondRetFaltouMemoria;
			} /* if */

			pMatriz->QuantidadeColunas = 1;
			pMatriz->QuantidadeLinhas = 1;
			pMatriz->pCelCorr = pMatriz->pCelRaiz;

			return MAT_CondRetOK;
		} /* if */

		/* Obt�m a c�lula na primeira coluna, �ltima linha */
		ret = ObterCelulaNasCoordenadas( Matriz, 0, pMatriz->QuantidadeLinhas - 1, &cel );

		if (ret != MAT_CondRetOK)
		{
			return ret;
		} /* if */

		for (coluna = 0; coluna < pMatriz->QuantidadeColunas; coluna++)
		{
			if (cel == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula = (MAT_tpCelulaMatriz*) calloc(sizeof(MAT_tpCelulaMatriz), 1);

			if (novaCelula == NULL)
			{
				return MAT_CondRetErroEstrutura;
			}	/* if */

			novaCelula->pNorte = cel;
			novaCelula->pOeste = ultimaCriada;

			if (ultimaCriada != NULL)
			{
				ultimaCriada->pLeste = novaCelula;
			} /* if */

			ultimaCriada = novaCelula;
			cel->pSul = novaCelula;
			cel = cel->pLeste;
		} /* for */

		pMatriz->QuantidadeLinhas++;

		return MAT_CondRetOK;
   } /* Fim fun��o: MAT &Inserir linha */

/***************************************************************************
*
*  Fun��o: MAT Ler c�lula
*  ****/

   MAT_tpCondRet MAT_LerCelula( MAT_tppMatriz Matriz , int Coluna , int Linha , PIL_tppPilha * Pilha )
   {
	   MAT_tpCelulaMatriz * pCel ;
	   MAT_tpCondRet ret;

      if ( Pilha == NULL )
      {
         return MAT_CondRetPonteiroRetornoNulo ;
      } /* if */

      ret = ObterCelulaNasCoordenadas( Matriz , Coluna , Linha , &pCel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

	  *Pilha = pCel->Pilha ;
      return MAT_CondRetOK ;

   } /* Fim fun��o: MAT Ler c�lula */

/***************************************************************************
*
*  Fun��o: MAT Escrever c�lula
*  ****/

   MAT_tpCondRet MAT_EscreverCelula( MAT_tppMatriz Matriz , int Coluna , int Linha , PIL_tppPilha Pilha )
   {

      MAT_tpCelulaMatriz * pCel ;
      MAT_tpCondRet ret ;
	  
	  ret = ObterCelulaNasCoordenadas( Matriz , Coluna , Linha , &pCel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */
	  
      pCel->Pilha = Pilha ;
      return MAT_CondRetOK ;

   } /* Fim fun��o: MAT Escrever c�lula */

/***************************************************************************
*
*  Fun��o: MAT Excluir coluna
*  ****/

   MAT_tpCondRet MAT_ExcluirColuna( MAT_tppMatriz Matriz , int Coluna )
   {

      MAT_tpMatriz * pMatriz = ( MAT_tpMatriz * ) Matriz ;
      MAT_tpCelulaMatriz * pCel ,
			             * pProximaCel ;
      MAT_tpCondRet ret ;
	  
	  ret = ObterCelulaNasCoordenadas( Matriz , Coluna , 0 , &pCel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      /* cel � obrigatoriamente v�lido a partir desse ponto */

      if ( Coluna == 0 )
      {
		  pMatriz->pCelRaiz = pCel->pLeste ;
      } /* if */

      /* Troca a c�lula corrente para a raiz caso ela seja excluida */
      if ( pMatriz->ColCorr == Coluna )
      {
         pMatriz->pCelCorr = pMatriz->pCelRaiz ;
         pMatriz->LinhaCorr = 0 ;
         pMatriz->ColCorr = 0 ;
      } /* if */

      /* Conserta ColCorr */
      if ( pMatriz->ColCorr > Coluna )
      {
         pMatriz->ColCorr -- ;
      } /* if */

      while ( pCel != NULL )
      {
         pProximaCel = pCel->pSul ;

         if ( pCel->Pilha != NULL )
         {
			 PIL_DestruirPilha(pCel->Pilha);
         } /* if */

         ExcluirCelula( pCel ) ;
         pCel = pProximaCel ;
      } /* while */

      pMatriz->QuantidadeColunas-- ;

      return MAT_CondRetOK;

   } /* Fim fun��o: MAT Excluir coluna */

/***************************************************************************
*
*  Fun��o: MAT Excluir linha
*  ****/

   MAT_tpCondRet MAT_ExcluirLinha( MAT_tppMatriz Matriz , int Linha )
   {

      MAT_tpMatriz * pMatriz = ( MAT_tpMatriz * ) Matriz ;
      MAT_tpCelulaMatriz * cel ,
					     * proximaCel ;
      MAT_tpCondRet ret ;
	  
	  ret = ObterCelulaNasCoordenadas( Matriz , 0 , Linha , &cel ) ;
      if ( ret != MAT_CondRetOK )
      {
         return ret ;
      } /* if */

      /* cel � obrigatoriamente v�lido a partir desse ponto */

      if ( Linha == 0 )
      {
         pMatriz->pCelRaiz = cel->pSul ;
      } /* if */

      /* Troca a c�lula corrente para a raiz caso ela seja excluida */
      if ( pMatriz->LinhaCorr == Linha )
      {
         pMatriz->pCelCorr = pMatriz->pCelRaiz ;
         pMatriz->LinhaCorr = 0 ;
         pMatriz->ColCorr = 0 ;
      } /* if */

      /* Conserta LinhaCorr */
      if ( pMatriz->LinhaCorr > Linha )
      {
         pMatriz->LinhaCorr -- ;
      } /* if */

      while ( cel != NULL )
      {
         proximaCel = cel->pLeste ;

         if ( cel->Pilha != NULL )
         {
            PIL_DestruirPilha( cel->Pilha ) ;
         } /* if */

         ExcluirCelula( cel ) ;
         cel = proximaCel ;
      } /* while */

      pMatriz->QuantidadeLinhas-- ;

      return MAT_CondRetOK;

   } /* Fim fun��o: MAT Excluir linha */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: MAT Obter c�lula nas coordenadas
*
*  $ED Descri��o da fun��o
*     Essa fun��o retorna um ponteiro para a c�lula da matriz nas coordenadas
*     (Coluna, Linha). Essa fun��o tem o efeito colateral de atualizar o
*     ponteiro para a c�lula atual na estrutura da matriz.
*
*  $EP Par�metros
*     $P Matriz - matriz que cont�m a c�lula desejada
*     $P Coluna - coluna da c�lula desejada
*                 a coluna mais � esquerda tem �ndice 0
*     $P Linha  - linha da c�lula desejada
*                 a linha mais � esquerda tem �ndice 0
*     $P Celula - par�metro para retorno do ponteiro para a c�lula desejada
*                 este par�metro � passado por refer�ncia
*
*  $AE Assertivas de entrada
*      - Matriz != NULL
*
*  $AE Assertivas de sa�da
*      - Celula aponta para a celula desejada da matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK    - obteve a c�lula sem problemas
*     MAT_CondRetMatrizNaoExiste - o par�metro Matriz � NULO
*     MAT_CondRetNaoPossuiCelula - coordenadas da c�lula est�o fora da matriz
*     MAT_CondRetErroEstrutura - estrutura da matriz est� corrompida
*
***********************************************************************/

   static MAT_tpCondRet ObterCelulaNasCoordenadas( MAT_tppMatriz Matriz , int Coluna , int Linha ,
                                                   MAT_tpCelulaMatriz ** Celula )
   {

      int distCol ,         /* Dist�ncia em colunas da c�lula atual para a desejada */
          distLin ;         /* Dist�ncia em linhas da c�lula atual para a desejada */

	  MAT_tpMatriz * pMatriz ;

      if ( Matriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      pMatriz = ( MAT_tpMatriz * ) Matriz ;

      if ( ( Coluna >= pMatriz->QuantidadeColunas )
        || ( Linha >= pMatriz->QuantidadeLinhas ))
      {
         return MAT_CondRetNaoPossuiCelula ;
      } /* if */

      if ( pMatriz->pCelCorr == NULL )
      {
         return MAT_CondRetErroEstrutura;
      } /* if */

      distCol = ( pMatriz->ColCorr - Coluna ) ;
	  if (distCol < 0)
	  {
		  distCol *= -1 ;
	  } /* if */

      distLin = ( pMatriz->LinhaCorr - Linha ) ;
	  if (distLin < 0)
	  {
		  distLin *= -1 ;
	  } /* if */

	  /* Percorre a matriz na horizontal */
      while (distCol != 0)
	  {
		  if (pMatriz->ColCorr < Coluna)
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pLeste;
			  pMatriz->ColCorr++;
		  } /* if */
		  else
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pOeste;
			  pMatriz->ColCorr--;
		  } /* else */

		  distCol--;
	  } /* while */

	  /* Percorre a matriz na vertical */
      while (distLin != 0)
	  {
		  if (pMatriz->LinhaCorr < Linha)
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pSul;
			  pMatriz->LinhaCorr++;
		  } /* if */
		  else
		  {
			  pMatriz->pCelCorr = pMatriz->pCelCorr->pNorte;
			  pMatriz->LinhaCorr--;
		  } /* else */

		  distLin--;
	  } /* while */

      /* Retorna a c�lula obtida */
      *Celula = pMatriz->pCelCorr;
	  
      return MAT_CondRetOK ;
   } /* Fim fun��o: Obter Celula nas Coordenadas */


/***********************************************************************
*
*  $FC Fun��o: Excluir C�lula
*
*  $ED Descri��o da fun��o
*     Essa fun��o exclui a c�lula passada por par�metro e troca os ponteiros
*     das c�lulas vizinhas de acordo.
*     Essa fun��o n�o exclui a pilha armazenada na c�lula
*
*  $EP Par�metros
*     $P cel - C�lula a excluir
*              este par�metro � passado por refer�ncia
*
*  $AE Assertivas de entrada
*      - cel != NULL
*
*  $AE Assertivas de sa�da
*      - C�lula desejada foi exclu�da com sucesso
*	   - Valem as assertivas estruturais da matriz de pilhas deste m�dulo
*
***********************************************************************/

   static void ExcluirCelula( MAT_tpCelulaMatriz * cel )
   {
	   MAT_tpCelulaMatriz *pcel = cel;
	   if (cel ->pNorte != NULL)
	   {
		   cel->pNorte->pSul = cel->pSul;
	   } /* if */
	   
	   if (cel ->pSul != NULL)
	   {
		   cel->pSul->pNorte = cel->pNorte;
	   } /* if */

	   if (cel ->pLeste != NULL)
	   {
		   cel->pLeste->pOeste = cel->pOeste;
	   } /* if */

	   if (cel ->pOeste != NULL)
	   {
		   cel->pOeste->pLeste = cel->pLeste;
	   } /* if */

	   free( pcel ) ;

   } /* Fim fun��o: Excluir Celula */
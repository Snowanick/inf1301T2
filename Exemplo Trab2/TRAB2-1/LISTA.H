#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Listas duplamente encadeadas
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gdl - Guido Dowsley Leme
*           jpd - Jos� Paulo Diniz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	  3		  jpd	06/abr/2016 adaptou o modulo para listas genericas
*     2       jpd   26/mar/2016 revisou o codigo e atualizou a documentacao
*     1       jpd   22/mar/2016 adaptou o modulo para o uso de varias listas
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     LIS_tppLista * - ponteiro para ponteiro de lista que ser�
*                      retornada por refer�ncia. Se ocorrer algum erro,
*                      o par�metro n�o � modificado.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*	$AE Assertivas de entrada
*	  - ppLista recebe o endere�o da lista a ser criada
*
*	$AS Assertivas de saida
*	  - A lista foi criada e seu endere�o foi inserido em ppLista
*	  - A lista est� vazia. Portanto n�o possui elemento corrente, origem nem fim.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * ppLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*	$ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*	$FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
*	$AE Assertivas de Entrada
*	  - pLista aponta para a Lista a ser destruida
*	  - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
*	$AS Assertivas de Saida
*	  - lista foi esvaziada e excluida
*	  - pLista agora tem valor NULL
*
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*	$FV Valor retornado
*     LIS_CondRetOK    - esvaziou sem problemas
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $AE Assertivas de Entrada
*	 - pLista aponta para a lista a ser esvaziada
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
*  $AE Assertivas de Saida
*	 - a lista est� vazia. Portanto n�o possui elemento corrente, origem nem fim.
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     Valor - valor do novo elemento
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista onde deseja-se inserir o elemento
*    - pElemCorr aponta para o elemento onde ser� inserido um elemento anterior a ele
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*    - se a lista estiver vazia, sera criado o primeiro elemento dela
*
*  $AS Assertivas de saida
*    - elemento foi criado antes do n� corrente
*	 - pElemCorr agora aponta para o ultimo elemento criado
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void   *Valor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        Valor - valor do novo elemento
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista onde deseja-se inserir o elemento
*    - pElemCorr aponta para o elemento onde ser� inserido um elemento posterior a ele
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*    - se a lista estiver vazia, sera criado o primeiro elemento dela
*
*  $AS Assertivas de saida
*    - elemento foi criado depois do n� corrente
*	 - se pElemCorr era o �ltimo da lista, o novo elemento agora � o �ltimo da lista
*	 - pElemCorr agora aponta para o ultimo elemento criado
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void    *Valor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $AE Assertivas de entrada
*	 - pLista aponta para lista onde deseja-se excluir o elemento
*	 - pElemCorr aponta para o elemento a ser exclu�do
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
*  $AS Assertivas de saida
*    - elemento foi excluido
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista onde deseja-se obter o valor do elemento
*	 - pElemCorr aponta para o n� cujo valor deseja-se obter
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
*  $AS Assertivas de saida
*	 - pValor contem o endere�o do valor desejado
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista ,  void * pValor) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
*	$FV Valor retornado
*     LIS_CondRetOK    - alterou pElemCorr sem problemas
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista que deseja-se percorrer
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
*  $AS Assertivas de saida
*	 - pElemCorr aponta para o inicio da lista
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
***********************************************************************/

   LIS_tpCondRet IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
*	$FV Valor retornado
*     LIS_CondRetOK    - alterou pElemCorr sem problemas
*
*  $AE Assertivas de entrada
*	 - pLista aponta para a lista que deseja-se percorrer
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
*  $AS Assertivas de saida
*	 - pElemCorr aponta para o ultimo elemento da lista
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
***********************************************************************/

   LIS_tpCondRet IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est� vazia
*
*  $AE Assertivas de entrada
*	 - numElem != 0
*	 - pLista aponta para a lista que deseja-se percorrer
*	 - a lista n�o deve estar vazia
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
*  $AS Assertivas de saida
*	 - se pElemCorr estiver a menos de |NumElem| do inicio ou fim da lista,
*				pElemCorr passa a apontar para uma das extremidades da lista
*	 - pElemCorr aponta para |NumElem| antes ou depois do elemento que apontava (depende do sinal)
*	 - valem as assertivas estruturais da lista duplamente encadeada com cabe�a
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif

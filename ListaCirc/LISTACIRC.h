/***************************************************************************
 *
 *  $MCD Módulo de definição: LISC  Lista Circular
 *
 *  Arquivo gerado:              LISTACIRC.h
 *  Letras identificadoras:      LISC
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *
 *
 *  Projeto: INF 1301 Jogo de Ludo
 *  Autores: awv - Alexandre Wanick Vieira
 *           bcr - Bernardo Costa Ruga
 *           vmp - Victor Meira Pinto
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     1       bcr   12/10/2016  Início do desenvolvimento do .h
 *
 *
 *  $ED Descrição do módulo
 *     Implementa um conjunto simples de funções para criar e manipular listas circulares genéricas.
 *     
 *     A lista é referenciada pelo usuário utilizando um ponteiro para uma estrutura alocada pela função LISC_CriarListaCirc.
 *     
 *     Ao seu criada, a lista não possui elementos, nem nó para o próximo elemento, nem nó para o elemento anterior. 
 *     estes serão adicionados utilizando a função LISC_InserirElemento.
 *  
 *     Para liberar algum elemento na lista é necessário utilizar a função LISC_LiberarElemento.
 *   
 *     Para destruir a lista completamente deve ser utilizada a função LISC_DestruirListaCirc, que irá destruir cada elemento da lista e 
 *     destrui-lo.
 *
 *
 ***************************************************************************/



/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LISC_tagListaCirc *  LISC_tpListaCirc;



/***********************************************************************
 *
 *  $TC Tipo de dados: LISC Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções da lista circular
 *
 ***********************************************************************/

typedef enum {
    
    LISC_CondRetOK ,
    /* Concluiu corretamente */
    
    LISC_CondRetListaVazia ,
    /* A lista não contém elementos */
    
    LISC_CondRetFimLista ,
    /* Foi atingido o fim de lista */
    
    LISC_CondRetNaoAchou ,
    /* Não encontrou o valor procurado */
    
    LISC_CondRetFaltouMemoria
    /* Faltou memória ao tentar criar um elemento de lista */
    
} LISC_tpCondRet ;


/***********************************************************************
 *
 *  $FC Função: LISC  &Criar lista circular
 *
 *  $ED Descrição da função
 *     Cria uma lista circular genérica.
 *
 *  $EP Parâmetros
 *     ExcluirValor  - ponteiro para a função que processa a
 *                     exclusão do valor referenciado pelo elemento
 *                     a ser excluído.
 *                     Ver descrição do módulo.
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna o ponteiro para a lista.
 *     Este ponteiro será utilizado pelas funções que manipulem esta lista.
 *
 *     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
 *     a função retornará NULL.
 *     Não será dada mais informação quanto ao problema ocorrido.
 *
 ***********************************************************************/

LISC_tpListaCirc LISC_CriarListaCirc(void(*ExcluirValor)(void * pDado));


/***********************************************************************
 *
 *  $FC Função: LISC  &Destruir lista circular
 *
 *  $ED Descrição da função
 *     Destrói a lista fornecida.
 *     O parâmetro ponteiro para a lista não é modificado.
 *     Se ocorrer algum erro durante a destruição, a lista resultará
 *     estruturalmente incorreta.
 *     OBS. não existe previsão para possíveis falhas de execução.
 *
 *  $FV Valor retornado
 *     LIS_CondRetOK    - destruiu sem problemas
 *
 ***********************************************************************/

void LISC_DestruirListaCirc( LISC_tpListaCirc p );


/***********************************************************************
 *
 *  $FC Função: LISC  &Inserir elemento
 *
 *  $ED Descrição da função
 *     Insere novo elemento.
 *     Caso a lista esteja vazia, insere o primeiro elemento da lista.
 *
 *  $EP Parâmetros
 *     pLista - ponteiro para a lista onde deve ser inserido o elemento
 *     pConteudo - ponteiro para o valor do novo elemento
 *              Pode ser NULL
 *
 *  $FV Valor retornado
 *     LIS_CondRetOK
 *     LIS_CondRetFaltouMemoria
 *
 ***********************************************************************/

LISC_tpCondRet LISC_InserirElemento( LISC_tpListaCirc pLista,void * pConteudo);


/***********************************************************************
 *
 *  $FC Função: LIS  &Liberar elemento
 *
 *  $ED Descrição da função
 *     Exclui o elemento desejado na lista dada.
 *     Se existir o elemento anterior a ele, este será o novo corrente.
 *     Se este também não existir a lista tornou-se vazia.
 *
 *  $EP Parâmetros
 *     pLista    - ponteiro para a lista na qual deve excluir.
 *     pElem     - ponteiro para o elemento que será excluido.
 *
 *  $FV Valor retornado
 *     LIS_CondRetOK
 *     LIS_CondRetListaVazia
 *
 ***********************************************************************/

void LISC_LiberarElemento( LISC_tpListaCirc pLista, tpListaCircElem  * pElem);



/********** Fim do módulo de definição: LISC  Lista circular **********/

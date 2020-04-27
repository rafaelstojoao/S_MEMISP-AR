//
//  functions.h
//  S_MEMISP+AR
//
//  Created by Rafael Stoffalette João on 1/8/15.
//  Copyright (c) 2015 Rafael Stoffalette João. All rights reserved.
//

#ifndef __S_MEMISP_AR__functions__
#define __S_MEMISP_AR__functions__

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define MIN_SUP 0.150

/****************************/// Estruturas de dados
typedef struct item{
    string item;
    struct item *proximoItem;
    double item_suporte;
}tipoItem;


typedef struct itemset{
    tipoItem *primeiroItem;
    int tamanhoItemset;
    double suporteItemset;
    struct itemset *proximoItemset;
}tipoItemset;


typedef struct sequencia{
    tipoItemset *primeiroItemset;
    int tamanhoSequencia;
    double suporteSequencia;
    struct sequencia *proximaSequencia;
}tipoSequencia;

typedef struct memorydb{
    tipoSequencia  *inicioMDB; //primeira sequencia da mdb
    int tamanhoMDB; // quantidade de sequencias na MDB
}memorydb;

typedef struct lista_de_Itens{
    item *cabeca;
    int tamanho;
}tlista_de_Itens;

typedef struct indice_par{
    int pos;
    int seqNum;
    sequencia *ptr;
    indice_par *prox;
}indice_par;

typedef struct pidx{
    sequencia s;
    pidx *prox;
    indice_par *cabeca;
    int tamanho;
}tpidx;

typedef struct sequenciaFrequente{
    sequencia *s;
    sequenciaFrequente *prox;
    
}seqFreq;

typedef struct listaSequenciasFrequetes{
    sequenciaFrequente *cabeca;
    int qtd_seq_freq;
    
}tListFreq;

/****************************/// Protótipos das funções
void hello();
void inicializaDado(tipoItem *i);
void inicializaDado(tipoItemset *it);
void inicializaDado(tipoSequencia *s);
void inicializaItem(tipoItem *i);
void inicializaItemset(tipoItemset *it);
void inicializaSequencia(tipoSequencia *s);
void insereItemItemset(tipoItem *it, tipoItemset *e);
void insereItemsetSequencia (tipoItemset *e, tipoSequencia *s);
void imprimeitemset(tipoItemset *e);
void imprimeSequencia(tipoSequencia *s);
void imprimeMDB(memorydb *m);
float calculaSuporte(int type, tipoItem *i, tipoItemset *e, tipoSequencia *s, memorydb *m);
int buscaItemSequencia(string c, tipoSequencia *s);
int buscaS1EmS2(tipoSequencia *s1, tipoSequencia *s2);
void find_all_frequent_items(lista_de_Itens *lf, memorydb *m);
void criaIndexSet(tipoSequencia *s, pidx *p, memorydb *m);
void insereIndiceIDX(pidx *p, indice_par *index, int contSeq);
void imprimeListaIndices(pidx *p);
void imprimeitemsetArq(tipoItemset *e, ifstream arq);
void imprimeSequenciaArq(tipoSequencia *s, ifstream arq);
void imprimeListaIndicesArq(pidx *p,string item);
void percorreLF(lista_de_Itens *lf, memorydb *mdb);
void mine(tipoSequencia *sit,pidx *pid,memorydb *mdb);
void mine2(sequencia *pattern, pidx *pid, memorydb *mdb);
void     wait_on_enter();
void imprimeListaIndices_emArq(pidx *p, string nomedoArq);

#endif /* defined(__S_MEMISP_AR__functions__) */
